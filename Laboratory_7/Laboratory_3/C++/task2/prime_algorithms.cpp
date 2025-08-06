#include <iostream>
#include <random>
#include <cmath>
#include <set>

#include "utils.h"

using namespace std;
using ull = unsigned long long;

bool miller_test(ull n, int t) {
    /* Вероятностный тест Миллера */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, n - 1);

    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n < 10) return false;

    set<ull> nums;
    while ((int)nums.size() != t) {
        nums.insert(dist(gen));
    }

    for (auto& a : nums) {
        if (modPow(a, n - 1, n) != 1) {
            return false;
        }
    }

    vector<pair<int, int>> primeFactors = factorize(n - 1);
    for (auto& factor : primeFactors) {
        int q = factor.first;
        bool onlyOne = true;
        for (auto& a : nums) {
            if (modPow(a, (n - 1) / q, n) != 1) {
                onlyOne = false;
                break;
            }
        }
        if (onlyOne) {
            return false;
        }
    }
    return true;
}

bool pocklington_test(ull n, int t) {
    /* Вероятностный тест Поклингтона */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distR(1, 3);
    uniform_int_distribution<> distA(2, n - 1);

    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n < 10) return false;

    int r = distR(gen);
    vector<pair<int, int>> primeFactors = factorize((n - 1) / r);

    set<ull> nums;
    while ((int)nums.size() != t) {
        nums.insert(distA(gen));
    }

    for (auto& a : nums) {
        if (modPow(a, n - 1, n) != 1) {
            return false;
        }
    }

    for (auto& a : nums) {
        bool noOne = true;
        for (auto& factor : primeFactors) {
            int q = factor.first;
            if (modPow(a, (n - 1) / q, n) == 1) {
                noOne = false;
                break;
            }
        }
        if (noOne) {
            return true;
        }
    }
    return false;
}

pair<ull, int> miller_prime(int num_size, vector<int> primes) {
    /* Генерация простого числа с помощью теста Миллера */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distQ(0, primes.size() - 1);
    uniform_int_distribution<> distA(1, 20);
    
    ull n = 1;
    int failedMillerCount = -1;
    while (!miller_test(n, 8)) {
        int attemptCount = 0;
        ull m = 1;
        set<int> uniqQ;
        while (sizeNum(m) != num_size - 1) {
            int q = primes[distQ(gen)];
            int a = distA(gen);
            if (sizeNum(m * (int)pow(q, a)) <= num_size - 1 && uniqQ.find(q) == uniqQ.end()) {
                m *= (int)pow(q, a);
                uniqQ.insert(q);
            }
            if (++attemptCount == 100 && sizeNum(m) != num_size - 1) {
                m = 1;
                attemptCount = 0;
                uniqQ.clear();
            }
        }
        n = 2 * m + 1;
        failedMillerCount++;
    }
    return {n, failedMillerCount};
}

pair<ull, int> pocklington_prime(int num_size, vector<int> primes) {
    /* Генерация простого числа с помощью теста Поклингтона*/
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distQ(0, primes.size() - 1);
    uniform_int_distribution<> distA(1, 20);
    
    ull n = 1;
    int failedPocklingtonCount = -1;
    while (!pocklington_test(n, 8)) {
        int attemptCount = 0;
        ull f = 1;
        set<int> uniqQ;
        while (sizeNum(f) - 1 != num_size / 2) {
            int q = primes[distQ(gen)];
            int a = distA(gen);
            if (sizeNum(f * (int)pow(q, a)) - 1 <= num_size / 2) {
                f *= (int)pow(q, a);
                uniqQ.insert(q);
            }
            if (++attemptCount == 100 && sizeNum(f) - 1 != num_size / 2) {
                f = 1;
                attemptCount = 0;
                uniqQ.clear();
            }
        }
        ull r = f >> 1;
        if (r % 2) {
            r++;
        }
        n = r * f + 1;
        failedPocklingtonCount++;
    }
    return {n, failedPocklingtonCount};
}

pair<ull, int> gost_prime(int num_size, vector<int> primes) {
    /* Генерация простого числа с помощью ГОСТ Р34.10-94*/
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution read_dist(0.0, 1.0);

    if (num_size <= 1) return {0, 0};
    if (num_size == 2) return {3, 0};

    ull p = 0;
    ull n = 0;
    ull u = 0;
    ull q = miller_prime(ceil(num_size / 2), primes).first;
    while (true) {
        double e = read_dist(gen);
        n = ceil(pow(2, num_size - 1) / q) + ceil(pow(2, num_size - 1) * e / q);
        if (n % 2) {
            n++;
        }

        u = 0;
        p = (n + u) * q + 1;
        if (p <= (ull)pow(2, num_size)) {
            break;
        }
    }

    int failedGostCount = -1;
    while (!(modPow(2, p - 1, p) == 1 && modPow(2, n + u, p) != 1)) {
        u += 2;
        p = (n + u) * q + 1;
        failedGostCount++;
    }
    failedGostCount = failedGostCount == -1 ? 0 : failedGostCount;
    return {p, failedGostCount};
}