#ifndef PRIME_ALGORITHMS
#define PRIME_ALGORITHMS

using namespace std;
using ull = unsigned long long;

bool miller_test(ull elm, int t = 8);
bool pocklington_test(ull elm, int t = 8);

pair<ull, int> miller_prime(int num_size, vector<int> primes);
pair<ull, int> pocklington_prime(int num_size, vector<int> primes);
pair<ull, int> gost_prime(int num_size, vector<int> primes);

#endif