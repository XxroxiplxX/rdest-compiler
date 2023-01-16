%{
#include <cstdio>
#include "../include/Logger.h"
#include <cstring>
#include "CodeBlock.h"
#include <vector>
#include "EdgeProvider.h"
#include <Graph.h>
#include "DirectedGraph.h"
#include <string.h>

std::vector<EdgeProvider> providers;
int yylex();
void yyerror(const char *s);
auto logger = Logging::Logger("logs.log");
auto control_flow_graph = GraphLib::Graph<int, int>();
auto t = DirectedGraph();
std::vector<Vertexx> vertic;
std::vector<std::string> procs;
int id = 0;

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



%%

program_all:
    procedures main {t.save_to_csv("/tmp/graphs");}
;
procedures:
    procedures PROCEDURE proc_head IS VAR proc_declarations BEGI commands END    {
        
        std::string proc_name = $3;
        std::string proc_id = "";
        int no_of_args = 0;
        int bracket = 0;
        for (int i = 0; i < proc_name.length(); i++) {
            if (bracket) {
                if (proc_name[i] == ',') {
                    no_of_args++;
                }
            } else {
                if (proc_name[i] == '(') {
                    bracket = 1;
                    if (proc_name[i+1] == ')') {
                        //warn procedura bez argumentow
                    }
                } else {
                    proc_id += proc_name[i];
                }
            }
        }
        no_of_args++;
        proc_id += std::to_string(no_of_args);
        procs.push_back(proc_id);
        logger.log("###definicja: " + proc_id);
        
    }
    | procedures PROCEDURE proc_head IS BEGI commands END   {
        
        std::string proc_name = $3;
        std::string proc_id = "";
        logger.log("to parse: " + proc_name);
        int no_of_args = 0;
        int bracket = 0;
        for (int i = 0; i < proc_name.length(); i++) {
            if (bracket) {
                if (proc_name[i] == ',') {
                    no_of_args++;
                }
            } else {
                if (proc_name[i] == '(') {
                    bracket = 1;
                    if (proc_name[i+1] == ')') {
                        //warn procedura bez argumentow
                    }
                } else {
                    proc_id += proc_name[i];
                }
            }
        }
        no_of_args++;
        proc_id += std::to_string(no_of_args);
        procs.push_back(proc_id);
        logger.log("###definicja: " + proc_id);
        
    }
    | %empty {printf("no procedures\n");}
;
main:
    PROGRAM IS VAR declarations BEGI commands END {printf("main detected\n");}
    | PROGRAM IS BEGI commands END
;
commands:
    commands command    {
        /*for (int i = 0; i < providers[$1]._end_ids.size(); i++) {
           control_flow_graph.add_edge(providers[$1]._end_ids[i], providers[$2]._begin_id, 0);
           std::string msg = "dodano krawedz miedzy vertexami: ";
           msg += std::to_string(providers[$1]._end_ids[i]);
           msg += " -> ";
           msg += std::to_string(providers[$2]._begin_id);
           logger.log(msg);
        }*/
        //control_flow_graph.add_edge(providers[$1].get_end_id(), providers[$2].get_begin_id(), 0);
        //control_flow_graph.print_e();
        
        //logger.log(std::to_string(control_flow_graph.edges.size()));
        std::string msg = "dodano krawedz miedzy vertexami: ";
        msg += std::to_string(providers[stoi($1)].get_end_id());
        msg += " -> ";
        msg += std::to_string(providers[stoi($2)].get_begin_id());
        if (providers[stoi($1)].get_end_id() == 0) {
            printf("AAAAAAAAAAAAAAAAAAAAAAAAAA\n");
        }
        t.add_edge(providers[stoi($1)]._end_id, providers[stoi($2)]._begin_id);
        //t.get_vertexx(providers[$1]._end_id)->neighbours.push_back(providers[$2]._begin_id);
        //logger.log(msg);
        //merge provider
        EdgeProvider provider;
        provider.set_begin_id(providers[stoi($1)].get_begin_id());
        provider.set_end_id(providers[stoi($2)].get_end_id());
        /*for (int i = 0; i < providers[$2]._end_ids.size(); i++) {
            provider._end_ids.push_back(providers[$2]._end_ids[i]);
        }*/
        providers.push_back(provider);
        //logger.log("zmergowano providery pod nowy z id: ", id);

        $$=std::to_string(id);
        id++;

    }
    | command   {
        $$=$1;
    }
;
command:
    proc_head SEMICOLON {
        
        std::string proc = $1;
        std::string tmp = "";
        std::string name;
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_CALL;
        int f = 0;
        for (int i = 0; i < proc.length(); i++) {
            if (f) {
                if (proc[i] == ',' || proc[i] == ')') {
                    instruction.args.push_back(Value(tmp));
                    tmp = "";
                } else {
                    tmp += proc[i];
                }
            }
            if (proc[i] == '(') {
                f = 1;
            }
            if (!f) {
                name += proc[i];
            }
        }   //fetch args

        name += std::to_string(instruction.args.size());

        int c = 0;
        for (auto it : procs) {
            if(it == name) {
                c++;
                logger.log("rzeczona nazwa to------------->" + it);
                //logger.log("procedura zadeklarowana nazwa- " + proc);
                t.add_vertexx(id);
                //logger.log("dodano vertex pod assign z id: ", id);
                t.vertices[t.vertices.size() - 1].meat.push_back(instruction);

                EdgeProvider provider;
                provider.set_begin_id(id);
                provider.set_end_id(id);
                providers.push_back(provider);
                $$=std::to_string(id);
                id++;
            }
        }
        if (!c) {
            logger.log("na liscie nie znaleziono procedury: " + name);
        }
        //logger.log("na liscie nie znaleziono procedury: " + name);
        //blad procedura nie zdefiniowana
        

    }

    |IDENTIFIER ASSIGN expression SEMICOLON     {   //TODO przerzucic tworzenie vertexa do expr, tutaj go tylko modyfikowac\
    o lewy argument
        //t.add_vertexx(id);
        //logger.log("dodano vertex pod assign z id: ", id);
        t.get_vertexx(providers[stoi($3)]._begin_id)->meat[0].left = Value($1);
        //logger.log("______" + t.get_vertexx(providers[$3]._begin_id)->meat[0].left + "_______");
        //logger.log("_________" + t.get_vertexx(providers[$3]._begin_id)->meat[0].expr.left + 
        //std::to_string(t.get_vertexx(providers[$3]._begin_id)->meat[0].expr.type_of_operator) +
        //t.get_vertexx(providers[$3]._begin_id)->meat[0].expr.right + "__________" );
        $$=$3;
    }
    | IF condition THEN commands ELSE commands ENDIF    {
            //control_flow_graph.add_vertex(id);
            //logger.log("zredukowano IF ELSE");
            EdgeProvider provider;  //provider for
            t.add_edge(providers[stoi($2)]._begin_id, providers[stoi($4)]._begin_id);   //condition ma ten sam poczatek i koniec
            t.add_edge(providers[stoi($2)]._begin_id, providers[stoi($6)]._begin_id);
            provider._begin_id = providers[stoi($2)]._begin_id;
            /*
            for (int i = 0; i < providers[$4]._end_ids.size(); i++) {
                provider._end_ids.push_back(providers[$4]._end_ids[i]);
            }
            for (int i = 0; i < providers[$6]._end_ids.size(); i++) {
                provider._end_ids.push_back(providers[$6]._end_ids[i]);
            }*/
            t.add_vertexx(id);  //empty for endif
            t.add_edge(providers[stoi($4)]._end_id, id);
            t.add_edge(providers[stoi($6)]._end_id, id);
            provider._end_id = id;
            providers.push_back(provider);
            $$=std::to_string(id);
            id++;

    }
    | IF condition THEN commands ENDIF  {
            //control_flow_graph.add_vertex(id);
            //logger.log("zredukowano IFa");
            std::string msg = "dodano krawedz miedzy vertexami: ";
            msg += std::to_string(providers[stoi($2)]._begin_id);
            msg += " -> ";
            msg += std::to_string(providers[stoi($4)]._begin_id);
            //logger.log(msg);
            t.add_vertexx(id);
            EdgeProvider provider;  //provider for
            t.add_edge(providers[stoi($2)]._begin_id, providers[stoi($4)]._begin_id);   //condidtion->commands
            t.add_edge(providers[stoi($2)]._begin_id, id);    //condition->endif
            t.add_edge(providers[stoi($4)]._end_id, id);  //end of command->endif
            provider._begin_id = providers[stoi($4)]._begin_id;
            provider._end_id = id;;    //koniec ifa to endif
            
            
            providers.push_back(provider);
            $$=std::to_string(id);
            id++;
    }
    | WHILE condition DO commands ENDWHILE  {
        
        //logger.log("zredukowano WHILE");
        std::string msg = "dodano krawedz miedzy vertexami: ";
        msg += std::to_string(providers[stoi($2)]._begin_id);
        msg += " -> ";
        msg += std::to_string(providers[stoi($4)]._begin_id);
        //logger.log(msg);
        EdgeProvider provider;  //provider for
        t.add_edge(providers[stoi($2)]._begin_id, providers[stoi($4)]._begin_id);   //\
        condition->begin of commands
        provider._begin_id = providers[stoi($2)]._begin_id;   
        t.add_vertexx(id);
        t.add_edge(providers[stoi($4)]._end_id, providers[stoi($2)]._begin_id); //end of commands->\
        condition
        
        t.add_edge(providers[stoi($2)]._begin_id, id);    //condition->endwhile
        provider._end_id = id;
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
        

    }
    | REPEAT commands UNTIL condition SEMICOLON {
        EdgeProvider provider;  //provider for
        t.add_edge(providers[stoi($2)]._end_id, providers[stoi($4)]._begin_id);   //\
        end of commands->condition
        provider._begin_id = providers[stoi($2)]._begin_id;   
        
        t.add_edge(providers[stoi($4)]._end_id, providers[stoi($2)]._begin_id); //condition->begin\
        of commands
        provider._begin_id = providers[stoi($2)]._end_id;
        provider._end_id = providers[stoi($4)]._end_id;
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    
    | READ IDENTIFIER SEMICOLON {
        t.add_vertexx(id);
        //logger.log("dodano vertex na READ z id: ", id);
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
        
        }
    | WRITE value SEMICOLON {

        t.add_vertexx(id);
        //logger.log("dodano vertex na WRITE z id: ", id);
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
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
    IDENTIFIER LBR proc_declarations RBR {
        std::string to_send = $1 + "(" + $3 + ")";
        logger.log("%%%%glowa: " + to_send);
        //$$=to_send.c_str();
        //printf("%s", to_send.c_str());
        $$=to_send;
    }
;
proc_declarations:
    proc_declarations COMMA IDENTIFIER {
        std::string to_send = $1 + "," + $3; 
        $$=to_send; 
        //logger.log($$);
    }
    | IDENTIFIER {
        $$=$1;
    }
;
declarations:
    declarations COMMA IDENTIFIER   {std::string to_send = $1 + ", " + $3; 
        $$=to_send; 
        //logger.log($$);
    }
    | IDENTIFIER {
        $$=$1;
    }
;

expression:
    value {
        t.add_vertexx(id);
        Expression expression;
        expression.type_of_operator = _type_of_operator::_NONE;
        expression.left = Value($1);
        //expression.right = Value();
        //expression.left = $<text>1;
        Instruction instruction;
        instruction.expr = expression;
        //CodeBlock codeblock;
        //codeblock.meat.push_back(instruction);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        logger.log("@@@expression: " + expression.left.load +  "----->"
        + std::to_string(expression.type_of_operator));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    | value PLUS value {
        t.add_vertexx(id);
        Expression expression;
        expression.type_of_operator = _type_of_operator::_ADD;
        expression.left = Value($1);
        expression.right = Value($3);
        //expression.right = $<text>3;
        
        Instruction instruction;
        instruction.expr = expression;
        //CodeBlock codeblock;
        //codeblock.meat.push_back(instruction);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        logger.log("@@@expression: " + expression.left.load + " + " + expression.right.load + "----->"
        + std::to_string(expression.type_of_operator));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    | value MIN value {
        t.add_vertexx(id);
        Expression expression;
        expression.type_of_operator = _type_of_operator::_DIV;
        //expression.left = $<text>1;
        //expression.right = $<text>3;
        expression.left = Value($1);
        expression.right = Value($3);
        Instruction instruction;
        instruction.expr = expression;
        //CodeBlock codeblock;
        //codeblock.meat.push_back(instruction);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        logger.log("@@@expression: " + expression.left.load + " - " + expression.right.load + "----->"
        + std::to_string(expression.type_of_operator));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    | value MUL value {
        t.add_vertexx(id);
        Expression expression;
        expression.type_of_operator = _type_of_operator::_MUL;
        //expression.left = $<text>1;
        //expression.right = $<text>3;
        expression.left = Value($1);
        expression.right = Value($3);
        Instruction instruction;
        instruction.expr = expression;
        //CodeBlock codeblock;
        //codeblock.meat.push_back(instruction);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        logger.log("@@@expression: " + expression.left.load + " * " + expression.right.load + "----->"
        + std::to_string(expression.type_of_operator));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    | value DIV value {
        t.add_vertexx(id);
        Expression expression;
        expression.type_of_operator = _type_of_operator::_DIV;
        //expression.left = $<text>1;
        //expression.right = $<text>3;
        expression.left = Value($1);
        expression.right = Value($3);
        Instruction instruction;
        instruction.expr = expression;
        //CodeBlock codeblock;
        //codeblock.meat.push_back(instruction);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        logger.log("@@@expression: " + expression.left.load + " / " + expression.right.load + "----->"
        + std::to_string(expression.type_of_operator));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    | value MOD value {
        t.add_vertexx(id);
        Expression expression;
        expression.type_of_operator = _type_of_operator::_MOD;
        //expression.left = $<text>1;
        //expression.right = $<text>3;
        expression.left = Value($1);
        expression.right = Value($3);
        Instruction instruction;
        instruction.expr = expression;
        //CodeBlock codeblock;
        //codeblock.meat.push_back(instruction);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        logger.log("@@@expression: " + expression.left.load + " % " + expression.right.load + "----->"
        + std::to_string(expression.type_of_operator));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
;
condition:
    value EQ value {
        //logger.log("@@@@COND" + std::string($<text>1) + " = " + std::string($<text>3) + "@@@@");
        t.add_vertexx(id);
        //CodeBlock codeblock;
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_COND;
        instruction.type_of_operator = _type_of_operator::_EQ;
        instruction.left = Value($1);
        instruction.right = Value($3);
        //instruction.left = $1;
        //instruction.right = $3;
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        //codeblock.meat.push_back(instruction);
        //t.get_vertexx(id)->codeblock = codeblock;
        logger.log("@@@condition: " + instruction.left.load + " = " + instruction.right.load + "---->"
         + std::to_string(instruction.type_of_instruction));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    |value NEQ value {
        t.add_vertexx(id);
        //CodeBlock codeblock;
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_COND;
        instruction.type_of_operator = _type_of_operator::_NEQ;
        instruction.left = Value($1);
        instruction.right = Value($3);
        //instruction.left = $1;
        //instruction.right = $3;
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        //codeblock.meat.push_back(instruction);
        //t.get_vertexx(id)->codeblock = codeblock;
        logger.log("@@@condition: " + instruction.left.load + " != " + instruction.right.load +"---->"
         + std::to_string(instruction.type_of_instruction));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    |value LMORE value {
        t.add_vertexx(id);
        //CodeBlock codeblock;
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_COND;
        instruction.type_of_operator = _type_of_operator::_LMORE;
        //instruction.left = $1;
        //instruction.right = $3;
        instruction.left = Value($1);
        instruction.right = Value($3);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        //codeblock.meat.push_back(instruction);
        //t.get_vertexx(id)->codeblock = codeblock;
        logger.log("@@@condition: " + instruction.left.load + " > " + instruction.right.load +"---->"
         + std::to_string(instruction.type_of_instruction));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    |value LLESS value {
        t.add_vertexx(id);
        //CodeBlock codeblock;
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_COND;
        instruction.type_of_operator = _type_of_operator::_LLESS;
        //instruction.left = $1;
        //instruction.right = $3;
        //codeblock.meat.push_back(instruction);
        //t.get_vertexx(id)->codeblock = codeblock;
        instruction.left = Value($1);
        instruction.right = Value($3);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        logger.log("@@@condition: " + instruction.left.load + " < " + instruction.right.load +"---->"
         + std::to_string(instruction.type_of_instruction));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    |value LHEQ value {
        t.add_vertexx(id);
        //CodeBlock codeblock;
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_COND;
        instruction.type_of_operator = _type_of_operator::_LHEQ;
        //instruction.left = $1;
        //instruction.right = $3;
       //codeblock.meat.push_back(instruction);
        instruction.left = Value($1);
        instruction.right = Value($3);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        //t.get_vertexx(id)->codeblock = codeblock;
        logger.log("@@@condition: " + instruction.left.load + " >= " + instruction.right.load +"---->"
         + std::to_string(instruction.type_of_instruction));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
    |value LLEQ value {
        t.add_vertexx(id);
        //CodeBlock codeblock;
        Instruction instruction;
        instruction.type_of_instruction = _type_of_meat::_COND;
        instruction.type_of_operator = _type_of_operator::_LLEQ;
        //auto a = Value(std::string($<text>1));
        //instruction.right = $3;
        instruction.left = Value($1);
        instruction.right = Value($3);
        t.vertices[t.vertices.size() - 1].meat.push_back(instruction);
        //t.get_vertexx(id)->codeblock = codeblock;
        logger.log("@@@condition: " + instruction.left.load + " <= " + instruction.right.load +"---->"
         + std::to_string(instruction.type_of_instruction));
        EdgeProvider provider;
        provider.set_begin_id(id);
        provider.set_end_id(id);
        providers.push_back(provider);
        $$=std::to_string(id);
        id++;
    }
;
value:
    NUM {
         //std::string to_send = "NUM" + std::string($<text>1); 
         
         
         $$=$1;
         //$<text>$= $<text>1;// + std::string($<text>1); 
         //$<type>$ = 1;
         //to_send + .c_str(); 
         
    }
    |IDENTIFIER {
        //std::string to_send = "ID__" + std::string($<text>1) + "__"; 
        //logger.log("odkrylem idenbtyfikator: -------" + to_send);
        
        $$=$1;
        //$$=strcat("ID_", $<text>1);
        //to_send.c_str(); 
        //$<text>$= $<text>1;// + std::string($<text>1); 
        //$<type>$ = 2;
        
        
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
    t.save_to_csv("/tmp/graphs");
    //control_flow_graph.save_to_csv("/tmp/graphs");
    printf("to ja\n");
    
    //auto x = control_flow_graph.get_edge(0,1)->label;
    //printf("%d\n", control_flow_graph.get_edge(0,1)->label);
    return parsed;
}
int main()
{

    return handle();
    
}
