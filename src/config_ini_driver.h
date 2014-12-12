#ifndef __SERENE_CONFIG_INI_DRIVER_H__
#define __SERENE_CONFIG_INI_DRIVER_H__

#include <string>
#include <vector>

class CalcContext;

namespace serene {

class ConfigIniScanner;

class ConfigIniDriver
{
    public:
        ConfigIniDriver(class CalcContext& calc);

        bool trace_scanning;

        bool trace_parsing;

        std::string streamname;

        bool parse_stream(std::istream& in,
                          const std::string& sname = "stream input");

        bool parse_string(const std::string& input,
                          const std::string& sname = "string stream");

        bool parse_file(const std::string& filename);

        void error(const class location& l, const std::string& m);

        void error(const std::string& m);

        class ConfigIniScanner* lexer;

        class CalcContext& calc;
};

} // namespace serene

#endif // __SERENE_CONFIG_INI_DRIVER_H__
