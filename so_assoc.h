//
// Created by inyourface34445 on 7/30/25.
//

#ifndef SO_ASSOC_H
#define SO_ASSOC_H
extern "C" {
    extern const unsigned char _binary_libDRM_so_start[];
    extern const unsigned char _binary_libDRM_so_end[];
    extern const unsigned int _binary_libDRM_so_size;
}
std::string libDRM_so(reinterpret_cast<const char*>(_binary_libDRM_so_start),
                      reinterpret_cast<const char*>(_binary_libDRM_so_end));
#endif //SO_ASSOC_H
