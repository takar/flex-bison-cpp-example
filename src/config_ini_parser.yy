/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="serene"

/* set the parser's class identifier */
%define "parser_class_name" "ConfigIniParser"

/* keep track of the current position within the input */
%locations

/* The driver is passed by reference to the parser and to the scanner. */
%parse-param { class ConfigIniDriver& driver }

/* verbose error messages */
%error-verbose

%union {
    int                integerVal;
    std::string*       stringVal;
}

%token                 END      0    "end of file"
%token                 EOL           "end of line"
%token <integerVal>    INTEGER       "integer"
%token <stringVal>     STRING        "string"

%destructor { delete $$; } STRING

%{

#include "config_ini_driver.h"
#include "config_ini_scanner.h"

#undef yylex
#define yylex driver.scanner->lex

%}

%% /*** Grammar Rules ***/

start : /* empty */
    | start EOL
    | start STRING '=' INTEGER EOL
    {
         driver.statement(*$2, $4);
    }
    | start STRING '=' INTEGER END
    {
         driver.statement(*$2, $4);
    }

%% /*** Additional Code ***/

void
serene::ConfigIniParser::error(const ConfigIniParser::location_type& l,
                               const std::string& m) {
    driver.error(l, m);
}
