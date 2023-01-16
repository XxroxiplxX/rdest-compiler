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
\;              {yylval = std::string(yytext);  return SEMICOLON;}
=               {yylval = std::string(yytext);  return EQ;}
:=              {yylval = std::string(yytext);  return ASSIGN;}
,               {yylval = std::string(yytext); return COMMA;}
\+              {yylval = std::string(yytext);   return PLUS;}
-               {yylval = std::string(yytext);   return MIN;}
\*              {yylval = std::string(yytext);  return MUL;}
\/              {yylval = std::string(yytext);  return DIV;}
"%"             {yylval = std::string(yytext);  return MOD;}
\(              {yylval = std::string(yytext);  return LBR;}
\)              {yylval = std::string(yytext); return RBR;}
!=              {yylval = std::string(yytext);  return NEQ;}
"<"             {yylval = std::string(yytext);    return LLESS;}
">"             {yylval = std::string(yytext);  return LMORE;}
"<="            {yylval = std::string(yytext);   return LLEQ;}
">="            {yylval = std::string(yytext);  return LLEQ;}
\[              {BEGIN(COMMENT);  }
<COMMENT>{
    \]           {  BEGIN(0);}
    .           { }
    \n          { }
}
[A-Z]+          {
                     
                    std::string ID(yytext);
                    yylval = ID;
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
[[:digit:]]+ {
    std::string ID = "NUM_" + std::string(yytext);
    yylval = ID;    return NUM;
    }
[_a-z]+ {
    std::string ID = "ID_" + std::string(yytext);
    yylval = ID;    return IDENTIFIER;
    }

\n          {  lines++;}
[[:space:]] { }
. { ECHO;}
%%


