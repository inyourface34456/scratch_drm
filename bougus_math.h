#ifndef BOUGUS_MATH_H
#define BOUGUS_MATH_H
__always_inline unsigned long long math_unit(const unsigned long long x, const unsigned long long a, const unsigned long long b) {
    return a*x+b;
}

unsigned long long math(const unsigned long long x, const unsigned long long a, const unsigned long long b, const unsigned long long c, const unsigned long long d, const unsigned long long e, const unsigned long long f, const unsigned long long g, const unsigned long long h) {
    return (((math_unit(x, a, b)*math_unit(x, c, d))/(math_unit(x, e, f)*math_unit(x, g, h)))*((math_unit(x, e, f)*math_unit(x, g, h))/(math_unit(x, a, b)*math_unit(x, c, d))))+1;
}
#endif //BOUGUS_MATH_H
