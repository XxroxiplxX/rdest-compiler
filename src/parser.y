%{
#include <cstdio>
#include "../include/Logger.h"
#include <cstring>
#include "CodeBlock.h"
#include <vector>
#include "EdgeProvider.h"
#include <Graph.h>
std::vector<EdgeProvider> providers;
int yylex();
void yyerror(const char *s);
auto logger = Logging::Logger("logs.log");
auto control_flow_graph = GraphLib::Graph<int, int>();
int id = 0;
%}

%union {
    char* text;
    int edge_provider_id;
    
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
%type<edge_provider_id> condition
%type<text> expression

%type<edge_provider_id> command
%type<edge_provider_id> commands

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
    commands command    {
        for (int i = 0; i < providers[$1]._end_ids.size(); i++) {
           control_flow_graph.add_edge(providers[$1]._end_ids[i], providers[$2]._begin_id, 0);
           std::string msg = "dodano krawedz miedzy vertexami: ";
           msg += std::to_string(providers[$1]._end_ids[i]);
           msg += " -> ";
           msg += std::to_string(providers[$2]._begin_id);
           logger.log(msg);
        }
        ;

        //merge provider
        EdgeProvider provider;
        provider._begin_id = providers[$1]._begin_id;
        for (int i = 0; i < providers[$2]._end_ids.size(); i++) {
            provider._end_ids.push_back(providers[$2]._end_ids[i]);
        }
        providers.push_back(provider);
        logger.log("zmergowano providery pod nowy z id: ", id);
        $$=id;
        id++;

    }
    | command   {
        $$=$1;
    }
;
command:
    IDENTIFIER ASSIGN expression SEMICOLON     {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex pod assign z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
    }
    | IF condition THEN commands ELSE commands ENDIF    {
            //control_flow_graph.add_vertex(id);
            logger.log("zredukowano IF ELSE");
            EdgeProvider provider;  //provider for
            control_flow_graph.add_edge(providers[$2]._begin_id, providers[$4]._begin_id, 0);   //condition ma ten sam poczatek i koniec
            control_flow_graph.add_edge(providers[$2]._begin_id, providers[$6]._begin_id, 0);
            provider._begin_id = providers[$2]._begin_id;
            for (int i = 0; i < providers[$4]._end_ids.size(); i++) {
                provider._end_ids.push_back(providers[$4]._end_ids[i]);
            }
            for (int i = 0; i < providers[$6]._end_ids.size(); i++) {
                provider._end_ids.push_back(providers[$6]._end_ids[i]);
            }
            providers.push_back(provider);
            $$=id;
            id++;

    }
    | IF condition THEN commands ENDIF  {
            //control_flow_graph.add_vertex(id);
            logger.log("zredukowano IFa");
            std::string msg = "dodano krawedz miedzy vertexami: ";
            msg += std::to_string(providers[$2]._begin_id);
            msg += " -> ";
            msg += std::to_string(providers[$4]._begin_id);
            logger.log(msg);
            EdgeProvider provider;  //provider for
            control_flow_graph.add_edge(providers[$2]._begin_id, providers[$4]._begin_id, 0);
            provider._begin_id = providers[$2]._begin_id;
            provider._end_ids.push_back(providers[$2]._begin_id);    //condidtion jest zarowno\
            koncem jak i poczatkiem IFa
            for (int i = 0; i < providers[$4]._end_ids.size(); i++) {
                provider._end_ids.push_back(providers[$4]._end_ids[i]);
            }
            
            providers.push_back(provider);
            $$=id;
            id++;
    }
    | WHILE condition DO commands ENDWHILE
    | REPEAT commands UNTIL condition SEMICOLON
    | proc_head SEMICOLON
    | READ IDENTIFIER SEMICOLON {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex na READ z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
        
        }
    | WRITE value SEMICOLON {

        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex na WRITE z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
        /*int id = graph.size();
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_WRITE;
        instruction.type_of_operator = _operators::_NONE;
        instruction.right = $<text>2;
        auto codeblock = CodeBlock(instruction, id);
        graph.push_back(codeblock);
        logger.log("handled WRITE with identaificator " + instruction.right + " and \
        ___id = " +"__");
        $$ = id;*/
        }
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
    value EQ value {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex na cond z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
    }
    |value NEQ value {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex na cond z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
    }
    |value LMORE value {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex na cond z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
    }
    |value LLESS value {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex na cond z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
    }
    |value LHEQ value {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertex na cond z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
    }
    |value LLEQ value {
        control_flow_graph.add_vertex(id);
        logger.log("dodano vertexna cond z id: ", id);
        EdgeProvider provider;
        provider._begin_id = id;
        provider._end_ids.push_back(id);
        providers.push_back(provider);
        $$=id;
        id++;
    }
;
value:
    NUM                {//$$=$<text>1; logger.log($$);
    }
    |IDENTIFIER         {//$$=$<text>1;logger.log($$);
    }
;
%%
void yyerror(const char* msg) {

}
int handle()
{
    int parsed = yyparse();
    logger.log("test");
    logger.close_logger();
    control_flow_graph.save_to_csv("/tmp/graphs");
    printf("to ja\n");
    return parsed;
}
int main()
{

    return handle();
    
}
