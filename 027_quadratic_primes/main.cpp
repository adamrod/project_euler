#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>


std::pair<int, int> get_coefficients(int N, const std::vector<int>& primes) {
    int a_result{1}, b_result{41};
    int max_consecutive_primes = 40;

    for (int i = 0, b = primes[i]; b <= N; b = primes[++i]) {
        for (int a = N % 2 ? -N: -N - 1; a <= N; a += 2) {
            int consecutive_primes = 1;
            for (int n = 1;;n++) {
                int val = n*n + a*n + b;
                auto it = std::lower_bound(primes.begin(), primes.end(), val);
                if (it != primes.end() && *it == val) {
                    consecutive_primes++;
                } else {
                    break;
                }
            }
            if (consecutive_primes > max_consecutive_primes) {
                max_consecutive_primes = consecutive_primes;
                a_result = a;
                b_result = b;
            }
        }
    }

    return std::pair<int, int>(a_result, b_result);
}


std::vector<int> get_primes(const int max) {
    std::vector<int> primes(max - 1);
    std::iota(primes.begin(), primes.end(), 2);

    for (auto it = primes.begin(); it != primes.end(); it++) {
        if (*it != 0) {
            for (int i = 1; *it * (1 + i) <= max; i++) {
                *(it + i * (*it)) = 0;
            }
        }
    }

    primes.erase(std::remove_if(primes.begin(), primes.end(),[](int x){ return x == 0; }), primes.end());

    return primes;
}


int main() {
    std::vector<int> primes = get_primes(20000);
    int N;
    std::cin >> N;
    auto coefficients = get_coefficients(N, primes);
    std::cout << coefficients.first << " " << coefficients.second << std::endl;
}