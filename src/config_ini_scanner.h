#ifndef __SERENE_CONFIG_INI_SCANNER_H__
#define __SERENE_CONFIG_INI_SCANNER_H__

#ifndef YY_DECL
# define YY_DECL                                          \
    serene::ConfigIniParser::token_type                   \
    serene::ConfigIniScanner::lex(                        \
        serene::ConfigIniParser::semantic_type* yylval,   \
        serene::ConfigIniParser::location_type* yylloc    \
    )
#endif

#ifndef __FLEX_LEXER_H
# define yyFlexLexer ConfigIniFlexLexer
# include "FlexLexer.h"
# undef yyFlexLexer
#endif

#include "config_ini_parser.hh"

namespace serene {

class ConfigIniScanner : public ConfigIniFlexLexer
{
 public:
    ConfigIniScanner(std::istream* arg_yyin = 0,
                     std::ostream* arg_yyout = 0);

    virtual ~ConfigIniScanner() { };

    virtual ConfigIniParser::token_type lex(
        ConfigIniParser::semantic_type* yylval,
        ConfigIniParser::location_type* yylloc
    );

    void set_debug(bool b);
};

} // namespace serene

#endif // __SERENE_CONFIG_INI_SCANNER_H__
