%{
#include <cstdio>
#include "../include/Logger.h"
#include <cstring>
#include "CodeBlock.h"
#include <vector>
std::vector<CodeBlock*> graph;
int yylex();
void yyerror(const char *s);
auto logger = Logging::Logger("logs.log");

%}

%union {
    char* text;
    
}

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



%token<text> NUM
%token SYNTAX_ERROR
%token<text> IDENTIFIER
%token LBR
%token RBR
%type <text> value
%type<text> condition
%type<text> expression
%%

program_all:
    procedures main
;
procedures:
    procedures PROCEDURE proc_head IS VAR declarations BEGI commands END
    | procedures PROCEDURE proc_head IS BEGI commands END
    | {printf("no procedures\n");}
;
main:
    PROGRAM IS VAR declarations BEGI commands END {printf("main detected\n");}
    | PROGRAM IS BEGI commands END
;
commands:
    commands command
    | command
;
command:
    IDENTIFIER ASSIGN expression SEMICOLON     {printf("ass\n");logger.log("assign\n");}
    | IF condition THEN commands ELSE commands ENDIF
    | IF condition THEN commands ENDIF
    | WHILE condition DO commands ENDWHILE
    | REPEAT commands UNTIL condition SEMICOLON
    | proc_head SEMICOLON
    | READ IDENTIFIER SEMICOLON {
        
        
        }
    | WRITE value SEMICOLON                     {logger.log("WRITE\n");}
;
proc_head:
    IDENTIFIER LBR declarations RBR
;
declarations:
    declarations COMMA IDENTIFIER
    | IDENTIFIER
;

expression:
    value;
    | value PLUS value {printf("reduced expression\n");}
    | value MIN value {printf("reduced expression\n");}
    | value MUL value {printf("reduced expression\n");}
    | value DIV value {printf("reduced expression\n");}
    | value MOD value {printf("reduced expression\n");}
;
condition:
    value EQ value {printf("reduced condition\n");}
    |value NEQ value {printf("reduced condition\n");}
    |value LMORE value {printf("reduced condition\n");}
    |value LLESS value {printf("reduced condition\n");}
    |value LHEQ value {printf("reduced condition\n");}
    |value LLEQ value {printf("reduced condition\n");}
;
value:
    NUM                {$$=$<text>1; logger.log($$);}
    |IDENTIFIER         {$$=$<text>1;logger.log($$);}
;
%%
void yyerror(const char* msg) {

}
int handle()
{
    int parsed = yyparse();
    logger.log("test");
    logger.close_logger();
    printf("to ja\n");
    return parsed;
}
int main()
{

    return handle();
    
}
