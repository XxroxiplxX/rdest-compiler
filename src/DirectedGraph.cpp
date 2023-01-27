#include "../include/DirectedGraph.h"
//#include "DirectedGraph.h"
void DirectedGraph::_asm_get(Value val, CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("GET", architecture.get_register(val.load, codeblock->proc_id), instruction_pointer));
    instruction_pointer++;
    
}
void DirectedGraph::_asm_halt(CodeBlock* codeblock) {
    _asm_instructions.push_back(AsmInstruction("HALT", instruction_pointer));
    instruction_pointer++;
    
}
void DirectedGraph::_asm_put(Value val, CodeBlock* codeblock) {
    log.log("#write");
    if (val.type == _ID) {
        _asm_instructions.push_back(AsmInstruction("PUT", architecture.get_register(val.load, codeblock->proc_id), instruction_pointer));
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("PUT", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
    
    log.log("ok");
    
}
void DirectedGraph::_asm_load(Value val, CodeBlock* codeblock) {
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("LOADI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("LOAD", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::_asm_store(Value val, CodeBlock* codeblock) {
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("STOREI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("STORE", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::translate_assign(Instruction ins, CodeBlock* codeblock) {
    translate_expression(ins.expr, codeblock);
    _asm_store(ins.left, codeblock);
    
}
void DirectedGraph::translate_expression(Expression expr, CodeBlock* codeblock) {
    _asm_load(expr.left, codeblock);
    switch(expr.type_of_operator) {
        case _ADD:
            //log.log("chce postawic add");
            _asm_add(expr.right, codeblock);
            break;
        case _SUB:
            _asm_sub(expr.right, codeblock);
            break;
        case _MUL:
            _asm_mul(expr.left, expr.right, codeblock);
            break;
        case _DIV:
            _asm_div(expr.left, expr.right, codeblock);
            break;
        case _MOD:
            _asm_mod(expr.left, expr.right, codeblock);
            break;
        
    }
}
void DirectedGraph::_asm_set_op_constants() {
    /*stala do mnozenia*/
    //architecture.assert_const("1");
    architecture.initialize_num_constant();
    _asm_instructions.push_back(AsmInstruction("SET", "1", instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_one(), instruction_pointer));
    instruction_pointer++;
    
}
void DirectedGraph::_asm_set_external_constants() {
    for (auto const_reg : architecture.constants) {
        _asm_instructions.push_back(AsmInstruction("SET", const_reg.first, instruction_pointer));
        instruction_pointer++;
        _asm_instructions.push_back(AsmInstruction("STORE", const_reg.second, instruction_pointer));
        instruction_pointer++;
    }
}
void DirectedGraph::_asm_mul(Value left, Value right, CodeBlock* codeblock) {
    
    log.log("wszedlem");
    if (architecture.get_mul_prod() == nullptr) {
        log.log("error mul prod");
    }
    if (architecture.get_op_1() == nullptr) {
        log.log("error mul op1");
    }
    if (architecture.get_op_2() == nullptr) {
        log.log("error mul op2");
    }
    if (architecture.get_mul_trash() == nullptr) {
        log.log("error mul trash");
    }
    _asm_instructions.push_back(AsmInstruction("SET", "0", instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_mul_prod(), instruction_pointer));
    instruction_pointer++;
    _asm_load(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_op_1(), instruction_pointer));
    instruction_pointer++;
    
    _asm_load(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_op_2(), instruction_pointer));
    instruction_pointer++;

    log.log("gotowe");
    int _zero = instruction_pointer;
    _asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_op_1(), instruction_pointer, "      [loop, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 23), instruction_pointer, "      [jzero end, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_op_2(), instruction_pointer, "      [loop, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 23), instruction_pointer, "      [jzero end, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("HALF", instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_mul_trash(), instruction_pointer));
    instruction_pointer++;
    log.log("eee");

    _asm_push_base("LOAD", architecture.get_op_2());
    _asm_push_base("ADD", architecture.get_one());
    log.log("eee");
    _asm_instructions.push_back(AsmInstruction("HALF", instruction_pointer));
    instruction_pointer++;
    _asm_push_base("SUB", architecture.get_mul_trash());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 12), instruction_pointer, "      [jzero ins, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 19), instruction_pointer, "      [jump odd, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_push_base("LOAD", architecture.get_op_1(), "   [ins, k = ");
    _asm_push_base("ADD", architecture.get_op_1());
    _asm_push_base("STORE", architecture.get_op_1());
    _asm_push_base("LOAD", architecture.get_op_2());
     _asm_instructions.push_back(AsmInstruction("HALF", instruction_pointer));
    instruction_pointer++;
    log.log("eee");
    _asm_push_base("STORE", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero), instruction_pointer, "      [jump loop, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_push_base("LOAD", architecture.get_op_1());
    _asm_push_base("ADD", architecture.get_mul_prod());
    _asm_push_base("STORE", architecture.get_mul_prod());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 12), instruction_pointer, "      [jump ins, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_push_base("LOAD", architecture.get_mul_prod(), "   [end, k = ");
    log.log("pomnozone");
    
    log.log("skonczylem");
    //w akumulatorze powinien byc wynik mnozenia

}
void DirectedGraph::_asm_div(Value left, Value right, CodeBlock* codeblock) {
    
    log.log("dziele");
   
    _asm_load(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_op_1(), instruction_pointer));
    instruction_pointer++;
    _asm_load(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_op_2(), instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_div_C(), instruction_pointer));
    instruction_pointer++;

    int _zero = instruction_pointer;
//pre  
    _asm_instructions.push_back(AsmInstruction("SET", "0", instruction_pointer, "      [pre, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_push_base("STORE", architecture.get_div_Q());
    _asm_push_base("LOAD", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 51), instruction_pointer, "      [jpos end, k = " + std::to_string(instruction_pointer) + "]")); //div by 0
    instruction_pointer++;
    _asm_push_base("SUB", architecture.get_op_1());
    
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 51), instruction_pointer, "      [jpos end, k = " + std::to_string(instruction_pointer) + "]")); // 4/5
    instruction_pointer++;
    
//init
    _asm_push_base("LOAD", architecture.get_op_1(), "       [init, k = ");
    _asm_push_base("SUB", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 13), instruction_pointer, "      [jpos shr, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;//
    _asm_push_base("LOAD", architecture.get_op_2());
    _asm_push_base("SUB", architecture.get_op_1());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 32), instruction_pointer, "      [jzero isVal, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 17), instruction_pointer, "      [jump start, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;

//shr
    _asm_push_base("LOAD", architecture.get_op_2());
    _asm_push_base("ADD", architecture.get_op_2());
    _asm_push_base("STORE", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 6), instruction_pointer, "      [jump init, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//start
    _asm_push_base("LOAD", architecture.get_op_2(), "       [start, k = ");
    _asm_instructions.push_back(AsmInstruction("HALF", instruction_pointer));
    instruction_pointer++;
    _asm_push_base("STORE", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 21), instruction_pointer, "      [jump isValid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//isValid
    _asm_push_base("LOAD", architecture.get_op_2(), "       [isValid, k = ");
    _asm_push_base("SUB", architecture.get_div_C());
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 28), instruction_pointer, "      [jpos valid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_push_base("LOAD", architecture.get_div_C());
    _asm_push_base("SUB", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 28), instruction_pointer, "      [jzero valid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 51), instruction_pointer, "      [jump end, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//valid
    _asm_push_base("LOAD", architecture.get_op_1(), "       [valid, k = ");
    _asm_push_base("SUB", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 32), instruction_pointer, "      [jpos kon, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 43), instruction_pointer, "      [jzero sprawdzmy, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//kon
    _asm_push_base("STORE", architecture.get_div_R(), "     [kon, k = ");
    _asm_push_base("STORE", architecture.get_op_1());
    _asm_push_base("LOAD", architecture.get_div_Q());
    _asm_push_base("ADD", architecture.get_div_Q());
    _asm_push_base("ADD", architecture.get_one());
    _asm_push_base("STORE", architecture.get_div_Q());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 39), instruction_pointer, "      [jump changeY, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//changeY
    _asm_push_base("LOAD", architecture.get_op_2(), "       [changeY, k = ");
    _asm_instructions.push_back(AsmInstruction("HALF", instruction_pointer));
    instruction_pointer++;
    _asm_push_base("STORE", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 21), instruction_pointer, "      [jump isValid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//sprawdzmy
    _asm_push_base("LOAD", architecture.get_op_2(), "       [sprawdzmy, k = ");
    _asm_push_base("SUB", architecture.get_op_1());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 32), instruction_pointer, "      [jzero kon, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 47), instruction_pointer, "      [jump cant, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//cant
    _asm_push_base("LOAD", architecture.get_div_Q(), "      [cant, k = ");
    _asm_push_base("ADD", architecture.get_div_Q());
    _asm_push_base("STORE", architecture.get_div_Q());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 39), instruction_pointer, "      [jump changeY, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//end
    _asm_push_base("LOAD", architecture.get_div_Q(), "      [end, k = ");
    
    
    
}
void DirectedGraph::_asm_mod(Value left, Value right, CodeBlock* codeblock) {
    _asm_load(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_op_1(), instruction_pointer));
    instruction_pointer++;
    _asm_load(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_op_2(), instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_div_C(), instruction_pointer));
    instruction_pointer++;

    int _zero = instruction_pointer;
//pre  
    _asm_instructions.push_back(AsmInstruction("SET", "0", instruction_pointer));
    instruction_pointer++;
    _asm_push_base("STORE", architecture.get_div_Q());
    _asm_push_base("STORE", architecture.get_div_R()); //+1
    _asm_push_base("LOAD", architecture.get_op_2(), "       [pre, k = ");
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 52), instruction_pointer, "      [jpos enc, k = " + std::to_string(instruction_pointer) + "]"));//mod by 0
    instruction_pointer++;
    _asm_push_base("SUB", architecture.get_op_1());
    
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 54), instruction_pointer, "      [jpos post end, k = " + std::to_string(instruction_pointer) + "]"));  //4%5
    instruction_pointer++;
    
//init
    _asm_push_base("LOAD", architecture.get_op_1(), "       [init, k = ");
    _asm_push_base("SUB", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 14), instruction_pointer, "      [jpos shr, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;//
    _asm_push_base("LOAD", architecture.get_op_2());
    _asm_push_base("SUB", architecture.get_op_1());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 33), instruction_pointer, "      [jzero isVal, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 18), instruction_pointer, "      [jump start, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;

//shr
    _asm_push_base("LOAD", architecture.get_op_2());
    _asm_push_base("ADD", architecture.get_op_2());
    _asm_push_base("STORE", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 7), instruction_pointer, "      [jump init, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//start
    _asm_push_base("LOAD", architecture.get_op_2(), "       [start, k = ");
    _asm_instructions.push_back(AsmInstruction("HALF", instruction_pointer));
    instruction_pointer++;
    _asm_push_base("STORE", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 22), instruction_pointer, "      [jump isValid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//isValid
    _asm_push_base("LOAD", architecture.get_op_2(), "       [isValid, k = ");
    _asm_push_base("SUB", architecture.get_div_C());
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 29), instruction_pointer, "      [jpos valid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_push_base("LOAD", architecture.get_div_C());
    _asm_push_base("SUB", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 29), instruction_pointer, "      [jzero valid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 52), instruction_pointer, "      [jump end, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//valid
    _asm_push_base("LOAD", architecture.get_op_1(), "       [valid, k = ");
    _asm_push_base("SUB", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JPOS", std::to_string(_zero + 33), instruction_pointer, "      [jpos kon, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 44), instruction_pointer, "      [jzero sprawdzmy, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//kon
    _asm_push_base("STORE", architecture.get_div_R(), "     [kon, k = ");
    _asm_push_base("STORE", architecture.get_op_1());
    _asm_push_base("LOAD", architecture.get_div_Q());
    _asm_push_base("ADD", architecture.get_div_Q());
    _asm_push_base("ADD", architecture.get_one());
    _asm_push_base("STORE", architecture.get_div_Q());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 40), instruction_pointer, "      [jump changeY, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//changeY
    _asm_push_base("LOAD", architecture.get_op_2(), "       [changeY, k = ");
    _asm_instructions.push_back(AsmInstruction("HALF", instruction_pointer));
    instruction_pointer++;
    _asm_push_base("STORE", architecture.get_op_2());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 22), instruction_pointer, "      [jump isValid, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//sprawdzmy
    _asm_push_base("LOAD", architecture.get_op_2(), "       [sprawdzmy, k = ");
    _asm_push_base("SUB", architecture.get_op_1());
    _asm_instructions.push_back(AsmInstruction("JZERO", std::to_string(_zero + 33), instruction_pointer, "      [jzero kon, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 48), instruction_pointer, "      [jump cant, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//cant
    _asm_push_base("LOAD", architecture.get_div_Q(), "      [cant, k = ");
    _asm_push_base("ADD", architecture.get_div_Q());
    _asm_push_base("STORE", architecture.get_div_Q());
    _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 40), instruction_pointer, "      [jump changeY, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//end
    _asm_push_base("LOAD", architecture.get_div_R(), "      [end, k = ");
     _asm_instructions.push_back(AsmInstruction("JUMP", std::to_string(_zero + 55), instruction_pointer, "      [jump next, k = " + std::to_string(instruction_pointer) + "]"));
    instruction_pointer++;
//post end
    _asm_load(left, codeblock);
//next
}
void DirectedGraph::_asm_add(Value val, CodeBlock* codeblock) {
    log.log("prosze o rejestr procedury: " + codeblock->proc_id + " dla zmiennej: " + val.load);
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("ADDI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("ADD", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("ADD", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::_asm_sub(Value val, CodeBlock* codeblock) {
    log.log("prosze o rejestr procedury: " + codeblock->proc_id + " dla zmiennej: " + val.load);
    if (val.type == _ID) {
        auto val_reg = architecture.get_register(val.load, codeblock->proc_id);
        if (val_reg->holds_argument) {
            _asm_instructions.push_back(AsmInstruction("SUBI", val_reg, instruction_pointer));
        } else {
            _asm_instructions.push_back(AsmInstruction("SUB", val_reg, instruction_pointer));
        }
    } else {    //case const
        _asm_instructions.push_back(AsmInstruction("SUB", architecture.get_constant(val.load), instruction_pointer));
    }
    instruction_pointer++;
}
void DirectedGraph::_asm_cmp_lower(Value left, Value right, CodeBlock* codeblock) {
    //load right sub left jpos true jump false
    _asm_load(right, codeblock);
    _asm_sub(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("JPOS", codeblock->next_true, instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_false, instruction_pointer));
    instruction_pointer++;

}
void DirectedGraph::_asm_cmp_eq(Value left, Value right, CodeBlock* codeblock) {
    //true jesli left - right = 0 i right i left = 0
    _asm_load(right, codeblock);
    _asm_sub(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("JPOS", codeblock->next_false, instruction_pointer));
    instruction_pointer++;
    _asm_load(left, codeblock);
    _asm_sub(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("JZERO", codeblock->next_true, instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_false, instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_cmp_neq(Value left, Value right, CodeBlock* codeblock) {
    //true jesli left - right > 0 lub right - left > 0
    _asm_load(right, codeblock);
    _asm_sub(left, codeblock);
    _asm_instructions.push_back(AsmInstruction("JPOS", codeblock->next_true, instruction_pointer));
    instruction_pointer++;
    _asm_load(left, codeblock);
    _asm_sub(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("JPOS", codeblock->next_true, instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_false, instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_cmp_leq(Value left, Value right, CodeBlock* codeblock) {
    //true jesli left <= right tzn left - right = 0
    _asm_load(left, codeblock);
    _asm_sub(right, codeblock);
    _asm_instructions.push_back(AsmInstruction("JZERO", codeblock->next_true, instruction_pointer));
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_false, instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_jump_i(std::string proc_id) {
    _asm_instructions.push_back(AsmInstruction("JUMPI", architecture.get_ret_reg(proc_id), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::_asm_clean_op_regs() {
    
}
void DirectedGraph::translate_condition(Instruction ins, CodeBlock* codeblock) {
    switch(ins.type_of_operator) {
        case _LLESS:
            _asm_cmp_lower(ins.left, ins.right, codeblock);
            break;
        case _LMORE:
            _asm_cmp_lower(ins.right, ins.left, codeblock);
            break;
        case _EQ:
            _asm_cmp_eq(ins.left, ins.right, codeblock);
            break;
        case _LLEQ:
            _asm_cmp_leq(ins.right, ins.left, codeblock);
            break;
        case _LHEQ:
            _asm_cmp_leq(ins.left, ins.right, codeblock);
            break;
        case _NEQ:
            _asm_cmp_neq(ins.left, ins.right, codeblock);
            break;
    }
}
void DirectedGraph::translate_call(Instruction ins, CodeBlock* codeblock) {
    //TODO change registers insinde another procedures
    std::string proc_to_jump = ins.proc_id;
    log.log("wewnatrz procedury: " + codeblock->proc_id + " tlumacze calla do procedury: " + proc_to_jump);
    for (int i = 0; i < ins.args.size(); i++) {
        //_asm_load(ins.args[i], codeblock);
        std::string arg_address = std::to_string(architecture.get_register(ins.args[i].load, codeblock->proc_id)->id);  //numer rejestru pod ktorym jestidentyfikator taki sam jak w callu dla 
        auto reg = architecture.get_register(ins.args[i].load, codeblock->proc_id);
        std::string id_want_to_store = architecture.procedures_memory[proc_to_jump].arg_ids[i];

        if (codeblock->proc_id == "main") {
            _asm_instructions.push_back(AsmInstruction("SET", arg_address, instruction_pointer));
            instruction_pointer++;
        } else if (architecture.is_an_arg(ins.args[i].load, codeblock->proc_id)) {
            _asm_instructions.push_back(AsmInstruction("LOAD", reg, instruction_pointer));
            instruction_pointer++;
        } else {
            _asm_instructions.push_back(AsmInstruction("SET", arg_address, instruction_pointer));
            instruction_pointer++;
        }
        _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_register(id_want_to_store, proc_to_jump), instruction_pointer));
            instruction_pointer++;
        log.log("zapakowalem argument: " + id_want_to_store);
    }
    auto c = AsmInstruction("SET", std::to_string(instruction_pointer + 3), instruction_pointer);
    //std::cout << "constant to jump: " << c.constant << std::endl;
    _asm_instructions.push_back(c); //lokalizacja powrotu
    log.log("ustawilem adres powrotu na: ", instruction_pointer + 3);
    instruction_pointer++;
    _asm_instructions.push_back(AsmInstruction("STORE", architecture.get_ret_reg(proc_to_jump), instruction_pointer));
    instruction_pointer++;
    
    int id_of_proc_head;
    for (auto proc_head : head_map) {
        if (proc_head.second == proc_to_jump) {
            id_of_proc_head = proc_head.first;
        }
    }
    log.log("skacze do procedury, ktorej glowa ma numer: ", id_of_proc_head);
    _asm_instructions.push_back(AsmInstruction("JUMP", get_vertexx(id_of_proc_head), instruction_pointer));
    instruction_pointer++;
}
void DirectedGraph::translate_ins(Instruction ins, CodeBlock* codeblock) {
    log.log("tlumacze instrukcje w procedurze: " + codeblock->proc_id);
    switch (ins.type_of_instruction) {
        case _COND:
            log.log("translacja warunku");
            translate_condition(ins, codeblock);
            break;
        case _READ:
            log.log("translacja READ");
            _asm_get(ins.right, codeblock);
            if (codeblock->next_true != nullptr and (codeblock->next_true->empty or codeblock->next_true->meat[0]._while_cond)) {
                //_asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_true, instruction_pointer));
                //instruction_pointer++;
            }
            break;
        case _WRITE:
        log.log("translacja WRITE");
            _asm_put(ins.right, codeblock);
            log.log("done");
            if (codeblock->next_true != nullptr and (codeblock->next_true->empty or codeblock->next_true->meat[0]._while_cond)) {
                //_asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_true, instruction_pointer));
                //instruction_pointer++;
            }
            break;
        case _ASS:
        log.log("tlumacze ass");
            translate_assign(ins, codeblock);
            if (codeblock->next_true != nullptr and (codeblock->next_true->empty or codeblock->next_true->meat[0]._while_cond)) {
                //_asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_true, instruction_pointer));
                //instruction_pointer++;
            }
            break;
        case _CALL:
            translate_call(ins, codeblock);
            if (codeblock->next_true != nullptr and (codeblock->next_true->empty or codeblock->next_true->meat[0]._while_cond)) {
                //_asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_true, instruction_pointer));
                //instruction_pointer++;
            }
            break;
        case _ENDWHILE:
            
            break;
    }
    //translacja ID := ID + ID;
    //architecture.assert_var("a");
    //architecture.assert_var("b");
    //architecture.assert_var("c");
    //log.log("utoworzono rejestry zmiennych a b c");
    //_asm_instructions.push_back(AsmInstruction("LOAD", architecture.get_register("b")));
    //_asm_instructions.push_back(AsmInstruction("ADD", architecture.get_register("c")));
    //_asm_instructions.push_back(AsmInstruction("STORE", architecture.get_register("a")));
}

void DirectedGraph::add_vertexx(int v_id) {
    vertices.push_back(CodeBlock(v_id));
}

CodeBlock* DirectedGraph::get_vertexx(int v_id) {
    if (v_id == 5) {
        std::cout << "handled\n";
    }
    if (v_id == -1) {
        log.log("aha");
        return nullptr;
    }
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].id == v_id) {
            return &vertices[i];
        }
    }
    //log.log("aha");
    
    //throw "no bitches :((";
}

void DirectedGraph::add_edge(int v_id, int u_id) {
    try {
        get_vertexx(v_id)->next_true_id = u_id;
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}
void DirectedGraph::add_edge(int v_id, int u_id, bool flag) {
    try {
        if (flag) {
            get_vertexx(v_id)->next_true_id = u_id;
        } else {
            get_vertexx(v_id)->next_false_id = u_id;
            std::cout << "dodalem" << u_id << std::endl;
        }
        
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}
void DirectedGraph::populate_neighbours(CodeBlock* codeblock, std::string proc_id) {
   if (codeblock != nullptr and codeblock->visited == 0) {
        codeblock->proc_id = proc_id;
        codeblock->visited = 1;
        populate_neighbours(codeblock->next_true, proc_id);
        populate_neighbours(codeblock->next_false, proc_id);
   }
   /*
   if (codeblock->visited) { and codeblock->visited == 0
       return 1;
   } else {
       log.log(*codeblock);
       codeblock->visited = 1;
       codeblock->proc_id = proc_id;
       log.log("zaraz zaczne");
       std::cout << "zaraz zaczne\n";
       if (codeblock->next_true_id != -1) {
               std::cout << "wszedlem " << codeblock->next_true_id << std::endl;

             codeblock->next_true = get_vertexx(codeblock->next_true_id);
             int x =  1 + populate_neighbours(codeblock->next_true, proc_id);
       } 
       std::cout << "wyszedlem " << codeblock->next_false_id << std::endl;
       if (codeblock->next_false_id != -1) {
            std::cout << "zaludnilem\n";
            codeblock->next_false = get_vertexx(codeblock->next_false_id);
            int x = 1 + populate_neighbours(codeblock->next_false, proc_id);
       }
       if (codeblock->next_false_id == -1 and codeblock->next_true_id == -1) {
            log.log("dodaje koncowy do codeblocka: ", codeblock->id);
            
            codeblock->last = 1;
           
            return 1;
       }
       
   }*/
}
void DirectedGraph::transform() {
    CodeBlock* tmp;
    for (auto v : vertices) {
        std:: cout << v.next_false_id << "   ";
    }
    //std::cout << get_vertexx(5)->id << "  ###\n";
    
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].next_true = get_vertexx(vertices[i].next_true_id);
        vertices[i].next_false = get_vertexx(vertices[i].next_false_id);
        if (vertices[i].next_false_id == -1 and vertices[i].next_true_id == -1) {
            vertices[i].last = 1;;
        }
    }
    for (auto head : head_map) {
        tmp = get_vertexx(head.first);
        //std::cout << "glowa no        " << head.first << "id: " << head.second << std::endl;
        populate_neighbours(tmp, head.second);
    }
    for (auto v : vertices) {
        std :: cout << v.id << "        " << v.proc_id << std::endl;
    }
    std::cout << "skonczylem transformacje\n";
    save_to_csv("/tmp/graphs");
}

void DirectedGraph::save_to_csv(std::string path) {
        std::ofstream outdata_v;
        std::ofstream outdata_e;
        outdata_v.open(path + "/graph_v.csv");
        outdata_e.open(path + "/graph_e.csv");
        outdata_v << "v" << ";" << std::endl;
        outdata_e << "e1" << ";" << "e2" << std::endl;
        for (auto vertex : vertices) {
            outdata_v << vertex.id << ";" << std::endl;
        }
        outdata_v.close();
        /*for (auto edge : edges) {
            outdata_e << edge.u->label << ";" << edge.v->label << std::endl;
            
        }*/
        for (int i = 0; i < vertices.size(); i++) {
            //for (int j = 0; j < vertices[i].neighbours.size(); j++) {
              //  outdata_e << vertices[i].id << ";" << vertices[i].neighbours[j] << std::endl;
                //std::cout << vertices[i].id << ";" << vertices[i].neighbours[j] << std::endl;
            //}
            if (vertices[i].next_true != nullptr) {
                outdata_e << vertices[i].id << ";" << vertices[i].next_true->id <<std::endl;
            }
            if (vertices[i].next_false != nullptr) {
                outdata_e << vertices[i].id << ";" << vertices[i].next_false->id <<std::endl;
            }
            
        }
        outdata_e.close();
}
void DirectedGraph::translate_snippet(CodeBlock* codeblock) {



    log.log("trans");
    if (codeblock == nullptr or codeblock->translated) {
        return;
    } else {
        
        //std::cout <<"adres"<< codeblock << std::endl;;
        codeblock->ip = instruction_pointer;    //stad bede wiedzial gdzie skakac
        for (auto instruction : codeblock->meat) {
            translate_ins(instruction, codeblock);
            log.log("tlumacze instrukcje w codeblocku: ", codeblock->id);
        }
        codeblock->translated = 1;
        log.log("before if");
        //log.log("size ", codeblock->nbrs_ptrs.size());
        if (codeblock->next_true == nullptr) {
            log.log("trafilem na koniec");
            if (codeblock->proc_id == "main") {
                _asm_halt(codeblock);
            } else {
                log.log("w procedurze");
                _asm_jump_i(codeblock->proc_id);
            }
            log.log("wracam");
            //return;
        } else {
            if (codeblock->empty) {
                codeblock->translated = false;
                _asm_instructions.push_back(AsmInstruction("JUMP", codeblock->next_true, instruction_pointer));
                instruction_pointer++;
            }
            log.log("after if");
            translate_snippet(codeblock->next_true);
            translate_snippet(codeblock->next_false);
        }

    }
    log.log("aaaa");
}
void DirectedGraph::translate_main() {
    //architecture.assert_const("c_1");
    //architecture.assert_ops();
    architecture.initialize_mul_registers();
    architecture.initialize_div_registers();
    

    _asm_set_op_constants();
    _asm_set_external_constants();
    for (auto it : head_map) {
        if (it.second == "main") {
            auto head = get_vertexx(it.first);
            std::cout << "numerek " << it.first << std::endl;
            _asm_instructions.push_back(AsmInstruction("JUMP", head, instruction_pointer));
            instruction_pointer++;
        }
    }
    for (auto it : head_ids) {
        log.log("tlumacze head z id: ", it);
        auto head = get_vertexx(it);
        
        
        translate_snippet(head);
    }
    log.log("------teraz skoski-------");
    resolve_jumps();
    for (auto asmins : _asm_instructions) {
        if (asmins.jump_address == -1) {
            if (asmins._register != nullptr) {
                //log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins._register->id) + asmins.constant + asmins.label);
                log.log( "   " + asmins.code + "        " + std::to_string(asmins.reg_id) + asmins.constant + asmins.label);
            } else {
                //log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " +asmins.constant + asmins.label);
                           log.log("   " + asmins.code + "        " +asmins.constant + asmins.label);

            }
        } else {
                //log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins.jump_address) + asmins.constant + asmins.label);
                   log.log("   " + asmins.code + "        " + std::to_string(asmins.jump_address) + asmins.constant + asmins.label);

        }
    }

}

void DirectedGraph:: resolve_jumps() {
    for (int i = 0; i < _asm_instructions.size(); i++) {
        if (_asm_instructions[i].codeblock != nullptr) {
            //
            _asm_instructions[i].jump_address = _asm_instructions[i].codeblock->ip;
        }
    }
    
}

void DirectedGraph::save_code(std::string out) {
    output.open(out + ".mr");
    for (auto asmins : _asm_instructions) {
        if (asmins.jump_address == -1) {
            if (asmins._register != nullptr) {
                //log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins._register->id) + asmins.constant + asmins.label);
                output <<  "   " + asmins.code + "        " + std::to_string(asmins.reg_id) + asmins.constant + asmins.label << std::endl;
            } else {
                //log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " +asmins.constant + asmins.label);
                           output << "   " + asmins.code + "        " +asmins.constant + asmins.label << std::endl;;

            }
        } else {
                //log.log(std::to_string(asmins.ip) + "   " + asmins.code + "        " + std::to_string(asmins.jump_address) + asmins.constant + asmins.label);
                   output << "   " + asmins.code + "        " + std::to_string(asmins.jump_address) + asmins.constant + asmins.label << std::endl;

        }
    }
    output.close();
}