#include <iostream>

#include "config_ini_driver.h"

int main (int argc, char *argv[]) {
    serene::ConfigIniDriver driver;

    for (int ai = 1; ai < argc; ++ai) {
        if (argv[ai] == std::string ("-p")) {
            driver.trace_parsing = true;
        }
        else if (argv[ai] == std::string ("-s")) {
            driver.trace_scanning = true;
        }
    }

    std::string line;
    while (std::cout << "input: " && std::getline(std::cin, line) &&
            !line.empty()) {
        bool result = driver.parse_string(line, "input");
    }
}
