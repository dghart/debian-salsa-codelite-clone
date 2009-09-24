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
#ifndef CheckOtherH
#define CheckOtherH
//---------------------------------------------------------------------------

#include "check.h"
#include "settings.h"

class Token;

/// @addtogroup Checks
/// @{

class CheckOther : public Check
{
public:
    /** This constructor is used when registering the CheckClass */
    CheckOther() : Check()
    { }

    /** This constructor is used when running checks.. */
    CheckOther(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
            : Check(tokenizer, settings, errorLogger)
    { }


    void runChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
    {
        CheckOther checkOther(tokenizer, settings, errorLogger);

        if (settings->_checkCodingStyle)
        {
            checkOther.warningOldStylePointerCast();
            checkOther.checkUnsignedDivision();
            checkOther.checkCharVariable();
            checkOther.nullPointer();
        }
    }

    void runSimplifiedChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
    {
        CheckOther checkOther(tokenizer, settings, errorLogger);

        if (settings->_checkCodingStyle)
        {
            checkOther.warningRedundantCode();
            checkOther.warningIf();
            checkOther.checkVariableScope();
            checkOther.checkConstantFunctionParameter();
            checkOther.checkStructMemberUsage();
            checkOther.checkIncompleteStatement();
            if (settings->_showAll)
            {
                checkOther.postIncrement();
            }
        }

        checkOther.strPlusChar();
        checkOther.invalidFunctionUsage();
        checkOther.checkZeroDivision();
    }

    // Casting
    void warningOldStylePointerCast();

    // Redundant code
    void warningRedundantCode();

    // Warning upon: if (condition);
    void warningIf();

    // Invalid function usage..
    void invalidFunctionUsage();

    // Check for unsigned division that might create bad results
    void checkUnsignedDivision();

    // Check scope of variables
    void checkVariableScope();

    // Check for constant function parameter
    void checkConstantFunctionParameter();

    // Check that all struct members are used
    void checkStructMemberUsage();

    // Using char variable as array index / as operand in bit operation
    void checkCharVariable();

    // Incomplete statement. A statement that only contains a constant or variable
    void checkIncompleteStatement();

    /** str plus char */
    void strPlusChar();

    /** possible null pointer dereference */
    void nullPointer();

    /** Check zero division*/
    void checkZeroDivision();

    /** Check for post increment/decrement in for loop*/
    void postIncrement();

    void lookupVar(const Token *tok1, const char varname[]);

    // Redundant condition
    // if (haystack.find(needle) != haystack.end())
    //    haystack.remove(needle);
    void redundantCondition2();

    // Error messages..
    void cstyleCastError(const Token *tok);
    void redundantIfDelete0Error(const Token *tok);
    void redundantIfRemoveError(const Token *tok);
    void dangerousUsageStrtolError(const Token *tok);
    void ifNoActionError(const Token *tok);
    void sprintfOverlappingDataError(const Token *tok, const std::string &varname);
    void udivError(const Token *tok);
    void udivWarning(const Token *tok);
    void unusedStructMemberError(const Token *tok, const std::string &structname, const std::string &varname);
    void passedByValueError(const Token *tok, const std::string &parname);
    void constStatementError(const Token *tok, const std::string &type);
    void charArrayIndexError(const Token *tok);
    void charBitOpError(const Token *tok);
    void variableScopeError(const Token *tok, const std::string &varname);
    void conditionAlwaysTrueFalse(const Token *tok, const std::string &truefalse);
    void strPlusChar(const Token *tok);
    void nullPointerError(const Token *tok, const std::string &varname);
    void nullPointerError(const Token *tok, const std::string &varname, const int line);
    void zerodivError(const Token *tok);
    void postIncrementError(const Token *tok, const std::string &var_name, const bool isIncrement);

    void getErrorMessages()
    {
        cstyleCastError(0);
        redundantIfDelete0Error(0);
        redundantIfRemoveError(0);
        dangerousUsageStrtolError(0);
        ifNoActionError(0);
        sprintfOverlappingDataError(0, "varname");
        udivError(0);
        udivWarning(0);
        unusedStructMemberError(0, "structname", "variable");
        passedByValueError(0, "parametername");
        constStatementError(0, "type");
        charArrayIndexError(0);
        charBitOpError(0);
        variableScopeError(0, "varname");
        conditionAlwaysTrueFalse(0, "true/false");
        strPlusChar(0);
        nullPointerError(0, "pointer");
        zerodivError(0);
        postIncrementError(0, "varname", true);
    }

    std::string name() const
    {
        return "Other";
    }

    std::string classInfo() const
    {
        return "Other checks\n"
               " * C-style pointer cast in cpp file\n"
               " * redundant if\n"
               " * bad usage of the function 'strtol'\n"
               " * [[OverlappingData|bad usage of the function 'sprintf' (overlapping data)]]\n"
               " * division with zero\n"
               " * [[CheckUnsignedDivision|unsigned division]]\n"
               " * unused struct member\n"
               " * passing parameter by value\n"
               " * [[charvar|check how signed char variables are used]]\n"
               " * condition that is always true/false\n"
               " * unusal pointer arithmetic. For example: \"abc\" + 'd'\n"
               " * dereferencing a null pointer\n"
               " * [[IncompleteStatement|Incomplete statement]]\n";
    }
};
/// @}
//---------------------------------------------------------------------------
#endif

