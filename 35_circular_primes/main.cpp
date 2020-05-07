#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <numeric>
#include <vector>

std::vector<int> sieve_of_eratosthenes(const int max) {
  std::vector<int> primes(max - 2);
  std::iota(primes.begin(), primes.end(), 2);

  for (int i = 0; i < (primes.size() / 2); i++) {
    if (primes[i]) {
      for (int j = 2 * primes[i] - 2; j < primes.size(); j += primes[i]) {
        primes[j] = 0;
      }
    }
  }

  primes.erase(std::remove_if(primes.begin(), primes.end(),
                              [](int x) { return x == 0; }),
               primes.end());
  return primes;
}

bool contain_digits(int number, std::vector<int> &digits) {
  while (number != 0) {
    int curr_digit = number % 10;
    for (auto digit : digits) {
      if (curr_digit == digit) {
        return true;
      }
    }
    number /= 10;
  }
  return false;
}

std::vector<int> get_rotations(int n) {
  std::vector<int> rotations{};

  std::vector<int> digits;
  while (n != 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
  std::reverse(std::begin(digits), std::end(digits));

  for (int i = 0; i < digits.size() - 1; i++) {
    std::rotate(digits.begin(), digits.begin() + 1, digits.end());
    int value = 0;
    for (const auto &digit : digits) {
      value = value * 10 + digit;
    }
    rotations.push_back(value);
  }
  return rotations;
}

bool in_sorted_vector(const std::vector<int> &v, const int value) {
  auto it = std::lower_bound(v.begin(), v.end(), value);
  if (it != v.end() && *it == value) {
    return true;
  }
  return false;
}

void remove_primes_with_specific_digits(std::vector<int> &primes) {
  std::vector<int> not_circular_digits{0, 2, 4, 5, 6, 8};
  for (int i = 4; i < primes.size(); i++) {
    if (contain_digits(primes[i], not_circular_digits)) {
      primes[i] = 0;
      continue;
    }
  }
  primes.erase(std::remove_if(primes.begin(), primes.end(),
                              [](int x) { return x == 0; }),
               primes.end());
}

void remove_not_circular_primes(std::vector<int> &primes) {
  remove_primes_with_specific_digits(primes);
  
  std::vector<int> indexes_to_remove;
  for (int i = 4; i < primes.size(); i++) {
    auto rotations = get_rotations(primes[i]);
    for (auto rotation : rotations) {
      if (!in_sorted_vector(primes, rotation)) {
        indexes_to_remove.push_back(i);
        break;
      }
    }
  }

  for (auto index : indexes_to_remove) {
    primes[index] = 0;
  }

  primes.erase(std::remove_if(primes.begin(), primes.end(),
                              [](int x) { return x == 0; }),
               primes.end());
}

int sum_circular_primes(int N) {
  auto primes = sieve_of_eratosthenes(N);
  remove_not_circular_primes(primes);
  return std::accumulate(primes.begin(), primes.end(), 0);
}

TEST(sum_circular_primes, zero) {
    EXPECT_EQ(sum_circular_primes(100), 446);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}

