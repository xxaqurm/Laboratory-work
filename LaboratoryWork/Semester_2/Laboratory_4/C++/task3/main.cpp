#include <iostream>
#include <cstdint>
#include <ctime>

using namespace std;

uint32_t xorshift32(uint32_t &seed) {
    // XORShift32
    seed ^= seed << 16;
    seed ^= seed >> 21;
    seed ^= seed << 11;
    return seed;
}

int main() {
    time_t t = time(0);
    uint32_t seed = t;

    for (int i = 0; i < 10; i++) {
        uint32_t rnd = xorshift32(seed);
        cout << "Случайное число: " << rnd << endl;
    }
}
