#include <elfio/elfio.hpp>
#include <openssl/sha.h>
#include <iomanip>
#include <chrono>
#include <fstream>
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

    if (!reader.load("/proc/self/exe")) {
        return false;
    }

    auto start = std::chrono::high_resolution_clock::now();
    const ELFIO::Elf_Half sec_num = reader.sections.size();
    for ( int i = 0; i < sec_num; ++i ) {
        const ELFIO::section* psec = reader.sections[i];
        if (psec->get_name() == ".text") {
            const auto hash = sha256(psec->get_data(), psec->get_size());
            auto now = std::chrono::high_resolution_clock::now();
            if (hash == og_hash) {
                if (now-start > std::chrono::microseconds(1200)) {
                    std::cerr << "2: failed "  << now-start << std::endl;
                    exit(1);
                }
                return false;
            }
            return true;
        }
    }
    return true;
}

bool tracer_id() {
    auto proc_self = std::fstream("/proc/self/status", std::fstream::in);
    std::ostringstream buffer;
    buffer << proc_self.rdbuf();
    std::string file_content = buffer.str();
    proc_self.close();

    int counter = 0;
    int c7 = 0;
    int c8 = 0;
    for (int i = 0; i < file_content.size()-1; i++) {
        if (file_content[i] == '\n')
        {
            counter++;
            if (counter == 7) {
                c7 = i;
                continue;
            } else if (counter == 8) {
                c8 = i;
                break;
            }
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string tracer_id = file_content.substr(c7, c8-c7);
    int tracer_pid = stoi(tracer_id.substr(tracer_id.find(':'), 3).erase(0, 2));
    auto now = std::chrono::high_resolution_clock::now();
    if (now-start > std::chrono::microseconds(5))
    {
        std::cerr << "5: failed "  << now-start << std::endl;
        exit(1);
    }
    if (tracer_pid == 0 || tracer_pid == getpid())
    {
        return false;
    }
    return true;
}