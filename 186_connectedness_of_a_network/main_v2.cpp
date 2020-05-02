// This solution is based on idea described in https://euler.stephan-brumme.com/186/

#include <iostream>
#include <vector>

struct Person {
  int root;
  int friends;
};

std::vector<Person> people;

void initialize_S(std::vector<int> &S) {
  S.push_back(0);
  long a, b, c;
  a = 100003;

  for (long i = 1; i <= 55; i++) {
    b = 200003 * i;
    c = 300007 * i * i * i;
    S.push_back((a - b + c) % 1000000);
  }
}

std::pair<int, int> get_next_call(std::vector<int> &S) {
  int len = S.size();
  S.push_back((S[len - 24] + S[len - 55]) % 1000000);
  len++;
  S.push_back((S[len - 24] + S[len - 55]) % 1000000);

  static int n = 1;
  int caller = S[2 * n - 1];
  int called = S[2 * n];
  n++;

  return std::pair<int, int>(caller, called);
}

int root(int number) {
  int i = number;
  while (true) {
    int current_root = people[i].root;
    if (current_root == i) {
      people[number].root = current_root;
      return current_root;
    }
    i = current_root;
  }
}

void process(int caller, int called) {
  int root_caller = root(caller);
  int root_called = root(called);
  if (root_caller == root_called) {
    return;
  }
  if (people[root_caller].friends >= people[root_called].friends) {
    people[root_caller].friends += people[root_called].friends;
    people[root_called].root = root_caller;
  } else {
    people[root_called].friends += people[root_caller].friends;
    people[root_caller].root = root_called;
  }
}

int solution(const int NUMBER, const int p) {
  std::vector<int> S;
  initialize_S(S);
  people.reserve(1000000);
  for (int i = 0; i < 1000000; i++) {
    people[i] = Person{i, 1};
  }
  int calls = 0;
  while (people[root(NUMBER)].friends < 10000 * p) {
    auto call = get_next_call(S);
    while (call.first == call.second) {
      call = get_next_call(S);
    }
    calls++;
    process(call.first, call.second);
  }
  return calls;
}

int main() {
  int NUMBER, p;
  std::cin >> NUMBER >> p;
  std::cout << solution(NUMBER, p);
}
