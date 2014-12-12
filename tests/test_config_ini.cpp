#include <iostream>

#include "config_ini.h"
#include <assert.h>
#include <map>

int main (int argc, char *argv[]) {
    serene::ConfigIni config_ini;
    serene::ConfigIni::data_t data;

    data = config_ini.parse_string("identifier = 3");
    assert(data.count("identifier") == 1);
    assert(data["identifier"] == 3);

    data = config_ini.parse_string("config = -3");
    assert(data.count("config") == 1);
    assert(data["config"] == -3);
}
