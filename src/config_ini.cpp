#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>

#include "config_ini.h"
#include "config_ini_scanner.h"

serene::ConfigIni::ConfigIni()
    : trace_scanning(false), trace_parsing(false) { }

serene::ConfigIni::data_t
serene::ConfigIni::parse_stream(std::istream& in) {
    serene::ConfigIniScanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->scanner = &scanner;

    serene::ConfigIniParser parser(*this);
    parser.set_debug_level(trace_parsing);
    assert(parser.parse() == 0);
    return data_;
}

serene::ConfigIni::data_t
serene::ConfigIni::parse_string(const std::string &input) {
    std::istringstream iss(input);
    return parse_stream(iss);
}

void
serene::ConfigIni::statement(const std::string& identifier, int value) {
    std::cout << "identifier: " << identifier << ", "
                 "value: " << value << std::endl;
    data_.insert(std::make_pair(identifier, value));
}

void
serene::ConfigIni::error(const class location& loc,
        const std::string& msg) {
    std::cerr << loc << ": " << msg << std::endl;
}

void
serene::ConfigIni::error(const std::string& msg) {
    std::cerr << msg << std::endl;
}
