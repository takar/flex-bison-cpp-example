#ifndef __SERENE_CONFIG_SCANNER_H__
#define __SERENE_CONFIG_SCANNER_H__

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define	YY_DECL						\
    serene::Config_Ini_Parser::token_type				\
    serene::Scanner::lex(				\
	serene::Config_Ini_Parser::semantic_type* yylval,		\
	serene::Config_Ini_Parser::location_type* yylloc		\
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer ExampleFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include "config_ini_parser.hh"

namespace serene {

/** Scanner is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to ExampleFlexLexer. However we change the context of the generated
 * yylex() function to be contained within the Scanner class. This is required
 * because the yylex() defined in ExampleFlexLexer has no parameters. */
class Scanner : public ExampleFlexLexer
{
public:
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex(). */
    Scanner(std::istream* arg_yyin = 0,
	    std::ostream* arg_yyout = 0);

    /** Required for virtual functions */
    virtual ~Scanner();

    /** This is the main lexing function. It is generated by flex according to
     * the macro declaration YY_DECL above. The generated bison parser then
     * calls this virtual function to fetch new tokens. */
    virtual Config_Ini_Parser::token_type lex(
	Config_Ini_Parser::semantic_type* yylval,
	Config_Ini_Parser::location_type* yylloc
	);

    /** Enable debug output (via arg_yyout) if compiled into the scanner. */
    void set_debug(bool b);
};

} // namespace serene

#endif // __SERENE_CONFIG_SCANNER_H__
