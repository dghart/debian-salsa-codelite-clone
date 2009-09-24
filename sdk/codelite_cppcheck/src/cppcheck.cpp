/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2009 Daniel Marjamäki and Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */
#include "cppcheck.h"

#include "preprocessor.h" // preprocessor.
#include "tokenize.h"   // <- Tokenizer

#include "filelister.h"

#include "check.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include <map>
#include <stdexcept>

#ifdef __GNUC__
#include <ctime> // clock_t
#endif

//---------------------------------------------------------------------------

CppCheck::CppCheck(ErrorLogger &errorLogger)
{
    _errorLogger = &errorLogger;
}

CppCheck::~CppCheck()
{

}

void CppCheck::settings(const Settings &settings)
{
    _settings = settings;
}

void CppCheck::addFile(const std::string &path)
{
    FileLister::recursiveAddFiles(_filenames, path.c_str(), true);
}

void CppCheck::addFile(const std::string &path, const std::string &content)
{
    _filenames.push_back(path);
    _fileContents[ path ] = content;
}

void CppCheck::clearFiles()
{
    _filenames.clear();
    _fileContents.clear();
}




std::string CppCheck::parseFromArgs(int argc, const char* const argv[])
{
    std::vector<std::string> pathnames;
    bool showHelp = false;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--version") == 0)
            return "Cppcheck 1.36\n";

        // Flag used for various purposes during debugging
        if (strcmp(argv[i], "--debug") == 0)
            _settings._debug = true;

        // Show all messages
        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
            _settings._showAll = true;

        // Only print something when there are errors
        else if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0)
            _settings._errorsOnly = true;

        // Checking coding style
        else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--style") == 0)
            _settings._checkCodingStyle = true;

        // Verbose error messages (configuration info)
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
            _settings._verbose = true;

        // Force checking of files that have "too many" configurations
        else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0)
            _settings._force = true;

        // Write results in results.xml
        else if (strcmp(argv[i], "--xml") == 0)
            _settings._xml = true;

        // Check if there are unused functions
        else if (strcmp(argv[i], "--unused-functions") == 0)
            _settings._unusedFunctions = true;

        // Append userdefined code to checked source code
        else if (strncmp(argv[i], "--append=", 9) == 0)
            _settings.append(9 + argv[i]);

#ifdef __GNUC__
        // show timing information..
        else if (strcmp(argv[i], "--showtime") == 0)
            _settings._showtime = true;
#endif

        // Print help
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            pathnames.clear();
            _filenames.clear();
            showHelp = true;
            break;
        }


        // --error-exitcode=1
        else if (strncmp(argv[i], "--error-exitcode=", 17) == 0)
        {
            std::string temp = argv[i];
            temp = temp.substr(17);
            std::istringstream iss(temp);
            if (!(iss >> _settings._exitCode))
            {
                _settings._exitCode = 0;
                return "cppcheck: Argument must be an integer. Try something like '--error-exitcode=1'\n";
            }
        }

        // Include paths
        else if (strcmp(argv[i], "-I") == 0 || strncmp(argv[i], "-I", 2) == 0)
        {
            std::string path;

            // "-I path/"
            if (strcmp(argv[i], "-I") == 0)
            {
                ++i;
                if (i >= argc)
                    return "cppcheck: argument to '-I' is missing\n";

                path = argv[i];
            }

            // "-Ipath/"
            else
            {
                path = argv[i];
                path = path.substr(2);
            }

            // If path doesn't end with / or \, add it
            if (path[path.length()-1] != '/' && path[path.length()-1] != '\\')
                path += '/';

            _settings._includePaths.push_back(path);
        }


        // Output formatter
        else if (strcmp(argv[i], "--template") == 0)
        {
            // "--template path/"
            if (strcmp(argv[i], "--template") == 0)
            {
                ++i;
                if (i >= argc)
                    return "cppcheck: argument to '--template' is missing\n";

                _settings._outputFormat = argv[i];
            }
        }

        // Include paths
        else if (strcmp(argv[i], "-j") == 0 ||
                 strncmp(argv[i], "-j", 2) == 0)
        {
            std::string numberString;

            // "-j 3"
            if (strcmp(argv[i], "-j") == 0)
            {
                ++i;
                if (i >= argc)
                    return "cppcheck: argument to '-j' is missing\n";

                numberString = argv[i];
            }

            // "-j3"
            else if (strncmp(argv[i], "-j", 2) == 0)
            {
                numberString = argv[i];
                numberString = numberString.substr(2);
            }

            std::istringstream iss(numberString);
            if (!(iss >> _settings._jobs))
                return "cppcheck: argument to '-j' is not a number\n";

            if (_settings._jobs > 1000)
            {
                return "cppcheck: argument for '-j' is allowed to be 1000 at max\n";
            }
        }

        // auto deallocated classes..
        else if (strcmp(argv[i], "--auto-dealloc") == 0)
        {
            ++i;

            if (i >= argc || !strstr(argv[i], ".lst"))
                return "No .lst file specified for the --auto-dealloc option\n";

            std::ifstream f(argv[i]);
            if (!f.is_open())
                return "couldn't open the file \"" + std::string(argv[i+1]) + "\"\n";
            _settings.autoDealloc(f);
        }

        // print all possible error messages..
        else if (strcmp(argv[i], "--errorlist") == 0)
        {
            // call all "getErrorMessages" in all registered Check classes
            std::cout << ErrorLogger::ErrorMessage::getXMLHeader();
            for (std::list<Check *>::iterator it = Check::instances().begin(); it != Check::instances().end(); ++it)
            {
                (*it)->getErrorMessages();
            }
            std::cout << ErrorLogger::ErrorMessage::getXMLFooter() << std::endl;
            return "";
        }

        // documentation..
        else if (strcmp(argv[i], "--doc") == 0)
        {
            std::ostringstream doc;
            // Get documentation..
            for (std::list<Check *>::iterator it = Check::instances().begin(); it != Check::instances().end(); ++it)
            {
                doc << "===" << (*it)->name() << "===\n"
                << (*it)->classInfo() << "\n\n";
            }
            doc << "===" << "Unused functions" << "===\n"
            << "Check for functions that are never called\n";
            std::string doc2(doc.str());
            while (doc2.find("\n\n\n") != std::string::npos)
                doc2.erase(doc2.find("\n\n\n"), 1);
            std::cout << doc2;
            return "";
        }

        else if (strncmp(argv[i], "-", 1) == 0 || strncmp(argv[i], "--", 2) == 0)
        {
            return "cppcheck: error: unrecognized command line option \"" + std::string(argv[i]) + "\"\n";
        }

        else
            pathnames.push_back(argv[i]);
    }

    if (_settings._unusedFunctions && _settings._jobs > 1)
    {
        return "cppcheck: error: --unused-functions can't be used with -j option.\n";
    }

    if (pathnames.size() > 0)
    {
        // Execute recursiveAddFiles() to each given file parameter
        std::vector<std::string>::const_iterator iter;
        for (iter = pathnames.begin(); iter != pathnames.end(); iter++)
            FileLister::recursiveAddFiles(_filenames, iter->c_str(), true);
    }

    if (argc <= 1 || showHelp)
    {
        std::ostringstream oss;
        oss <<   "Cppcheck - A tool for static C/C++ code analysis\n"
        "\n"
        "Syntax:\n"
        "    cppcheck [--all] [--append=file] [--auto-dealloc file.lst]\n"
        "             [--error-exitcode=[n]] [--force] [--help] [-Idir] [-j [jobs]]\n"
        "             [--quiet] [--style] [--unused-functions] [--verbose] [--version]\n"
        "             [--xml] [file or path1] [file or path] ...\n"
        "\n"
        "If path is given instead of filename, *.cpp, *.cxx, *.cc, *.c++ and *.c files\n"
        "are checked recursively from given directory.\n\n"
        "Options:\n"
        "    -a, --all            Make the checking more sensitive. More bugs are\n"
        "                         detected, but there are also more false positives\n"
        "    --append=file        This allows you to provide information about\n"
        "                         functions by providing an implementation for these.\n"
        "    --auto-dealloc file  Suppress warnings about classes that have automatic\n"
        "                         deallocation.\n"
        "                         The classnames must be provided in plain text - one\n"
        "                         classname / line - in a .lst file.\n"
        "                         This option can be used several times, allowing you to\n"
        "                         specify several .lst files.\n"
        "    --error-exitcode=[n] If errors are found, integer [n] is returned instead\n"
        "                         of default 0. EXIT_FAILURE is returned\n"
        "                         if arguments are not valid or if no input files are\n"
        "                         provided. Note that your operating system can\n"
        "                         modify this value, e.g. 256 can become 0.\n"
        "    -f, --force          Force checking on files that have \"too many\"\n"
        "                         configurations\n"
        "    -h, --help           Print this help\n"
        "    -I [dir]             Give include path. Give several -I parameters to give\n"
        "                         several paths. First given path is checked first. If\n"
        "                         paths are relative to source files, this is not needed\n"
        "    -j [jobs]            Start [jobs] threads to do the checking simultaneously.\n"
        "    -q, --quiet          Only print error messages\n"
        "    -s, --style          Check coding style\n"
        "    --template '[text]'  Format the error messages. E.g.\n"
        "                         '{file}:{line},{severity},{id},{message}' or\n"
        "                         '{file}({line}):({severity}) {message}'\n"
        "    --unused-functions   Check if there are unused functions\n"
        "    -v, --verbose        More detailed error reports\n"
        "    --version            Print out version number\n"
        "    --xml                Write results in xml to error stream.\n"
        "\n"
        "Example usage:\n"
        "  # Recursively check the current folder. Print the progress on the screen and\n"
        "    write errors in a file:\n"
        "    cppcheck . 2> err.txt\n"
        "  # Recursively check ../myproject/ and print only most fatal errors:\n"
        "    cppcheck --quiet ../myproject/\n"
        "  # Check only files one.cpp and two.cpp and give all information there is:\n"
        "    cppcheck -v -a -s one.cpp two.cpp\n"
        "  # Check f.cpp and search include files from inc1/ and inc2/:\n"
        "    cppcheck -I inc1/ -I inc2/ f.cpp\n";
        return oss.str();
    }
    else if (_filenames.empty())
    {
        return "cppcheck: No C or C++ source files found.\n";
    }


    return "";
}

unsigned int CppCheck::check()
{
    _checkUnusedFunctions.setErrorLogger(this);
    std::sort(_filenames.begin(), _filenames.end());
    for (unsigned int c = 0; c < _filenames.size(); c++)
    {
        _errout.str("");
        std::string fname = _filenames[c];

        if (_settings._errorsOnly == false)
            _errorLogger->reportOut(std::string("Checking ") + fname + std::string("..."));

        try
        {
            Preprocessor preprocessor(&_settings, this);
            std::list<std::string> configurations;
            std::string filedata = "";

            if (_fileContents.size() > 0 && _fileContents.find(_filenames[c]) != _fileContents.end())
            {
                // File content was given as a string
                std::istringstream iss(_fileContents[ _filenames[c] ]);
                preprocessor.preprocess(iss, filedata, configurations, fname, _settings._includePaths);
            }
            else
            {
                // Only file name was given, read the content from file
                std::ifstream fin(fname.c_str());
                preprocessor.preprocess(fin, filedata, configurations, fname, _settings._includePaths);
            }

            int checkCount = 0;
            for (std::list<std::string>::const_iterator it = configurations.begin(); it != configurations.end(); ++it)
            {
                // Check only 12 first configurations, after that bail out, unless --force
                // was used.
                if (!_settings._force && checkCount > 11)
                {
                    if (_settings._errorsOnly == false)
                        _errorLogger->reportOut(std::string("Bailing out from checking ") + fname + ": Too many configurations. Recheck this file with --force if you want to check them all.");

                    break;
                }

                cfg = *it;
#ifdef __GNUC__
                clock_t c1 = clock();
                const std::string codeWithoutCfg = Preprocessor::getcode(filedata, *it, fname, _errorLogger);
                if (_settings._showtime)
                {
                    clock_t c2 = clock();
                    std::cout << "Preprocessor::getcode: " << ((c2 - c1) / 1000) << std::endl;
                }
#else
                std::string codeWithoutCfg = Preprocessor::getcode(filedata, *it, fname, _errorLogger);
#endif

                // If only errors are printed, print filename after the check
                if (_settings._errorsOnly == false && it != configurations.begin())
                    _errorLogger->reportOut(std::string("Checking ") + fname + ": " + cfg + std::string("..."));

                checkFile(codeWithoutCfg + _settings.append(), _filenames[c].c_str());
                ++checkCount;
            }
        }
        catch (std::runtime_error &e)
        {
            // Exception was thrown when checking this file..
            _errorLogger->reportOut("Bailing out from checking " + fname + ": " + e.what());
        }

        _errorLogger->reportStatus(c + 1, (unsigned int)_filenames.size());
    }

    // This generates false positives - especially for libraries
    _settings._verbose = false;
    if (_settings._unusedFunctions)
    {
        _errout.str("");
        if (_settings._errorsOnly == false)
            _errorLogger->reportOut("Checking usage of global functions..");

        _checkUnusedFunctions.check();
    }



    unsigned int result = static_cast<unsigned int>(_errorList.size());
    _errorList.clear();
    return result;
}


//---------------------------------------------------------------------------
// CppCheck - A function that checks a specified file
//---------------------------------------------------------------------------

void CppCheck::checkFile(const std::string &code, const char FileName[])
{
    Tokenizer _tokenizer(&_settings, this);

    // Tokenize the file
    {
        std::istringstream istr(code);
        if (!_tokenizer.tokenize(istr, FileName))
        {
            // File had syntax errors, abort
            return;
        }
    }

    // Set variable id
    _tokenizer.setVarId();

    _tokenizer.fillFunctionList();

    // call all "runChecks" in all registered Check classes
    for (std::list<Check *>::iterator it = Check::instances().begin(); it != Check::instances().end(); ++it)
    {
        (*it)->runChecks(&_tokenizer, &_settings, this);
    }

#ifdef __GNUC__
    {
        clock_t c1 = clock();
        _tokenizer.simplifyTokenList();
        clock_t c2 = clock();
        if (_settings._showtime)
            std::cout << "Tokenizer::simplifyTokenList: " << ((c2 - c1) / 1000) << std::endl;
    }
#else
    _tokenizer.simplifyTokenList();
#endif

    if (_settings._unusedFunctions)
        _checkUnusedFunctions.parseTokens(_tokenizer);

    // call all "runSimplifiedChecks" in all registered Check classes
    for (std::list<Check *>::iterator it = Check::instances().begin(); it != Check::instances().end(); ++it)
    {
#ifdef __GNUC__
        clock_t c1 = clock();
        (*it)->runSimplifiedChecks(&_tokenizer, &_settings, this);
        clock_t c2 = clock();
        if (_settings._showtime)
            std::cout << (*it)->name() << "::runSimplifiedChecks: " << ((c2 - c1) / 1000) << std::endl;
#else
        (*it)->runSimplifiedChecks(&_tokenizer, &_settings, this);
#endif
    }
}

Settings CppCheck::settings() const
{
    return _settings;
}

//---------------------------------------------------------------------------

void CppCheck::reportErr(const ErrorLogger::ErrorMessage &msg)
{
    std::string errmsg = msg.toText();

    // Alert only about unique errors
    if (std::find(_errorList.begin(), _errorList.end(), errmsg) != _errorList.end())
        return;

    _errorList.push_back(errmsg);
    std::string errmsg2(errmsg);
    if (_settings._verbose)
    {
        errmsg2 += "\n    Defines=\'" + cfg + "\'\n";
    }

    _errorLogger->reportErr(msg);

    _errout << errmsg2 << std::endl;
}

void CppCheck::reportOut(const std::string &outmsg)
{
    _errorLogger->reportOut(outmsg);
}

const std::vector<std::string> &CppCheck::filenames() const
{
    return _filenames;
}

void CppCheck::reportStatus(unsigned int /*index*/, unsigned int /*max*/)
{

}
