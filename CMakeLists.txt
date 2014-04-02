cmake_minimum_required( VERSION 2.8.0 )

project( serene )

enable_testing()

find_package( bison REQUIRED )
find_package( flex REQUIRED )

# Create source directory for generated files
file( MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/generated )

# Define Parser and Scanner targets
bison_target( Parser ${CMAKE_CURRENT_SOURCE_DIR}/src/config_ini_parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/config_ini_parser.cc )
flex_target( Scanner ${CMAKE_CURRENT_SOURCE_DIR}/src/scanner.ll ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/scanner.cc )
add_flex_bison_dependency( Scanner Parser )

# Build parser library
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src/generated )
set( SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/config_ini_driver.cc ${FLEX_Scanner_OUTPUTS} ${BISON_Parser_OUTPUTS} )
set( TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/exprtest.cc )
add_library( serene-parser STATIC ${SRC_FILES} )

# Build tests
add_executable( sereneTest ${TEST_SRC_FILES} )
target_link_libraries( serene-parser )
target_link_libraries( sereneTest serene-parser )
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/exprtest.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
add_test( sereneTest sereneTest exprtest.txt )
