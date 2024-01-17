%{
#include <cstdio>

#include <cstring>

#include <vector>


#include <iostream>
#include <string>

int yylex();

void yyerror(const char *s);

extern "C" FILE *yyin;
int handle(const char* input_file, const char* output_file)
{
    yyin = fopen(input_file, "r" );
    
    return 0;
}
%}

%define api.value.type {std::string}


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




%token SYNTAX_ERROR
%token IDENTIFIER
%token NUM
%token LBR
%token RBR

%token PARSE_ERROR

%%

program_all:
    procedures main {}
;
procedures:
    procedures PROCEDURE proc_head IS VAR proc_declarations BEGI commands END    {}
        
    | procedures PROCEDURE proc_head IS BEGI commands END   {
        
        
    }
    | %empty {}
;
main:
    PROGRAM IS VAR declarations BEGI commands END {
       
        
    }
    | PROGRAM IS BEGI commands END {

       
    }
;
commands:
    commands command    {
        

    }
    | command   {
       
    }
;
command:
    proc_head SEMICOLON {
        
    }

    |IDENTIFIER ASSIGN expression SEMICOLON     {   //TODO przerzucic tworzenie vertexa do expr, tutaj go tylko modyfikowac\

    }
    | IF condition THEN commands ELSE commands ENDIF    {
        
    }
    | WHILE condition DO commands ENDWHILE  {
     
        

    }
    | REPEAT commands UNTIL condition SEMICOLON {
    
     
    }
    
    | READ IDENTIFIER SEMICOLON {
        
        }
    | WRITE value SEMICOLON {

   
   
        }
;
proc_head:
    IDENTIFIER LBR proc_declarations RBR {
      
    }
;
proc_declarations:
    proc_declarations COMMA IDENTIFIER {
   
    }
    | IDENTIFIER {
        
    }
;
declarations:
    declarations COMMA IDENTIFIER   {
       
    }
    | IDENTIFIER {
        
    }
;

expression:
    value {
  
    }
    | value PLUS value {
    
   
    }
    | value MIN value {
 
    }
    | value MUL value {
   
    }
    | value DIV value {
      
    }
    | value MOD value {
    
    }
;
condition:
    value EQ value {
       
      
    }
    |value NEQ value {
       
    }
    |value LMORE value {
       
    }
    |value LLESS value {
      
    }
    |value LHEQ value {
       
    }
    |value LLEQ value {
       
       
    }
;
value:
    NUM {
       
         
    }
    |IDENTIFIER {
       
        
        
    }
    
;
%%
void yyerror(const char* msg) {
    std::cerr << "blad w linii: " <<  std::endl;
    exit(1);
    
}



