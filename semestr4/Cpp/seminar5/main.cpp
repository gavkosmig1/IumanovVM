#include <iostream>
#include <cmath>

unsigned long long fact(unsigned long long n) {
    if (n == 0 || n == 1)
        return 1;
    return n * fact(n - 1);
}


namespace detail {
    template <unsigned long N>
    struct factorial_impl {
        static constexpr unsigned long long value = N * factorial_impl<N - 1>::value;
    };

    template <>
    struct factorial_impl<0> {
        static constexpr unsigned long long value = 1;
    };
}

template <unsigned long N>
constexpr unsigned long long factorial = detail::factorial_impl<N>::value;

unsigned long crc32(const unsigned char *buff, unsigned long size) {
    unsigned long crc = 0;
    unsigned long crc_table[256];

    for (int i = 0; i < 256; ++i) {
        crc = i;
        for (int j = 0; j < 8; ++j) {
            crc = (crc & 1) ? (crc >> 1) ^ 0xEDB88320 : (crc >> 1);
        crc_table[i] = crc;
        }
    }

    crc = 0xffffffffUL;

    while (--size)
        crc = crc_table[(crc ^ *(buff++)) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xffffffffUL;
}


namespace detail {
    template <unsigned long I>
    constexpr unsigned long _coef = (I & 1) ? (I >> 1) ^ 0xEDB88320 : (I >> 1);
}

int main() {
    constexpr double pi_ = std::atan(1.) * 4;
    std::cout << fact(17) << std::endl;
    std::cout << factorial<17> << std::endl;

    const char *str = "Возми еще этих сладких французких булокчек, да выпей чаю!";

    std::cout << crc32(str, sizeof(str)) << std::endl;

}