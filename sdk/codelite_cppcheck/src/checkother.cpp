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


//---------------------------------------------------------------------------
#include "checkother.h"
#include "mathlib.h"
#include "tokenize.h"

#include <algorithm>
#include <list>
#include <map>
#include <sstream>
#include <cstring>
#include <cctype>
//---------------------------------------------------------------------------

// Register this check class (by creating a static instance of it)
namespace
{
CheckOther instance;
}

//---------------------------------------------------------------------------



void CheckOther::warningOldStylePointerCast()
{
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        // Old style pointer casting..
        if (!Token::Match(tok, "( const| %type% * ) %var%"))
            continue;

        int addToIndex = 0;
        if (tok->tokAt(1)->str() == "const")
            addToIndex = 1;

        if (tok->tokAt(4 + addToIndex)->str() == "const")
            continue;

        // Is "type" a class?
        const std::string pattern("class " + tok->tokAt(1 + addToIndex)->str());
        if (!Token::findmatch(_tokenizer->tokens(), pattern.c_str()))
            continue;

        cstyleCastError(tok);
    }
}




//---------------------------------------------------------------------------
// Redundant code..
//---------------------------------------------------------------------------

void CheckOther::warningRedundantCode()
{

    // if (p) delete p
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (! Token::simpleMatch(tok, "if ("))
            continue;

        const char *varname = NULL;
        const Token *tok2 = tok->tokAt(2);

        /*
         * Possible if-constructions:
         *
         *   if (var)
         *   if (this->var)
         *   if (Foo::var)
         *
         **/

        if (Token::Match(tok2, "%var% .|::"))
        {
            tok2 = tok2->tokAt(2);
        }

        if (Token::Match(tok2, "%var%"))
        {
            varname = tok2->strAt(0);
            tok2 = tok2->next();
        }

        if (tok2->str() == ")")
        {
            tok2 = tok2->next();

        }
        else
        {
            varname = NULL;
        }

        if (varname == NULL)
            continue;

        bool ifHasBracket = false;
        if (tok2->str() == "{")
        {
            tok2 = tok2->next();
            ifHasBracket = true;
        }

        bool err = false;
        bool funcHasBracket = false;

        /*
         * Possible constructions:
         *
         * - delete %var%
         * - delete [] %var%
         * - free ( %var )
         * - kfree ( %var% )
         *
         * Where %var% may be:
         * - just variable name (var)
         * - class member (this->var)
         * - static member (Class::var)
         *
         **/

        if (Token::Match(tok2, "free|kfree ("))
        {
            tok2 = tok2->tokAt(2);
            funcHasBracket = true;

        }
        else if (tok2->str() == "delete")
        {

            tok2 = tok2->next();

            if (Token::simpleMatch(tok2, "[ ]"))
            {
                tok2 = tok2->tokAt(2);
            }
        }

        if (Token::Match(tok2, "%var% ::|."))
        {
            tok2 = tok2->tokAt(2);
        }

        if (Token::Match(tok2, "%var%") && (strcmp(tok2->strAt(0), varname) == 0))
        {
            tok2 = tok2->next();
            err = true;
        }

        if (funcHasBracket)
        {
            if (tok2->str() != ")")
            {
                err = false;
            }
            else
            {
                tok2 = tok2->next();
            }
        }

        if (tok2->str() != ";")
        {
            err = false;
        }
        else
        {
            tok2 = tok2->next();
        }

        if (ifHasBracket)
        {
            if (tok2->str() != "}")
            {
                err = false;
            }
        }

        if (err)
        {
            redundantIfDelete0Error(tok);
        }
    }



    // Redundant condition
    // if (haystack.find(needle) != haystack.end())
    //    haystack.remove(needle);
    redundantCondition2();
}
//---------------------------------------------------------------------------

void CheckOther::redundantCondition2()
{
    const char pattern[] = "if ( %var% . find ( %any% ) != %var% . end ( ) ) "
                           "{|{|"
                           "    %var% . remove ( %any% ) ; "
                           "}|}|";
    const Token *tok = Token::findmatch(_tokenizer->tokens(), pattern);
    while (tok)
    {
        bool b(tok->tokAt(15)->str() == "{");

        // Get tokens for the fields %var% and %any%
        const Token *var1 = tok->tokAt(2);
        const Token *any1 = tok->tokAt(6);
        const Token *var2 = tok->tokAt(9);
        const Token *var3 = tok->tokAt(b ? 16 : 15);
        const Token *any2 = tok->tokAt(b ? 20 : 19);

        // Check if all the "%var%" fields are the same and if all the "%any%" are the same..
        if (var1->str() == var2->str() &&
            var2->str() == var3->str() &&
            any1->str() == any2->str())
        {
            redundantIfRemoveError(tok);
        }

        tok = Token::findmatch(tok->next(), pattern);
    }
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
// if (condition) ....
//---------------------------------------------------------------------------

void CheckOther::warningIf()
{
    if (ErrorLogger::ifNoAction(*_settings))
    {
        // Search for 'if (condition);'
        for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
        {
            if (!Token::simpleMatch(tok, "if ("))
                continue;

            // Search for the end paranthesis for the condition..
            int parlevel = 0;
            for (const Token *tok2 = tok->next(); tok2; tok2 = tok2->next())
            {
                if (tok2->str() == "(")
                    ++parlevel;
                else if (tok2->str() == ")")
                {
                    --parlevel;
                    if (parlevel <= 0)
                    {
                        if (Token::Match(tok2, ") ; !!else"))
                        {
                            ifNoActionError(tok);
                        }
                        break;
                    }
                }
            }
        }
    }

    if (_settings->_checkCodingStyle)
    {
        // Search for 'a=b; if (a==b)'
        for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
        {
            // Begin statement?
            if (! Token::Match(tok, "[;{}]"))
                continue;
            tok = tok->next();
            if (! tok)
                break;

            if (!Token::Match(tok, "%var% = %var% ; if ( %var%"))
                continue;

            if (strcmp(tok->strAt(9), ")") != 0)
                continue;

            // var1 = var2 ; if ( var3 cond var4 )
            unsigned int var1 = tok->tokAt(0)->varId();
            unsigned int var2 = tok->tokAt(2)->varId();
            unsigned int var3 = tok->tokAt(6)->varId();
            const char *cond = tok->strAt(7);
            unsigned int var4 = tok->tokAt(8)->varId();

            if (var1 == 0 || var2 == 0 || var3 == 0 || var4 == 0)
                continue;

            if (var1 == var2 || var3 == var4)
                continue;

            // Check that var3 is equal with either var1 or var2
            if (var1 != var3 && var2 != var3)
                continue;

            // Check that var4 is equal with either var1 or var2
            if (var1 != var4 && var2 != var4)
                continue;

            // Check that there is a condition..
            static const char * const p[6] = {"==", "<=", ">=", "!=", "<", ">"};
            bool iscond = false;
            for (int i = 0; i < 6; i++)
            {
                if (strcmp(cond, p[i]) == 0)
                {
                    iscond = true;
                    break;
                }
            }
            if (!iscond)
                continue;

            // If there are casting involved it's hard to know if the
            // condition is true or false
            const Token *vardecl1 = Token::findmatch(_tokenizer->tokens(), "; %type% %varid% ;", var1);
            if (!vardecl1)
                continue;
            const Token *vardecl2 = Token::findmatch(_tokenizer->tokens(), "; %type% %varid% ;", var2);
            if (!vardecl2)
                continue;

            // variable 1 & 2 must be the same type..
            if (vardecl1->next()->str() != vardecl2->next()->str())
                continue;

            // we found the error. Report.
            bool b = false;
            for (int i = 0; i < 6; i++)
            {
                if (strcmp(cond, p[i]) == 0)
                    b = (i < 3);
            }
            conditionAlwaysTrueFalse(tok->tokAt(4), b ? "True" : "False");
        }
    }
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
// strtol(str, 0, radix)  <- radix must be 0 or 2-36
//---------------------------------------------------------------------------

void CheckOther::invalidFunctionUsage()
{
    // strtol and strtoul..
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if ((tok->str() != "strtol") && (tok->str() != "strtoul"))
            continue;

        // Locate the third parameter of the function call..
        int parlevel = 0;
        int param = 1;
        for (const Token *tok2 = tok->next(); tok2; tok2 = tok2->next())
        {
            if (tok2->str() == "(")
                ++parlevel;
            else if (tok2->str() == ")")
                --parlevel;
            else if (parlevel == 1 && tok2->str() == ",")
            {
                ++param;
                if (param == 3)
                {
                    if (Token::Match(tok2, ", %num% )"))
                    {
                        int radix = MathLib::toLongNumber(tok2->next()->str());
                        if (!(radix == 0 || (radix >= 2 && radix <= 36)))
                        {
                            dangerousUsageStrtolError(tok2);
                        }
                    }
                    break;
                }
            }
        }
    }

    // sprintf|snprintf overlapping data
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        // Get variable id of target buffer..
        unsigned int varid = 0;

        if (Token::Match(tok, "sprintf|snprintf ( %var% ,"))
            varid = tok->tokAt(2)->varId();

        else if (Token::Match(tok, "sprintf|snprintf ( %var% . %var% ,"))
            varid = tok->tokAt(4)->varId();

        if (varid == 0)
            continue;

        // goto ","
        const Token *tok2 = tok->tokAt(3);
        while (tok2 && tok2->str() != ",")
            tok2 = tok2->next();

        // is any source buffer overlapping the target buffer?
        int parlevel = 0;
        while ((tok2 = tok2->next()) != NULL)
        {
            if (tok2->str() == "(")
                ++parlevel;
            else if (tok2->str() == ")")
            {
                --parlevel;
                if (parlevel < 0)
                    break;
            }
            else if (parlevel == 0 && Token::Match(tok2, ", %varid% [,)]", varid))
            {
                sprintfOverlappingDataError(tok2->next(), tok2->next()->str());
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Check for unsigned divisions
//---------------------------------------------------------------------------

void CheckOther::checkUnsignedDivision()
{
    if (!_settings->_showAll || !_settings->_checkCodingStyle)
        return;

    // Check for "ivar / uvar" and "uvar / ivar"
    std::map<std::string, char> varsign;
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (Token::Match(tok, "[{};(,] %type% %var% [;=,)]"))
        {
            const char *type = tok->strAt(1);
            if (strcmp(type, "char") == 0 || strcmp(type, "short") == 0 || strcmp(type, "int") == 0)
                varsign[tok->strAt(2)] = 's';
        }

        else if (Token::Match(tok, "[{};(,] unsigned %type% %var% [;=,)]"))
            varsign[tok->strAt(3)] = 'u';

        else if (!Token::Match(tok, "[).]") && Token::Match(tok->next(), "%var% / %var%"))
        {
            if (ErrorLogger::udivWarning(*_settings))
            {
                const char *varname1 = tok->strAt(1);
                const char *varname2 = tok->strAt(3);
                char sign1 = varsign[varname1];
                char sign2 = varsign[varname2];

                if (sign1 && sign2 && sign1 != sign2)
                {
                    // One of the operands are signed, the other is unsigned..
                    udivWarning(tok->next());
                }
            }
        }

        else if (!Token::Match(tok, "[).]") && Token::Match(tok->next(), "%var% / %num%"))
        {
            if (tok->strAt(3)[0] == '-' && ErrorLogger::udivError())
            {
                const char *varname1 = tok->strAt(1);
                char sign1 = varsign[varname1];
                if (sign1 == 'u')
                {
                    udivError(tok->next());
                }
            }
        }

        else if (Token::Match(tok, "[([=*/+-,] %num% / %var%"))
        {
            if (tok->strAt(1)[0] == '-' && ErrorLogger::udivError())
            {
                const char *varname2 = tok->strAt(3);
                char sign2 = varsign[varname2];
                if (sign2 == 'u')
                {
                    udivError(tok->next());
                }
            }
        }
    }
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// Check scope of variables..
//---------------------------------------------------------------------------

void CheckOther::checkVariableScope()
{
    // Walk through all tokens..
    bool func = false;
    int indentlevel = 0;
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        // Skip class and struct declarations..
        if ((tok->str() == "class") || (tok->str() == "struct"))
        {
            for (const Token *tok2 = tok; tok2; tok2 = tok2->next())
            {
                if (tok2->str() == "{")
                {
                    int indentlevel2 = 0;
                    for (tok = tok2; tok; tok = tok->next())
                    {
                        if (tok->str() == "{")
                        {
                            ++indentlevel2;
                        }
                        if (tok->str() == "}")
                        {
                            --indentlevel2;
                            if (indentlevel2 <= 0)
                            {
                                tok = tok->next();
                                break;
                            }
                        }
                    }
                    break;
                }
                if (Token::Match(tok2, "[,);]"))
                {
                    break;
                }
            }
            if (! tok)
                break;
        }

        if (tok->str() == "{")
        {
            ++indentlevel;
        }
        if (tok->str() == "}")
        {
            --indentlevel;
            if (indentlevel == 0)
                func = false;
        }
        if (indentlevel == 0 && Token::simpleMatch(tok, ") {"))
        {
            func = true;
        }
        if (indentlevel > 0 && func && Token::Match(tok, "[{};]"))
        {
            // First token of statement..
            const Token *tok1 = tok->next();
            if (! tok1)
                continue;

            if ((tok1->str() == "return") ||
                (tok1->str() == "throw") ||
                (tok1->str() == "delete") ||
                (tok1->str() == "goto") ||
                (tok1->str() == "else"))
                continue;

            // Variable declaration?
            if (Token::Match(tok1, "%type% %var% ; %var% = %num% ;"))
            {
                // Tokenizer modify "int i = 0;" to "int i; i = 0;",
                // so to handle this situation we just skip
                // initialization (see ticket #272).
                const unsigned int firstVarId = tok1->next()->varId();
                const unsigned int secondVarId = tok1->tokAt(3)->varId();
                if (firstVarId > 0 && firstVarId == secondVarId)
                {
                    lookupVar(tok1->tokAt(6), tok1->strAt(1));
                }
            }
            else if (Token::Match(tok1, "%type% %var% [;=]"))
            {
                lookupVar(tok1, tok1->strAt(1));
            }
        }
    }

}
//---------------------------------------------------------------------------

void CheckOther::lookupVar(const Token *tok1, const char varname[])
{
    const Token *tok = tok1;

    // Skip the variable declaration..
    while (tok && tok->str() != ";")
        tok = tok->next();

    // Check if the variable is used in this indentlevel..
    bool used = false, used1 = false;
    int indentlevel = 0;
    int parlevel = 0;
    bool for_or_while = false;
    while (tok)
    {
        if (tok->str() == "{")
        {
            ++indentlevel;
        }

        else if (tok->str() == "}")
        {
            if (indentlevel == 0)
                break;
            --indentlevel;
            if (indentlevel == 0)
            {
                if (for_or_while && used)
                    return;
                used1 |= used;
                used = false;
            }
        }

        else if (tok->str() == "(")
        {
            ++parlevel;
        }

        else if (tok->str() == ")")
        {
            --parlevel;
        }

        // Bail out if references are used
        else if (Token::simpleMatch(tok, (std::string("& ") + varname).c_str()))
        {
            return;
        }

        else if (tok->str() == varname)
        {
            if (indentlevel == 0 || used1)
                return;
            used = true;
        }

        else if (indentlevel == 0)
        {
            if ((tok->str() == "for") || (tok->str() == "while"))
                for_or_while = true;
            if (parlevel == 0 && (tok->str() == ";"))
                for_or_while = false;
        }

        tok = tok->next();
    }

    // Warning if this variable:
    // * not used in this indentlevel
    // * used in lower indentlevel
    if (!used && used1)
        variableScopeError(tok1, varname);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Check for constant function parameters
//---------------------------------------------------------------------------

void CheckOther::checkConstantFunctionParameter()
{
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (Token::Match(tok, "[,(] const std :: %type% %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(5));
        }

        else if (Token::Match(tok, "[,(] const %type% %var% [,)]"))
        {
            // Check if type is a struct or class.
            const std::string pattern(std::string("class|struct ") + tok->strAt(2));
            if (Token::findmatch(_tokenizer->tokens(), pattern.c_str()))
            {
                passedByValueError(tok, tok->strAt(3));
            }
        }
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Check that all struct members are used
//---------------------------------------------------------------------------

void CheckOther::checkStructMemberUsage()
{
    const char *structname = 0;
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (tok->fileIndex() != 0)
            continue;

        if (Token::Match(tok, "struct|union %type% {"))
        {
            structname = tok->strAt(1);

            // Bail out if struct/union contain any functions
            for (const Token *tok2 = tok->tokAt(2); tok2; tok2 = tok2->next())
            {
                if (tok2->str() == "(")
                {
                    structname = 0;
                    break;
                }

                if (tok2->str() == "}")
                    break;
            }
        }

        if (tok->str() == "}")
            structname = 0;

        if (structname && Token::Match(tok, "[{;]"))
        {
            const char *varname = 0;
            if (Token::Match(tok->next(), "%type% %var% [;[]"))
                varname = tok->strAt(2);
            else if (Token::Match(tok->next(), "%type% %type% %var% [;[]"))
                varname = tok->strAt(3);
            else if (Token::Match(tok->next(), "%type% * %var% [;[]"))
                varname = tok->strAt(3);
            else if (Token::Match(tok->next(), "%type% %type% * %var% [;[]"))
                varname = tok->strAt(4);
            else
                continue;

            const std::string usagePattern(". " + std::string(varname));
            bool used = false;
            for (const Token *tok2 = _tokenizer->tokens(); tok2; tok2 = tok2->next())
            {
                if (Token::simpleMatch(tok2, usagePattern.c_str()))
                {
                    used = true;
                    break;
                }
            }

            if (! used)
            {
                unusedStructMemberError(tok->next(), structname, varname);
            }
        }
    }
}





//---------------------------------------------------------------------------
// Check usage of char variables..
//---------------------------------------------------------------------------

void CheckOther::checkCharVariable()
{
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        // Declaring the variable..
        if (Token::Match(tok, "[{};(,] signed| char %var% [;=,)]"))
        {
            // Set tok to point to the variable name
            tok = tok->tokAt(2);
            if (tok->str() == "char")
                tok = tok->next();

            // Check usage of char variable..
            int indentlevel = 0;
            for (const Token *tok2 = tok->next(); tok2; tok2 = tok2->next())
            {
                if (tok2->str() == "{")
                    ++indentlevel;

                else if (tok2->str() == "}")
                {
                    --indentlevel;
                    if (indentlevel <= 0)
                        break;
                }

                else if (tok2->str() == "return")
                    continue;

                std::string temp = "%var% [ " + tok->str() + " ]";
                if ((tok2->str() != ".") && Token::Match(tok2->next(), temp.c_str()))
                {
                    charArrayIndexError(tok2->next());
                    break;
                }

                if (Token::Match(tok2, "[;{}] %var% = %any% [&|] %any% ;"))
                {
                    // is the char variable used in the calculation?
                    if (tok2->tokAt(3)->varId() != tok->varId() && tok2->tokAt(5)->varId() != tok->varId())
                        continue;

                    // it's ok with a bitwise and where the other operand is 0xff or less..
                    if (std::string(tok2->strAt(4)) == "&")
                    {
                        if (tok2->tokAt(3)->isNumber() && MathLib::isGreater("0x100", tok2->strAt(3)))
                            continue;
                        if (tok2->tokAt(5)->isNumber() && MathLib::isGreater("0x100", tok2->strAt(5)))
                            continue;
                    }

                    // is the result stored in a short|int|long?
                    if (!Token::findmatch(_tokenizer->tokens(), "short|int|long %varid%", tok2->next()->varId()))
                        continue;

                    // This is an error..
                    charBitOpError(tok2);
                    break;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
// Incomplete statement..
//---------------------------------------------------------------------------

void CheckOther::checkIncompleteStatement()
{
    int parlevel = 0;

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (tok->str() == "(")
            ++parlevel;
        else if (tok->str() == ")")
            --parlevel;

        if (parlevel != 0)
            continue;

        if (Token::simpleMatch(tok, "= {"))
        {
            /* We are in an assignment, so it's not a statement.
             * Skip until ";" */

            while (tok->str() != ";")
            {
                int level = 0;
                do
                {
                    if (tok->str() == "(" || tok->str() == "{")
                        ++level;
                    else if (tok->str() == ")" || tok->str() == "}")
                        --level;

                    tok = tok->next();

                    if (tok == NULL)
                        return;
                }
                while (level > 0);
            }

            continue;
        }

        if (Token::Match(tok, "[;{}] %str%") && !Token::Match(tok->tokAt(2), "[,}]"))
        {
            constStatementError(tok->next(), "string");
        }

        if (Token::Match(tok, "[;{}] %num%") && !Token::Match(tok->tokAt(2), "[,}]"))
        {
            constStatementError(tok->next(), "numeric");
        }
    }
}
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
// str plus char
//---------------------------------------------------------------------------

void CheckOther::strPlusChar()
{
    bool charVars[10000] = {0};

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        // Declaring char variable..
        if (Token::Match(tok, "char %var% [;=]"))
        {
            unsigned int varid = tok->next()->varId();
            if (varid > 0 && varid < 10000)
                charVars[varid] = true;
        }

        //
        else if (Token::Match(tok, "[=(] %str% + %any%"))
        {
            // char constant..
            const char *s = tok->strAt(3);
            if (*s == '\'')
                strPlusChar(tok->next());

            // char variable..
            unsigned int varid = tok->tokAt(3)->varId();
            if (varid > 0 && varid < 10000 && charVars[varid])
                strPlusChar(tok->next());
        }
    }
}





void CheckOther::nullPointer()
{
    // Locate insufficient null-pointer handling after loop
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (! Token::Match(tok, "while ( %var% )"))
            continue;

        const unsigned int varid(tok->tokAt(2)->varId());
        if (varid == 0)
            continue;

        const std::string varname(tok->strAt(2));

        // Locate the end of the while loop..
        const Token *tok2 = tok->tokAt(4);
        if (tok2->str() == "{")
            tok2 = tok2->link();
        else
        {
            while (tok2 && tok2->str() != ";")
                tok2 = tok2->next();
        }

        // Goto next token
        if (tok2)
            tok2 = tok2->next();

        // Check if the variable is dereferenced..
        while (tok2)
        {
            if (tok2->str() == "{" || tok2->str() == "}")
                break;

            if (tok2->varId() == varid)
            {
                if (tok2->next()->str() == "." || Token::Match(tok2->next(), "= %varid% .", varid))
                {
                    // Is this variable a pointer?
                    const Token *tok3 = Token::findmatch(_tokenizer->tokens(), "%type% * %varid% [;)]", varid);
                    if (!tok3)
                        break;

                    if (!tok3->previous() ||
                        Token::Match(tok3->previous(), "[({};]") ||
                        tok3->previous()->isName())
                    {
                        nullPointerError(tok2, varname);
                    }
                }
                break;
            }

            tok2 = tok2->next();
        }
    }

    // looping through items in a linked list in a inner loop..
    for (const Token *tok1 = _tokenizer->tokens(); tok1; tok1 = tok1->next())
    {
        // search for a "for" token..
        if (!Token::simpleMatch(tok1, "for ("))
            continue;

        if (!Token::simpleMatch(tok1->next()->link(), ") {"))
            continue;

        // is there any dereferencing occuring in the for statement..
        unsigned int parlevel2 = 1;
        for (const Token *tok2 = tok1->tokAt(2); tok2; tok2 = tok2->next())
        {
            // Parantheses..
            if (tok2->str() == "(")
                ++parlevel2;
            else if (tok2->str() == ")")
            {
                if (parlevel2 <= 1)
                    break;
                --parlevel2;
            }

            // Dereferencing a variable inside the "for" parantheses..
            else if (Token::Match(tok2, "%var% . %var%"))
            {
                const unsigned int varid(tok2->varId());
                if (varid == 0)
                    continue;

                if (Token::Match(tok2->tokAt(-2), "%varid% ?", varid))
                    continue;

                const std::string varname(tok2->str());

                // Check usage of dereferenced variable in the loop..
                unsigned int indentlevel3 = 0;
                for (const Token *tok3 = tok1->next()->link(); tok3; tok3 = tok3->next())
                {
                    if (tok3->str() == "{")
                        ++indentlevel3;
                    else if (tok3->str() == "}")
                    {
                        if (indentlevel3 <= 1)
                            break;
                        --indentlevel3;
                    }
                    else if (Token::Match(tok3, "while ( %varid% &&|)", varid))
                    {
                        // Make sure there is a "break" to prevent segmentation faults..
                        unsigned int indentlevel4 = indentlevel3;
                        for (const Token *tok4 = tok3; tok4; tok4 = tok4->next())
                        {
                            if (tok4->str() == "{")
                                ++indentlevel4;
                            else if (tok4->str() == "}")
                            {
                                if (indentlevel4 <= 1)
                                {
                                    nullPointerError(tok1, varname);
                                    break;
                                }
                                --indentlevel4;
                            }
                            else if (tok4->str() == "break")
                                break;
                        }
                    }
                }
            }
        }
    }

    // Dereferencing a struct pointer and then checking if it's NULL..
    for (const Token *tok1 = _tokenizer->tokens(); tok1; tok1 = tok1->next())
    {
        if (Token::Match(tok1, "[{};] %var% = %var% . %var%"))
        {
            if (std::string(tok1->strAt(1)) == tok1->strAt(3))
                continue;

            tok1 = tok1->tokAt(3);
            const unsigned int varid1(tok1->varId());
            if (varid1 == 0)
                continue;

            const std::string varname(tok1->str());

            // Checking if the struct pointer is non-null before the assignment..
            {
                const Token *tok2 = _tokenizer->tokens();
                while (tok2)
                {
                    if (tok2 == tok1)
                        break;
                    if (Token::Match(tok2, "if|while ( !| %varid% )", varid1))
                        break;
                    tok2 = tok2->next();
                }
                if (tok2 != tok1)
                    continue;
            }

            unsigned int indentlevel2 = 0;
            for (const Token *tok2 = tok1->tokAt(3); tok2; tok2 = tok2->next())
            {
                if (tok2->str() == "{")
                    ++indentlevel2;

                else if (tok2->str() == "}")
                {
                    if (indentlevel2 == 0)
                        break;
                    --indentlevel2;
                }

                // goto destination..
                else if (tok2->isName() && Token::simpleMatch(tok2->next(), ":"))
                    break;

                // Reassignment of the struct
                else if (tok2->varId() == varid1)
                {
                    if (tok2->next()->str() == "=")
                        break;
                    if (Token::Match(tok2->tokAt(-2), "[,(] &"))
                        break;
                }

                // Loop..
                /** @todo don't bail out if the variable is not used in the loop */
                else if (tok2->str() == "do")
                    break;

                // return at base level => stop checking
                else if (indentlevel2 == 0 && tok2->str() == "return")
                    break;

                else if (Token::Match(tok2, "if ( !| %varid% )", varid1))
                {
                    nullPointerError(tok1, varname, tok2->linenr());
                    break;
                }
            }
        }
    }

    // Dereferencing a pointer and then checking if it's NULL..
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (tok->str() == "if" && Token::Match(tok->previous(), "; if ( ! %var% )"))
        {
            const unsigned int varid(tok->tokAt(3)->varId());
            if (varid == 0)
                continue;

            const std::string varname(tok->strAt(3));

            const Token *decltok = Token::findmatch(_tokenizer->tokens(), "%varid%", varid);
            if (!Token::Match(decltok->tokAt(-3), "[;,(] %var% *"))
                continue;

            for (const Token *tok1 = tok->previous(); tok1 && tok1 != decltok; tok1 = tok1->previous())
            {
                if (tok1->varId() == varid)
                {
                    if (Token::Match(tok1->tokAt(-2), "[=;{}] *"))
                    {
                        nullPointerError(tok1, varname);
                        break;
                    }
                    else if (tok1->previous() && tok1->previous()->str() == "&")
                    {
                        break;
                    }
                    else if (tok1->next() && tok1->next()->str() == "=")
                    {
                        break;
                    }
                }

                else if (tok1->str() == "{" ||
                         tok1->str() == "}")
                    break;

                // goto destination..
                else if (tok1->isName() && Token::simpleMatch(tok1->next(), ":"))
                    break;
            }
        }
    }
}



void CheckOther::checkZeroDivision()
{
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {

        if (Token::Match(tok, "/ %num%") &&
            MathLib::isInt(tok->next()->str()) &&
            MathLib::toLongNumber(tok->next()->str()) == 0L)
        {
            zerodivError(tok);
        }
        else if (Token::Match(tok, "div|ldiv|lldiv|imaxdiv ( %num% , %num% )") &&
                 MathLib::isInt(tok->tokAt(4)->str()) &&
                 MathLib::toLongNumber(tok->tokAt(4)->str()) == 0L)
        {
            zerodivError(tok);
        }
    }
}



void CheckOther::postIncrement()
{
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (Token::simpleMatch(tok, "for ("))
        {
            const Token *tok2 = tok->next()->link();
            if (tok2)
                tok2 = tok2->tokAt(-3);
            if (Token::Match(tok2, "; %var% ++|-- )"))
            {
                if (tok2->next()->varId() == 0)
                    continue;

                // Take a look at the variable declaration
                const Token *decltok = Token::findmatch(_tokenizer->tokens(), "%varid%", tok2->tokAt(1)->varId());
                const std::string classDef = std::string("class ") + std::string(decltok->previous()->strAt(0));

                // Is the variable an iterator?
                if (decltok && Token::Match(decltok->previous(), "iterator|const_iterator"))
                    postIncrementError(tok2, tok2->strAt(1), (std::string("++") == tok2->strAt(2)));
                // Is the variable a class?
                else if (Token::findmatch(_tokenizer->tokens(), classDef.c_str()))
                    postIncrementError(tok2, tok2->strAt(1), (std::string("++") == tok2->strAt(2)));

                break;
            }
        }
    }
}




void CheckOther::cstyleCastError(const Token *tok)
{
    reportError(tok, Severity::style, "cstyleCast", "C-style pointer casting");
}

void CheckOther::redundantIfDelete0Error(const Token *tok)
{
    reportError(tok, Severity::style, "redundantIfDelete0", "Redundant condition. It is safe to deallocate a NULL pointer");
}

void CheckOther::redundantIfRemoveError(const Token *tok)
{
    reportError(tok, Severity::style, "redundantIfRemove", "Redundant condition. The remove function in the STL will not do anything if element doesn't exist");
}

void CheckOther::dangerousUsageStrtolError(const Token *tok)
{
    reportError(tok, Severity::error, "dangerousUsageStrtol", "Invalid radix in call to strtol or strtoul. Must be 0 or 2-36");
}

void CheckOther::ifNoActionError(const Token *tok)
{
    reportError(tok, Severity::style, "ifNoAction", "Found redundant if condition - 'if (condition);'");
}

void CheckOther::sprintfOverlappingDataError(const Token *tok, const std::string &varname)
{
    reportError(tok, Severity::error, "sprintfOverlappingData", "Overlapping data buffer " + varname + "\nWhen using sprintf the same buffer must not be used both for output and input. The behaviour is undefined when that happens.\nFor example: 'sprintf(str,\"<%s>\",str);'");
}

void CheckOther::udivError(const Token *tok)
{
    reportError(tok, Severity::error, "udivError", "Unsigned division. The result will be wrong.");
}

void CheckOther::udivWarning(const Token *tok)
{
    reportError(tok, Severity::possibleStyle, "udivWarning", "Division with signed and unsigned operators");
}

void CheckOther::unusedStructMemberError(const Token *tok, const std::string &structname, const std::string &varname)
{
    reportError(tok, Severity::style, "unusedStructMember", "struct or union member '" + structname + "::" + varname + "' is never used");
}

void CheckOther::passedByValueError(const Token *tok, const std::string &parname)
{
    reportError(tok, Severity::style, "passedByValue", "Function parameter '" + parname + "' is passed by value. It could be passed by reference instead.");
}

void CheckOther::constStatementError(const Token *tok, const std::string &type)
{
    reportError(tok, Severity::style, "constStatement", "Redundant code: Found a statement that begins with " + type + " constant");
}

void CheckOther::charArrayIndexError(const Token *tok)
{
    reportError(tok, Severity::style, "charArrayIndex", "Warning - using char variable as array index");
}

void CheckOther::charBitOpError(const Token *tok)
{
    reportError(tok, Severity::style, "charBitOp", "Warning - using char variable in bit operation");
}

void CheckOther::variableScopeError(const Token *tok, const std::string &varname)
{
    reportError(tok, Severity::style, "variableScope", "The scope of the variable " + varname + " can be limited");
}

void CheckOther::conditionAlwaysTrueFalse(const Token *tok, const std::string &truefalse)
{
    reportError(tok, Severity::style, "conditionAlwaysTrueFalse", "Condition is always " + truefalse);
}

void CheckOther::strPlusChar(const Token *tok)
{
    reportError(tok, Severity::error, "strPlusChar", "Unusual pointer arithmetic");
}

void CheckOther::nullPointerError(const Token *tok, const std::string &varname)
{
    reportError(tok, Severity::error, "nullPointer", "Possible null pointer dereference: " + varname);
}

void CheckOther::nullPointerError(const Token *tok, const std::string &varname, const int line)
{
    reportError(tok, Severity::error, "nullPointer", "Possible null pointer dereference: " + varname + " - otherwise it is redundant to check if " + varname + " is null at line " + MathLib::toString<long>(line));
}

void CheckOther::zerodivError(const Token *tok)
{
    reportError(tok, Severity::error, "zerodiv", "Division by zero");
}

void CheckOther::postIncrementError(const Token *tok, const std::string &var_name, const bool isIncrement)
{
    std::string type = (isIncrement ? "Incrementing" : "Decrementing");
    reportError(tok, Severity::possibleStyle, "postIncrementDecrement", ("Pre-" + type + " variable '" + var_name + "' is preferred to Post-" + type));
}
