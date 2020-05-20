#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>


int convert_from_base10(int val, int base) {
    int val_base = 0;
    int multiplier = 1;
    while (val != 0) {
        val_base += (val % base) * multiplier;
        val /= base;
        multiplier *= 10;
    }
    return val_base;
}

TEST(convert_from_base10, case_0) {
    EXPECT_EQ(convert_from_base10(10, 2), 1010);
}

bool is_palindrome(int val, int base) {
    if (base != 10) {
        val = convert_from_base10(val, base);
    }

    int val_copy = val;
    std::vector<int> val_digits;
    while (val_copy != 0) {
        val_digits.push_back(val_copy % 10);
        val_copy /= 10;
    }
    std::vector<int> val_digit_reversed = val_digits;
    std::reverse(val_digit_reversed.begin(), val_digit_reversed.end()); 
    return val_digits == val_digit_reversed;
}

TEST(is_palindrome, case_0) {
    EXPECT_TRUE(is_palindrome(515, 10));
    EXPECT_TRUE(is_palindrome(1001, 10));
    EXPECT_TRUE(is_palindrome(1, 10));
    EXPECT_FALSE(is_palindrome(1101, 10));
}

int solution(int N, int K) {
    int sum{0};
    for (int i = 1; i < N; i++) {
        if (is_palindrome(i, 10) && is_palindrome(i, K)) {
            sum += i;
        }
    }
    return sum;
}

TEST(solution, case_0) {
    EXPECT_EQ(solution(10, 2), 25);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}