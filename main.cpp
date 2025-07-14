#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <iomanip>
#include "drm.cpp"

bool check(const std::string &input) {
    return input == std::string("not");
}

bool integerty_check() {
    auto file = std::fstream("/proc/" + std::to_string(getpid()) + "/exe", std::fstream::in);
    return true;
}

int main(const int argc, char *argv[]) {
    // init();
    integerty_check();
    std::string input;
    if (argc >= 2) {
        input = argv[1];
    }

    if (check(input)) {
        std::cout << "got it!" << std::endl;
    } else {
        std::cout << "nope" << std::endl;
    }
    std::cout << input << std::endl;
    std::cout << _binary_hash_txt_start << std::endl;
}