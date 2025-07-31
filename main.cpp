#include <chrono>
#include <iostream>
#include <string>
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

    dlerror();
    void* handle = dlopen("/media/inyourface34445/New Volume/Projects/scratch_drm/build/libDRM.so", RTLD_NOW);
    if (!handle) {
        std::cerr << "Error loading dll: " << dlerror() << std::endl;
        exit(1);
    }

    bool (*verify)() = (bool (*)())dlsym(handle, "_Z6verifyv");

    if (verify == nullptr || !verify()) {
        std::cerr << "3: failed" << std::endl;
        exit(1);
    }

    std::string input;
    if (argc >= 2) {
        input = argv[1];
    }

    if (check(input)) {
        std::cout << "got it!" << std::endl;
    } else {
        std::cout << "nope " << std::endl;
    }
}