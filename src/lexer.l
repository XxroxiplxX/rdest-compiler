%option noyywrap
%{
#include <string>
#include <iostream>
#include <cstdlib>
#include "parsery.hpp"
int yylex();
int lex(int token);
int lnum(int token);
int lines = 1;

using namespace std;

/*
*******operators******

%token PLUS
%token MIN
%token MUL
%token DIV
%token MOD
%token EQ
%token NEQ
%token LLEQ
%token LHEQ
%token LLESS
%token LMORE
%token ASSIGN
%token SEMICOLON
%token COMMA

*********keywords*********

%token IF
%token THEN
%token ELSE
%token ENDIF
%token WHILE
%token DO
%token ENDWHILE
%token REPEAT
%token UNTIL
%token READ
%token WRITE
%token PROCEDURE
%token IS
%token VAR
%token BEGI
%token END
%token PROGRAM

********other********

%token NUM
%token SYNTAX_ERROR
%token IDENTIFIER
%token LBR
%token RBR
*/

%}

%x COMMENT
%%
\t              { }
\;              {yylval.text=strdup(yytext);  return SEMICOLON;}
=               {yylval.text=strdup(yytext);  return EQ;}
:=              {yylval.text=strdup(yytext);  return ASSIGN;}
,               {yylval.text=strdup(yytext);  return COMMA;}
\+              {yylval.text=strdup(yytext);   return PLUS;}
-               {yylval.text=strdup(yytext);   return MIN;}
\*              {yylval.text=strdup(yytext);  return MUL;}
\/              {yylval.text=strdup(yytext);   return DIV;}
"%"             {yylval.text=strdup(yytext);  return MOD;}
\(              {yylval.text=strdup(yytext);  return LBR;}
\)              {yylval.text=strdup(yytext);  return RBR;}
!=              {yylval.text=strdup(yytext);  return NEQ;}
"<"             {yylval.text=strdup(yytext);    return LLESS;}
">"             {yylval.text=strdup(yytext);   return LMORE;}
"<="            {yylval.text=strdup(yytext);    return LLEQ;}
">="            {yylval.text=strdup(yytext);   return LLEQ;}
\[              {BEGIN(COMMENT);  }
<COMMENT>{
    \]           {  BEGIN(0);}
    .           { }
    \n          { }
}
[A-Z]+          {
                     
                    std::string ID(yytext);
                    yylval.text=strdup(yytext);
                    if (ID == "PROCEDURE") {
                        return PROCEDURE;
                    } else if (ID == "IS") {
                        return IS;
                    } else if (ID == "VAR") {
                        return VAR;
                    } else if (ID == "BEGIN") {
                        return BEGI;
                    } else if (ID == "END") {
                        return END;
                    } else if (ID == "IF") {
                        return IF;
                    } else if (ID == "THEN") {
                        return THEN;
                    } else if (ID == "ELSE") {
                        return ELSE;
                    } else if (ID == "ENDIF") {
                        return ENDIF;
                    } else if (ID == "WHILE") {
                        return WHILE;
                    } else if (ID == "DO") {
                        return DO;
                    } else if (ID == "ENDWHILE") {
                        return ENDWHILE;
                    } else if (ID == "REPEAT") {
                        return REPEAT;
                    } else if (ID == "UNTIL") {
                        return UNTIL;
                    } else if (ID == "READ") {
                        return READ;
                    } else if (ID == "WRITE") {
                        return WRITE;
                    } else if (ID == "PROGRAM") {
                        return PROGRAM;
                    } else ECHO;
                }
[[:digit:]]+ {yylval.text=strdup(yytext);  return NUM;}
[_a-z]+ {yylval.text=strdup(yytext);  return IDENTIFIER;}

\n          {  lines++;}
[[:space:]] { }
. { ECHO;}
%%


