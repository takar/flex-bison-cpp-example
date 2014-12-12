#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>

#include "config_ini_driver.h"
#include "config_ini_scanner.h"

serene::ConfigIniDriver::ConfigIniDriver()
    : trace_scanning(false), trace_parsing(false) { }

serene::ConfigIniDriver::data_t
serene::ConfigIniDriver::parse_stream(std::istream& in) {
    serene::ConfigIniScanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->scanner = &scanner;

    serene::ConfigIniParser parser(*this);
    parser.set_debug_level(trace_parsing);
    assert(parser.parse() == 0);
    return data_;
}

serene::ConfigIniDriver::data_t
serene::ConfigIniDriver::parse_string(const std::string &input) {
    std::istringstream iss(input);
    return parse_stream(iss);
}

void
serene::ConfigIniDriver::statement(const std::string& identifier, int value) {
    std::cout << "identifier: " << identifier << ", "
                 "value: " << value << std::endl;
    data_.insert(std::make_pair(identifier, value));
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
