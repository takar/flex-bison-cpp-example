#ifndef __SERENE_CONFIG_INI_H__
#define __SERENE_CONFIG_INI_H__

#include <map>
#include <string>

namespace serene {

class ConfigIniScanner;

class ConfigIni {
 public:
    typedef std::map<std::string, int> data_t;

    ConfigIni();

    bool trace_scanning;

    bool trace_parsing;

    data_t parse_stream(std::istream& in);

    data_t parse_string(const std::string& input);

    void statement(const std::string& key, int value);

    void error(const class location& l, const std::string& m);

    void error(const std::string& m);

    class ConfigIniScanner* scanner;

 private:
    data_t data_;
};

}  // namespace serene

#endif // __SERENE_CONFIG_INI_H__
