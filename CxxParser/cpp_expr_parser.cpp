#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define yyparse cl_expr_parse
#define yylex cl_expr_lex
#define yyerror cl_expr_error
#define yychar cl_expr_char
#define yyval cl_expr_val
#define yylval cl_expr_lval
#define yydebug cl_expr_debug
#define yynerrs cl_expr_nerrs
#define yyerrflag cl_expr_errflag
#define yyss cl_expr_ss
#define yyssp cl_expr_ssp
#define yyvs cl_expr_vs
#define yyvsp cl_expr_vsp
#define yylhs cl_expr_lhs
#define yylen cl_expr_len
#define yydefred cl_expr_defred
#define yydgoto cl_expr_dgoto
#define yysindex cl_expr_sindex
#define yyrindex cl_expr_rindex
#define yygindex cl_expr_gindex
#define yytable cl_expr_table
#define yycheck cl_expr_check
#define yyname cl_expr_name
#define yyrule cl_expr_rule
#define YYPREFIX "cl_expr_"
/* Copyright Eran Ifrah(c)*/
/*************** Includes and Defines *****************************/
#include "string"
#include "vector"
#include "stdio.h"
#include "map"
#include "expression_result.h"

#define YYSTYPE std::string
#define YYDEBUG 0        /* get the pretty debugging code to compile*/

void cl_expr_error(char *string);

static ExpressionResult result;

/*---------------------------------------------*/
/* externs defined in the lexer*/
/*---------------------------------------------*/
extern char *cl_expr_text;
extern int cl_expr_lex();
extern int cl_expr_parse();
extern int cl_expr_lineno;
extern std::vector<std::string> currentScope;
extern bool setExprLexerInput(const std::string &in);
extern void cl_expr_lex_clean();

/*************** Standard ytab.c continues here *********************/
#define LE_AUTO 257
#define LE_DOUBLE 258
#define LE_INT 259
#define LE_STRUCT 260
#define LE_BREAK 261
#define LE_ELSE 262
#define LE_LONG 263
#define LE_SWITCH 264
#define LE_CASE 265
#define LE_ENUM 266
#define LE_REGISTER 267
#define LE_TYPEDEF 268
#define LE_CHAR 269
#define LE_EXTERN 270
#define LE_RETURN 271
#define LE_UNION 272
#define LE_CONST 273
#define LE_FLOAT 274
#define LE_SHORT 275
#define LE_UNSIGNED 276
#define LE_BOOL 277
#define LE_CONTINUE 278
#define LE_FOR 279
#define LE_SIGNED 280
#define LE_VOID 281
#define LE_DEFAULT 282
#define LE_GOTO 283
#define LE_SIZEOF 284
#define LE_VOLATILE 285
#define LE_DO 286
#define LE_IF 287
#define LE_STATIC 288
#define LE_WHILE 289
#define LE_NEW 290
#define LE_DELETE 291
#define LE_THIS 292
#define LE_OPERATOR 293
#define LE_CLASS 294
#define LE_PUBLIC 295
#define LE_PROTECTED 296
#define LE_PRIVATE 297
#define LE_VIRTUAL 298
#define LE_FRIEND 299
#define LE_INLINE 300
#define LE_OVERLOAD 301
#define LE_TEMPLATE 302
#define LE_TYPENAME 303
#define LE_THROW 304
#define LE_CATCH 305
#define LE_IDENTIFIER 306
#define LE_STRINGliteral 307
#define LE_FLOATINGconstant 308
#define LE_INTEGERconstant 309
#define LE_CHARACTERconstant 310
#define LE_OCTALconstant 311
#define LE_HEXconstant 312
#define LE_POUNDPOUND 313
#define LE_CComment 314
#define LE_CPPComment 315
#define LE_NAMESPACE 316
#define LE_USING 317
#define LE_TYPEDEFname 318
#define LE_ARROW 319
#define LE_ICR 320
#define LE_DECR 321
#define LE_LS 322
#define LE_RS 323
#define LE_LE 324
#define LE_GE 325
#define LE_EQ 326
#define LE_NE 327
#define LE_ANDAND 328
#define LE_OROR 329
#define LE_ELLIPSIS 330
#define LE_CLCL 331
#define LE_DOTstar 332
#define LE_ARROWstar 333
#define LE_MULTassign 334
#define LE_DIVassign 335
#define LE_MODassign 336
#define LE_PLUSassign 337
#define LE_MINUSassign 338
#define LE_LSassign 339
#define LE_RSassign 340
#define LE_ANDassign 341
#define LE_ERassign 342
#define LE_ORassign 343
#define LE_MACRO 344
#define LE_DYNAMIC_CAST 345
#define LE_STATIC_CAST 346
#define LE_CONST_CAST 347
#define LE_REINTERPRET_CAST 348
#define YYERRCODE 256
short cl_expr_lhs[] = {                                        -1,
    0,    0,    3,    1,    1,    4,    4,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    6,    6,    6,
    6,    6,    7,    7,    7,    8,    8,    8,    2,    2,
    2,    2,    2,    2,   14,   15,   15,   16,   16,   12,
   12,   12,   12,   18,   18,   19,   19,   10,   11,   11,
   11,   13,   13,    9,    9,   20,   17,   17,
};
short cl_expr_len[] = {                                         2,
    0,    2,    0,    2,    1,    0,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    2,    2,
    2,    1,    0,    1,    3,    4,    4,    7,    6,    2,
    3,    3,    5,    8,    2,    0,    3,    0,    1,    1,
    1,    1,    1,    0,    1,    0,    2,    2,    0,    1,
    1,    6,    3,    0,    2,    2,    0,    1,
};
short cl_expr_defred[] = {                                      1,
    0,    5,    2,    0,   50,   51,    4,    0,   30,   40,
   41,   42,   43,    0,    0,    0,    0,   54,   31,    0,
   32,    0,    0,   55,   54,    0,    0,   58,   35,   56,
    0,    0,    0,    0,   46,    7,   54,    0,   24,   39,
   33,    0,    0,   53,    0,    0,    0,    0,   37,   29,
    0,   47,   45,   48,    0,   13,    8,    0,    9,   12,
   10,    0,   17,    0,   16,    0,   22,   46,   25,   46,
   34,   21,   20,   11,   15,   14,   18,   19,    0,   26,
   27,   52,    0,   46,   28,
};
short cl_expr_dgoto[] = {                                       1,
    3,    7,    4,   37,   67,   68,   38,   39,   26,   44,
    8,   17,   27,   21,   32,   41,   29,   54,   45,   24,
};
short cl_expr_sindex[] = {                                      0,
 -219,    0,    0,   60,    0,    0,    0,  -17,    0,    0,
    0,    0,    0,   -1, -244, -252,   -3,    0,    0,  -18,
    0,  -87,    6,    0,    0, -245,   34,    0,    0,    0,
 -190,   53,   36,  -58,    0,    0,    0,  -30,    0,    0,
    0,   56, -190,    0,  -26, -207, -189, -190,    0,    0,
  -24,    0,    0,    0,   63,    0,    0, -232,    0,    0,
    0, -135,    0, -135,    0,  -57,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -190,    0,
    0,    0,   -9,    0,    0,
};
short cl_expr_rindex[] = {                                      0,
  -25,    0,    0,  -21,    0,    0,    0, -196,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,
    0,    5,    9,    0,    0,    0,    0,    0,    0,    0,
  -44,   13,    0,  -12,    0,    0,    0,    0,    0,    0,
    0,    0,  -44,    0,  -34,    0,    0, -169,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   14,    0,    0,
    0,   40,    0,   59,    0,   71,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -44,    0,
    0,    0,    0,    0,    0,
};
short cl_expr_gindex[] = {                                      0,
    0,    0,    0,    0,  -40,    0,  -35,   66,    3,   11,
    0,    0,   91,  -10,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 361
short cl_expr_table[] = {                                      23,
   57,   43,   79,   28,   57,   23,   44,   51,   36,   44,
   16,   53,   38,   48,    3,   52,    3,   23,   49,   48,
   49,   77,   14,   78,   15,   46,   72,   44,   46,   46,
   73,   49,    3,    3,   48,   55,    2,   70,   18,   47,
   57,   57,   57,   83,   57,   46,   57,   19,   36,   46,
   36,   11,   84,   22,   38,   11,   25,   11,   57,   57,
   34,   20,   57,   57,   57,   31,   36,   36,   56,   57,
   38,   38,   28,   58,   35,   11,   80,   15,   81,   59,
   82,   15,   36,   15,   60,   61,   62,   63,    6,    6,
   64,   65,   40,    6,   85,   50,   14,   42,   20,    6,
   14,   15,   14,   71,    6,    6,    6,    6,   46,   54,
    6,    6,   46,   69,   46,   33,   66,    6,    5,    0,
   14,    0,   56,   57,    0,    0,    0,   74,    0,    0,
    0,    0,   46,   59,    0,    0,    6,    0,   60,   61,
   75,   63,    0,    0,   76,   65,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    6,    6,    0,    0,    0,    6,    0,
    0,    0,    0,    0,    6,    0,    0,    0,    0,    6,
    6,    6,    6,    0,    0,    6,    6,    0,    0,    0,
    0,    0,    0,   30,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   57,    0,    0,    0,
   57,    6,    0,    0,   36,    0,    3,    0,   38,    0,
   49,   44,   30,   30,    9,    0,    0,    0,    0,    0,
    3,    0,    0,    0,   49,    0,    0,    0,    0,    0,
    0,    0,   57,    0,    0,    0,   57,    0,    0,    0,
   36,    0,    0,    0,   38,    0,   57,    0,    0,    0,
   57,    0,    0,    0,   36,    0,    0,    0,   38,    3,
    3,    3,    3,   49,   49,   49,   49,   10,   11,   12,
   13,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   57,   57,   57,   57,   57,
   57,   57,   57,   36,   36,   36,   36,   38,   38,   38,
   38,
};
short cl_expr_check[] = {                                      44,
    0,   60,   60,   91,    0,   16,   41,   43,    0,   44,
    8,   38,    0,   44,   40,   42,   42,   62,   40,   44,
   42,   62,   40,   64,   42,   38,  259,   62,   41,   42,
  263,   62,   58,   59,   44,   46,  256,   62,   40,   37,
   40,   41,   42,   79,   40,   35,   42,  292,   40,   62,
   42,   38,   62,  306,   42,   42,   60,   44,   58,   59,
  306,  306,   58,   59,   60,   60,   58,   59,  258,  259,
   58,   59,   91,  263,   41,   62,   66,   38,   68,  269,
   70,   42,  273,   44,  274,  275,  276,  277,  258,  259,
  280,  281,   40,  263,   84,   40,   38,   62,  306,  269,
   42,   62,   44,   41,  274,  275,  276,  277,   38,  306,
  280,  281,   42,   48,   44,   25,  306,   58,   59,   -1,
   62,   -1,  258,  259,   -1,   -1,   -1,  263,   -1,   -1,
   -1,   -1,   62,  269,   -1,   -1,  306,   -1,  274,  275,
  276,  277,   -1,   -1,  280,  281,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  258,  259,   -1,   -1,   -1,  263,   -1,
   -1,   -1,   -1,   -1,  269,   -1,   -1,   -1,   -1,  274,
  275,  276,  277,   -1,   -1,  280,  281,   -1,   -1,   -1,
   -1,   -1,   -1,  331,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  256,   -1,   -1,   -1,
  256,  306,   -1,   -1,  256,   -1,  292,   -1,  256,   -1,
  292,  306,  331,  331,  292,   -1,   -1,   -1,   -1,   -1,
  306,   -1,   -1,   -1,  306,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  292,   -1,   -1,   -1,  292,   -1,   -1,   -1,
  292,   -1,   -1,   -1,  292,   -1,  306,   -1,   -1,   -1,
  306,   -1,   -1,   -1,  306,   -1,   -1,   -1,  306,  345,
  346,  347,  348,  345,  346,  347,  348,  345,  346,  347,
  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  345,  346,  347,  348,  345,
  346,  347,  348,  345,  346,  347,  348,  345,  346,  347,
  348,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 348
#if YYDEBUG
char *cl_expr_name[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'&'",0,"'('","')'","'*'",0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",
"'<'",0,"'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"LE_AUTO","LE_DOUBLE","LE_INT","LE_STRUCT","LE_BREAK","LE_ELSE","LE_LONG",
"LE_SWITCH","LE_CASE","LE_ENUM","LE_REGISTER","LE_TYPEDEF","LE_CHAR",
"LE_EXTERN","LE_RETURN","LE_UNION","LE_CONST","LE_FLOAT","LE_SHORT",
"LE_UNSIGNED","LE_BOOL","LE_CONTINUE","LE_FOR","LE_SIGNED","LE_VOID",
"LE_DEFAULT","LE_GOTO","LE_SIZEOF","LE_VOLATILE","LE_DO","LE_IF","LE_STATIC",
"LE_WHILE","LE_NEW","LE_DELETE","LE_THIS","LE_OPERATOR","LE_CLASS","LE_PUBLIC",
"LE_PROTECTED","LE_PRIVATE","LE_VIRTUAL","LE_FRIEND","LE_INLINE","LE_OVERLOAD",
"LE_TEMPLATE","LE_TYPENAME","LE_THROW","LE_CATCH","LE_IDENTIFIER",
"LE_STRINGliteral","LE_FLOATINGconstant","LE_INTEGERconstant",
"LE_CHARACTERconstant","LE_OCTALconstant","LE_HEXconstant","LE_POUNDPOUND",
"LE_CComment","LE_CPPComment","LE_NAMESPACE","LE_USING","LE_TYPEDEFname",
"LE_ARROW","LE_ICR","LE_DECR","LE_LS","LE_RS","LE_LE","LE_GE","LE_EQ","LE_NE",
"LE_ANDAND","LE_OROR","LE_ELLIPSIS","LE_CLCL","LE_DOTstar","LE_ARROWstar",
"LE_MULTassign","LE_DIVassign","LE_MODassign","LE_PLUSassign","LE_MINUSassign",
"LE_LSassign","LE_RSassign","LE_ANDassign","LE_ERassign","LE_ORassign",
"LE_MACRO","LE_DYNAMIC_CAST","LE_STATIC_CAST","LE_CONST_CAST",
"LE_REINTERPRET_CAST",
};
char *cl_expr_rule[] = {
"$accept : translation_unit",
"translation_unit :",
"translation_unit : translation_unit primary_expr",
"$$1 :",
"primary_expr : $$1 simple_expr",
"primary_expr : error",
"const_spec :",
"const_spec : LE_CONST",
"basic_type_name_inter : LE_INT",
"basic_type_name_inter : LE_CHAR",
"basic_type_name_inter : LE_SHORT",
"basic_type_name_inter : LE_LONG",
"basic_type_name_inter : LE_FLOAT",
"basic_type_name_inter : LE_DOUBLE",
"basic_type_name_inter : LE_SIGNED",
"basic_type_name_inter : LE_UNSIGNED",
"basic_type_name_inter : LE_VOID",
"basic_type_name_inter : LE_BOOL",
"basic_type_name : LE_UNSIGNED basic_type_name_inter",
"basic_type_name : LE_SIGNED basic_type_name_inter",
"basic_type_name : LE_LONG LE_LONG",
"basic_type_name : LE_LONG LE_INT",
"basic_type_name : basic_type_name_inter",
"parameter_list :",
"parameter_list : template_parameter",
"parameter_list : parameter_list ',' template_parameter",
"template_parameter : const_spec nested_scope_specifier LE_IDENTIFIER special_star_amp",
"template_parameter : const_spec nested_scope_specifier basic_type_name special_star_amp",
"template_parameter : const_spec nested_scope_specifier LE_IDENTIFIER '<' parameter_list '>' special_star_amp",
"simple_expr : stmnt_starter special_cast '<' cast_type '>' '('",
"simple_expr : stmnt_starter LE_THIS",
"simple_expr : stmnt_starter '*' LE_THIS",
"simple_expr : stmnt_starter '*' identifier_name",
"simple_expr : stmnt_starter nested_scope_specifier identifier_name optional_template_init_list optinal_postifx",
"simple_expr : stmnt_starter '(' '(' cast_type ')' special_star_amp identifier_name ')'",
"identifier_name : LE_IDENTIFIER array_brackets",
"optional_template_init_list :",
"optional_template_init_list : '<' parameter_list '>'",
"optinal_postifx :",
"optinal_postifx : '('",
"special_cast : LE_DYNAMIC_CAST",
"special_cast : LE_STATIC_CAST",
"special_cast : LE_CONST_CAST",
"special_cast : LE_REINTERPRET_CAST",
"amp_item :",
"amp_item : '&'",
"star_list :",
"star_list : star_list '*'",
"special_star_amp : star_list amp_item",
"stmnt_starter :",
"stmnt_starter : ';'",
"stmnt_starter : ':'",
"cast_type : nested_scope_specifier LE_IDENTIFIER '<' parameter_list '>' special_star_amp",
"cast_type : nested_scope_specifier LE_IDENTIFIER special_star_amp",
"nested_scope_specifier :",
"nested_scope_specifier : nested_scope_specifier scope_specifier",
"scope_specifier : LE_IDENTIFIER LE_CLCL",
"array_brackets :",
"array_brackets : '['",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
void yyerror(char *s) {}

void expr_consumBracketsContent(char openBrace)
{
	char closeBrace;

	switch(openBrace) {
	case '(': closeBrace = ')'; break;
	case '[': closeBrace = ']'; break;
	case '<': closeBrace = '>'; break;
	case '{': closeBrace = '}'; break;
	default:
		openBrace = '(';
		closeBrace = ')';
		break;
	}

	int depth = 1;
	while(depth > 0)
	{
		int ch = cl_expr_lex();
		//printf("ch=%d\n", ch);
		//fflush(stdout);
		if(ch == 0){
			break;
		}

		if(ch == closeBrace)
		{
			depth--;
			continue;
		}
		else if(ch == openBrace)
		{
			depth ++ ;
			continue;
		}
	}
}

void expr_FuncArgList()
{
	int depth = 1;
	while(depth > 0)
	{
		int ch = cl_expr_lex();
		//printf("ch=%d\n", ch);
		//fflush(stdout);
		if(ch ==0){
			break;
		}

		if(ch == ')')
		{
			depth--;
			continue;
		}
		else if(ch == '(')
		{
			depth ++ ;
			continue;
		}
	}
}

void expr_consumeTemplateDecl()
{
	int depth = 1;
	while(depth > 0)
	{
		int ch = cl_expr_lex();
		//printf("ch=%d\n", ch);
		fflush(stdout);
		if(ch ==0){
			break;
		}

		if(ch == '>')
		{
			depth--;
			continue;
		}
		else if(ch == '<')
		{
			depth ++ ;
			continue;
		}
	}
}

void expr_syncParser(){
	//dont do anything, a hook to allow us to implement some
	//nice error recovery if needed
}

// return the scope name at the end of the input string
ExpressionResult &parse_expression(const std::string &in)
{
	result.Reset();
	//provide the lexer with new input
	if( !setExprLexerInput(in) ){
		return result;
	}

	//printf("parsing...\n");
	cl_expr_parse();
	//do the lexer cleanup
	cl_expr_lex_clean();

	return result;
}
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 3:
{result.Reset();}
break;
case 5:
{
								yyclearin;	/*clear lookahead token*/
								yyerrok;
								/*fprintf(stderr, "CodeLite: syntax error, unexpected token '%s' found at line %d \n", cl_expr_text, cl_expr_lineno);*/
								/*fflush(stderr);*/
								expr_syncParser();
						}
break;
case 6:
{yyval = ""; }
break;
case 7:
{ yyval = yyvsp[0]; }
break;
case 8:
{ yyval = yyvsp[0]; }
break;
case 9:
{ yyval = yyvsp[0]; }
break;
case 10:
{ yyval = yyvsp[0]; }
break;
case 11:
{ yyval = yyvsp[0]; }
break;
case 12:
{ yyval = yyvsp[0]; }
break;
case 13:
{ yyval = yyvsp[0]; }
break;
case 14:
{ yyval = yyvsp[0]; }
break;
case 15:
{ yyval = yyvsp[0]; }
break;
case 16:
{ yyval = yyvsp[0]; }
break;
case 17:
{ yyval = yyvsp[0]; }
break;
case 18:
{ yyval = yyvsp[-1] + " " + yyvsp[0]; }
break;
case 19:
{ yyval = yyvsp[-1] + " " + yyvsp[0]; }
break;
case 20:
{ yyval = yyvsp[-1] + " " + yyvsp[0]; }
break;
case 21:
{ yyval = yyvsp[-1] + " " + yyvsp[0]; }
break;
case 22:
{ yyval = yyvsp[0]; }
break;
case 23:
{yyval = "";}
break;
case 24:
{yyval = yyvsp[0];}
break;
case 25:
{yyval = yyvsp[-2] + yyvsp[-1] + yyvsp[0];}
break;
case 26:
{
							if(yyvsp[-3].empty()) {
								yyval = yyvsp[-2] + yyvsp[-1] +yyvsp[0];
								
							} else {
								yyval = yyvsp[-3] + " " + yyvsp[-2] + yyvsp[-1] +yyvsp[0];
							}
						}
break;
case 27:
{
							if(yyvsp[-3].empty()) {
								yyval = yyvsp[-2] + yyvsp[-1] +yyvsp[0];
								
							} else {
								yyval = yyvsp[-3] + " " + yyvsp[-2] + yyvsp[-1] +yyvsp[0];
							}
						}
break;
case 28:
{
							if(yyvsp[-6].empty()) {
								yyval = yyvsp[-5] + yyvsp[-4] + yyvsp[-3] + yyvsp[-2] + yyvsp[-1] + " ";
							} else {
								yyval = yyvsp[-6] + " " + yyvsp[-5] + yyvsp[-4] + yyvsp[-3] + yyvsp[-2] + yyvsp[-1] + " ";
							}
						}
break;
case 29:
{
						expr_FuncArgList();
						yyval = yyvsp[-2];
						result.m_isaType = true;
						result.m_name = yyvsp[-2];
						result.m_isFunc = false;
						printf("Rule 1\n");
						/*result.Print();*/
					}
break;
case 30:
{
						yyval = yyvsp[0];
						result.m_isaType = false;
						result.m_name = yyval;
						result.m_isFunc = false;
						result.m_isThis = true;
						result.m_isPtr = true;
						/*result.Print();*/
					}
break;
case 31:
{
						yyval = yyvsp[0];
						result.m_isaType = false;
						result.m_name = yyval;
						result.m_isFunc = false;
						result.m_isThis = true;
						/*result.Print();*/
					}
break;
case 32:
{
						yyval = yyvsp[0];
						result.m_isaType = false;
						result.m_name = yyval;
						result.m_isFunc = false;
						result.m_isThis = false;
						result.m_isPtr = false;
						/*result.Print();*/
					}
break;
case 33:
{
						result.m_isaType = false;
						result.m_name = yyvsp[-2];
						result.m_isThis = false;
						yyvsp[-3].erase(yyvsp[-3].find_last_not_of(":")+1);
						result.m_scope = yyvsp[-3];
						result.m_isTemplate = yyvsp[-1].empty() ? false : true;
						result.m_templateInitList = yyvsp[-1];
						/*result.Print();*/
					}
break;
case 34:
{
						yyval = yyvsp[-4];
						result.m_isaType = true;
						result.m_name = yyval;
						result.m_isFunc = false;
						result.m_isThis = false;
						/*result.Print();*/
					}
break;
case 35:
{yyval = yyvsp[-1];}
break;
case 36:
{yyval = "";}
break;
case 37:
{yyval = yyvsp[-2] + yyvsp[-1] + yyvsp[0];}
break;
case 38:
{yyval = "";}
break;
case 39:
{
						yyval = yyvsp[0];
						expr_FuncArgList();
						result.m_isFunc = true;
					}
break;
case 40:
{yyval = yyvsp[0];}
break;
case 41:
{yyval = yyvsp[0];}
break;
case 42:
{yyval = yyvsp[0];}
break;
case 43:
{yyval = yyvsp[0];}
break;
case 44:
{yyval = ""; }
break;
case 45:
{ yyval = yyvsp[0]; }
break;
case 46:
{yyval = ""; }
break;
case 47:
{yyval = yyvsp[-1] + yyvsp[0];}
break;
case 48:
{ yyval = yyvsp[-1] + yyvsp[0]; }
break;
case 49:
{yyval = "";}
break;
case 50:
{ yyval = ";";}
break;
case 51:
{ yyval = ":";}
break;
case 52:
{
					yyval = yyvsp[-5] + yyvsp[-4];
					yyvsp[-5].erase(yyvsp[-5].find_last_not_of(":")+1);
					result.m_scope = yyvsp[-5];
					result.m_name = yyvsp[-4];
					result.m_isPtr = (yyvsp[0].find("*") != (size_t)-1);;
					result.m_isTemplate = true;
					result.m_templateInitList = yyvsp[-3] + yyvsp[-2] + yyvsp[-1];
				}
break;
case 53:
{
					yyval = yyvsp[-2] + yyvsp[-1];
					yyvsp[-2].erase(yyvsp[-2].find_last_not_of(":")+1);
					result.m_scope = yyvsp[-2];
					result.m_name = yyvsp[-1];
					result.m_isPtr = (yyvsp[0].find("*") != (size_t)-1);;
				}
break;
case 54:
{yyval = "";}
break;
case 55:
{	yyval = yyvsp[-1] + yyvsp[0];}
break;
case 56:
{yyval = yyvsp[-1]+ yyvsp[0];}
break;
case 57:
{ yyval = ""; }
break;
case 58:
{ expr_consumBracketsContent('['); yyval = "[]";}
break;
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
