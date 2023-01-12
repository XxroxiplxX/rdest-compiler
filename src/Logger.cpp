#include "../include/Logger.h"
namespace Logging {

    void Logger::log(std::string msg) {
        //log_list.push_back(msg);
        output << msg << std::endl;
        std::cout << "                                  dzialam" << std::endl;
    }
    void Logger::log(std::string msg, int param) {
        output << msg << param << std::endl;
    }
}