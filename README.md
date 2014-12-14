flex-bison-cpp-example
======================

This project is forked from: Flex Bison C++ Template/Example
(https://github.com/bingmann/flex-bison-cpp-example)

The changes wrt the forked repository are:
- Replace autotools build system with cmake
- Reduced parser and scanner to the bare minimum, so it can be used as a
  simple starting point for developing C++ grammars (removed expression)
- The grammar is simple; it reads only "IDENTIFIER = INTEGER"
- Code formatting according to google style guide (not tested yet)
- The parser and scanner make calls to the main class (config_ini)
