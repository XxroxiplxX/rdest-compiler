#ifndef LOGGER_H
#define LOGGER_H

#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
namespace Logging {
class Logger {
public:
  Logger(const std::string &filename) {
    file_.open(filename, std::ios::out | std::ios::app);
  }

  ~Logger() {
    if (file_.is_open()) {
      file_.close();
    }
  }

  template <typename... Args>
  void error(const char *format, const Args &...args) {
    std::ostringstream oss;
    logTimeStamp(oss);
    oss << "> ERR/";

    logHelper(oss, format, args...);
    writeToLogFile(oss.str());
  }

  template <typename... Args>
  void info(const char *format, const Args &...args) {
    std::ostringstream oss;
    logTimeStamp(oss);
    oss << "> INF/";

    logHelper(oss, format, args...);
    writeToLogFile(oss.str());
  }

  template <typename... Args>
  void warning(const char *format, const Args &...args) {
    std::ostringstream oss;
    logTimeStamp(oss);
    oss << "> WRN/";

    logHelper(oss, format, args...);
    writeToLogFile(oss.str());
  }
  void log(std::string s) {}
  void log(std::string s, int i) {}

private:
  std::ofstream file_;
  void logTimeStamp(std::ostringstream &oss) {
    // current date and time on the current system
    time_t now = time(0);

    tm *ltm = localtime(&now);
    oss << "<" << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-"
        << ltm->tm_mday << " T " << ltm->tm_hour << ":" << ltm->tm_min << ":"
        << ltm->tm_sec;
  }
  template <typename Arg>
  void processFormatSpecifier(std::ostringstream &oss, char specifier,
                              const Arg &arg) {
    switch (specifier) {
    case 'd':
      oss << arg;
      break;
    case 's':
      oss << arg;
      break;
    case 'f':
      oss << std::fixed << std::setprecision(2) << arg;
      break;
    default:
      oss << "###";
      break;
    }
  }

  template <typename Arg>
  void logHelper(std::ostringstream &oss, const char *format, const Arg &arg) {
    size_t len = strlen(format);

    for (size_t i = 0; i < len; ++i) {
      if (format[i] == '%' && (i + 1 < len)) {
        if (format[i + 1] == '%') {
          oss << '%';
          ++i;
        } else {
          processFormatSpecifier(oss, format[i + 1], arg);
          return; // Bazowy przypadek rekurencji - wszystkie argumenty zostały
                  // przetworzone
        }
      } else {
        oss << format[i];
      }
    }
  }

  template <typename Arg, typename... Rest>
  void logHelper(std::ostringstream &oss, const char *format, const Arg &arg,
                 const Rest &...rest) {
    size_t len = strlen(format);

    for (size_t i = 0; i < len; ++i) {
      if (format[i] == '%' && (i + 1 < len)) {
        if (format[i + 1] == '%') {
          oss << '%';
          ++i;
        } else {
          processFormatSpecifier(oss, format[i + 1], arg);
          logHelper(oss, format + i + 2, rest...);
          return; // Przerwij rekurencję po przetworzeniu argumentu
        }
      } else {
        oss << format[i];
      }
    }
  }

  void writeToLogFile(const std::string &message) {
    if (file_.is_open()) {
      file_ << message << std::endl;
    }
  }
};

} // namespace Logging
#endif