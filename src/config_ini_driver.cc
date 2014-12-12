#include <fstream>
#include <sstream>

#include "config_ini_driver.h"
#include "config_ini_scanner.h"

namespace serene {

ConfigIniDriver::ConfigIniDriver(class CalcContext& _calc)
    : trace_scanning(false), trace_parsing(false), calc(_calc) { }

bool
ConfigIniDriver::parse_stream(std::istream& in, const std::string& sname) {
    streamname = sname;

    serene::ConfigIniScanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    serene::ConfigIniParser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool
ConfigIniDriver::parse_file(const std::string &filename) {
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parse_stream(in, filename);
}

bool
ConfigIniDriver::parse_string(const std::string &input,
                              const std::string& sname) {
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void
ConfigIniDriver::error(const class location& l,
        const std::string& m) {
    std::cerr << l << ": " << m << std::endl;
}

void
ConfigIniDriver::error(const std::string& m) {
    std::cerr << m << std::endl;
}

} // namespace serene
