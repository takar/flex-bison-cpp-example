#include <iostream>

#include "config_ini_driver.h"
#include <assert.h>
#include <map>

int main (int argc, char *argv[]) {
    serene::ConfigIniDriver driver;
    serene::ConfigIniDriver::data_t data;

    data = driver.parse_string("identifier = 3");
    assert(data.count("identifier") == 1);
    assert(data["identifier"] == 3);

    data = driver.parse_string("config = -3");
    assert(data.count("config") == 1);
    assert(data["config"] == -3);
}
