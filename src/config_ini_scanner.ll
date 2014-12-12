%{ /*** C/C++ Declarations ***/

#include <string>

#include "config_ini_scanner.h"

/* import the parser's token type into a local typedef */
typedef serene::ConfigIniParser::token token;
typedef serene::ConfigIniParser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ConfigIniFlexLexer" */
%option prefix="ConfigIni"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}

\-?[0-9]+ {
    yylval->integerVal = atoi(yytext);
    return token::INTEGER;
}

 /* gobble up white-spaces */
[ \t\r]+ {
    yylloc->step();
}

 /* gobble up end-of-lines */
\n {
    yylloc->lines(yyleng); yylloc->step();
    return token::EOL;
}

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

%% /*** Additional Code ***/

serene::ConfigIniScanner::ConfigIniScanner(std::istream* in,
    std::ostream* out) : ConfigIniFlexLexer(in, out) { }

void
serene::ConfigIniScanner::set_debug(bool b) {
    yy_flex_debug = b;
}

#ifdef yylex
#undef yylex
#endif

int ConfigIniFlexLexer::yylex() {
    std::cerr << "in ConfigIniFlexLexer::yylex() !" << std::endl;
    return 0;
}

int ConfigIniFlexLexer::yywrap()
{
    return 1;
}
