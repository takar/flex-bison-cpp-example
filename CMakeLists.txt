cmake_minimum_required( VERSION 2.8.0 )

project( serene )

enable_testing()

find_package( bison REQUIRED )
find_package( flex REQUIRED )

# Define Parser and Scanner targets
bison_target( Parser ${CMAKE_CURRENT_SOURCE_DIR}/src/config_ini_parser.yy ${CMAKE_CURRENT_BINARY_DIR}/config_ini_parser.cpp)
flex_target( Scanner ${CMAKE_CURRENT_SOURCE_DIR}/src/config_ini_scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/config_ini_scanner.cpp )
add_flex_bison_dependency( Scanner Parser )

# Build parser library
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
set( SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/config_ini.cpp ${FLEX_Scanner_OUTPUTS} ${BISON_Parser_OUTPUTS} )
set( TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_config_ini.cpp )
add_library( serene-parser STATIC ${SRC_FILES} )

# Build tests
add_executable( sereneTest ${TEST_SRC_FILES} )
target_link_libraries( serene-parser )
target_link_libraries( sereneTest serene-parser )
add_test( sereneTest sereneTest )
