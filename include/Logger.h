#include <fstream>
#include <iostream>
#include <vector>
namespace Logging {
    class Logger {
            std::vector<std::string> log_list;
            std::string file_name;
            std::ofstream output;
        public:
            Logger(std:: string filename) : file_name(filename) {
                output.open(file_name);
            }
            void log(std::string msg);\
            void log(std::string msg, int param);
            ~Logger() {
                output.close();
            }
            void close_logger() {
                for (auto it : log_list) {
                    std::cout << it << std::endl;
                }
                output.close();
            }
    };
}