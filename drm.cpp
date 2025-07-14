#include <elfio/elfio.hpp>
#include <openssl/sha.h>
#include <iomanip>
#include "var_defs.h"

std::string sha256(const char input[], const unsigned long len) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Hash the input in one step
    SHA256(reinterpret_cast<const unsigned char*>(input), len, hash);

    std::stringstream ss;
    for (const unsigned char byte : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return ss.str();
}

bool integerty_check() {
    ELFIO::elfio reader;
    std::string og_hash(reinterpret_cast<const char*>(_binary_hash_txt_start));

    if (!reader.load("/proc/" + std::to_string(getpid()) + "/exe")) {
        std::cerr << "Segmentation fault (core dumped)" << std::endl;
        return false;
    }

    const ELFIO::Elf_Half sec_num = reader.sections.size();
    for ( int i = 0; i < sec_num; ++i ) {
        const ELFIO::section* psec = reader.sections[i];
        if (psec->get_name() == ".text") {
            const auto hash = sha256(psec->get_data(), psec->get_size());
            // std::cout << hash << std::endl;
            // std::cout << og_hash << std::endl;
            // std::cout << (hash == og_hash) << std::endl;
            if (hash == og_hash) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}