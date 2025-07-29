#include <chrono>
#include <iostream>
#include <string>
#include <sys/ptrace.h>
// #include "drm.h"
#include "bougus_math.h"
#include <linux/prctl.h>
#include <csignal>
#include <sys/prctl.h>
#include <dlfcn.h>

bool check(const std::string &input) {
    return input == std::string("not");
}

int main(const int argc, char *argv[]) {
    prctl(PR_SET_DUMPABLE, false);
    signal(SIGTRAP, exit);
    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long state = 0;
    dlerror();
    void* handle = dlopen("/media/inyourface34445/New Volume/Projects/scratch_drm/build/libDRM.so", RTLD_NOW);
    if (!handle) {
        std::cerr << "Error loading dll: " << dlerror() << std::endl;
    }

    bool (*tracer_id)() = (bool (*)())dlsym(handle, "_Z9tracer_idv");
    bool (*integerty_check)() = (bool (*)())dlsym(handle, "_Z15integerty_checkv");

    while (true) {
        switch (state) {
            case 0:
                if (integerty_check()) {
                    goto exit;
                }
                state += math(981, 12, 862, 517, 73, 460, 43, 707, 868);
                continue;
            case 1:
                if (tracer_id()) {
                    goto exit;
                }
                state += math(983, 268, 90, 316, 810, 268, 582, 441, 839);
                continue;
            case 2:
                if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
                    goto exit;
                }
                state += math(962, 915, 225, 793, 966, 234, 238, 503, 370);
                continue;
            case 3:
                goto good;
            default:
                break;
        }
    }
    exit:
    std::cerr << "3: failed" << std::endl;
    exit(1);
    good:
    auto now = std::chrono::high_resolution_clock::now();
    if (now-start > std::chrono::microseconds(3550))
    {
        std::cerr << "1: failed "  << now-start << std::endl;
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