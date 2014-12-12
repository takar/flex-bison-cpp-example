#ifndef __SERENE_CONFIG_INI_DRIVER_H__
#define __SERENE_CONFIG_INI_DRIVER_H__

#include <map>
#include <string>

namespace serene {

class ConfigIniScanner;

class ConfigIniDriver {
 public:
    ConfigIniDriver();

    bool trace_scanning;

    bool trace_parsing;

    std::string streamname;

    bool parse_stream(std::istream& in,
                      const std::string& sname = "stream input");

    bool parse_string(const std::string& input,
                      const std::string& sname = "string stream");

    void statement(const std::string& key, int value);

    void error(const class location& l, const std::string& m);

    void error(const std::string& m);

    class ConfigIniScanner* scanner;

 private:
    std::map<std::string, int> data;
};

} // namespace serene

#endif // __SERENE_CONFIG_INI_DRIVER_H__
