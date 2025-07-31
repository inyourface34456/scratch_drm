#include <chrono>
#include <iostream>
#include <string>
#include <linux/prctl.h>
#include <csignal>
#include <sys/prctl.h>
#include <dlfcn.h>
#include "so_assoc.h"
#include <sys/mman.h>
#include <unistd.h>

bool check(const std::string &input) {
    return input == std::string("not");
}

int main(const int argc, char *argv[]) {
    prctl(PR_SET_DUMPABLE, false);
    signal(SIGTRAP, exit);

    const int libDRM_fd = memfd_create("1", MFD_CLOEXEC);
    write(libDRM_fd, _binary_libDRM_so_start, _binary_libDRM_so_end - _binary_libDRM_so_start);

    dlerror();
    void* handle = dlopen((std::string("/proc/self/fd/") + std::to_string(libDRM_fd)).c_str(), RTLD_NOW);
    if (!handle) {
        std::cerr << "Error loading dll: " << dlerror() << std::endl;
        exit(1);
    }

    auto (*verify)() = (bool (*)())dlsym(handle, "_Z6verifyv");

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
    // std::cout << libDRM_hash << std::endl;
}