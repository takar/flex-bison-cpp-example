cmake_minimum_required(VERSION 2.8)

project(serene)

FIND_PACKAGE(BISON REQUIRED)
FIND_PACKAGE(FLEX REQUIRED)

file(MAKE_DIRECTORY ${serene_SOURCE_DIR}/src/generated)
BISON_TARGET(Parser ${serene_SOURCE_DIR}/src/parser.yy ${serene_SOURCE_DIR}/src/generated/parser.cc)
FLEX_TARGET(Scanner ${serene_SOURCE_DIR}/src/scanner.ll ${serene_SOURCE_DIR}/src/generated/scanner.cc)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

INCLUDE_DIRECTORIES(${serene_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${serene_SOURCE_DIR}/src/generated)
SET(SRC_FILES ${serene_SOURCE_DIR}/src/driver.cc ${serene_SOURCE_DIR}/src/exprtest.cc ${FLEX_Scanner_OUTPUTS} ${BISON_Parser_OUTPUTS})
ADD_EXECUTABLE (sereneTest ${SRC_FILES})
