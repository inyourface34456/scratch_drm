#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "drm.h"

bool check(const std::string &input) {
    return input == std::string("not");
}

int main(const int argc, char *argv[]) {
    if (!integerty_check()) {
        std::cerr << "integerty_check failed" << std::endl;
        exit(1);
    }

    std::string input;
    if (argc >= 2) {
        input = argv[1];
    }

    if (check(input)) {
        std::cout << "got it!" << std::endl;
    } else {
        std::cout << "nope" << std::endl;
    }
}