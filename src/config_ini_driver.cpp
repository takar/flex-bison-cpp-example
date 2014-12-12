#include <fstream>
#include <sstream>

#include "config_ini_driver.h"
#include "config_ini_scanner.h"

serene::ConfigIniDriver::ConfigIniDriver()
    : trace_scanning(false), trace_parsing(false) { }

bool
serene::ConfigIniDriver::parse_stream(std::istream& in,
                                      const std::string& sname) {
    streamname = sname;

    serene::ConfigIniScanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->scanner = &scanner;

    serene::ConfigIniParser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool
serene::ConfigIniDriver::parse_string(const std::string &input,
                                      const std::string& sname) {
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void
serene::ConfigIniDriver::print(int i) {
    std::cout << "Got an int: " << i << std::endl;
}

void
serene::ConfigIniDriver::error(const class location& loc,
        const std::string& msg) {
    std::cerr << loc << ": " << msg << std::endl;
}

void
serene::ConfigIniDriver::error(const std::string& msg) {
    std::cerr << msg << std::endl;
}
