#include <vector>
#include <iostream>
#include <algorithm>

bool is_pandigital(int i, int K) {
    std::vector<bool> digits(10, false);
    digits[0] = true;
    if (K == 8) digits[9] = true;

    int multiplier = 1;
    int result, modulo;
    while (std::any_of(digits.begin(), digits.end(), [](bool i){ return !i; }) && multiplier < 10) {
        result = i * multiplier;
        while (result != 0) {
            modulo = result % 10;
            if (digits[modulo]) {
                return false;
            }
            digits[modulo] = true;
            result /= 10;
        }
        multiplier++;
    }

    return std::all_of(digits.begin(), digits.end(), [](bool i){ return i; });
}

void solution(int N, int K) {
    for (int i = 2; i < N; i++) {
        if (is_pandigital(i, K)) {
            std::cout << i << "\n";
        }
    }
}

int main() {
    int N, K;
    std::cin >> N >> K;
    solution(N, K);
    return 0;
}
