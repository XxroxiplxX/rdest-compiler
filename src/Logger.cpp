#include "../include/Logger.h"
namespace Logging {

    void Logger::log(std::string msg) {
        //log_list.push_back(msg);
        output << msg << std::endl;
        //std::cout << "                                  dzialam" << std::endl;
    }
    void Logger::log(std::string msg, int param) {
        output << msg << param << std::endl;
    }
    void Logger::log(CodeBlock cb) {
        output << "************************************\n";
        output << "********#codeblock id : " << cb.id << std::endl;
        output << "--------next_true: " << cb.next_true_id << std::endl;
        output << "--------next_false: " << cb.next_false_id << std::endl;
        for (auto it : cb.meat) {
            output << "@@@@Loading instuction...\n";
            output << "type_of_instruction: " << it.type_of_instruction << std::endl;
            output << "type_of_operator: " << it.type_of_operator << std::endl;
            output << "###Loading Value left...\n";
            output << "$val type: "<< it.left.type << std::endl;
            output << "$val load: "<< it.left.load << std::endl;
            output << "###Loading Value right...\n";
            output << "$val type: "<< it.right.type << std::endl;
            output << "$val load: "<< it.right.load << std::endl;
            output << "###Loading Expression...\n";
            output << it.expr.exp_to_string() << std::endl;
            output << "###Loading args...\n";
            for (auto item : it.args) {
                output << item.val_to_string() << "   ";
            }
            output << "\n";
        }
        output << "************************************\n";
    }
}