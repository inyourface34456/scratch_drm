#include <chrono>
#include <iostream>
#include <string>
#include <sys/ptrace.h>
#include "drm.h"
#include <linux/prctl.h>
#include <csignal>
#include <sys/prctl.h>

bool check(const std::string &input) {
    return input == std::string("not");
}

int main(const int argc, char *argv[]) {
    prctl(PR_SET_DUMPABLE, false);
    signal(SIGTRAP, exit);
    auto start = std::chrono::high_resolution_clock::now();
    if (integerty_check() || tracer_id() || ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
    {
        std::cerr << "3: failed" << std::endl;
        exit(1);
    }
    auto now = std::chrono::high_resolution_clock::now();
    if (now-start > std::chrono::microseconds(3550))
    {
        std::cerr << "1: failed"  << now-start << std::endl;
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