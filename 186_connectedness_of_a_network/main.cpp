#include <iostream>
#include <vector>

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

int solution(const int NUMBER, const int p) {
  std::vector<int> S;
  initialize_S(S);

  std::vector<int> people(1000000, 0);
  std::vector<std::vector<int>> groups(1000000, std::vector<int>());
  int group = 1;
  auto call = get_next_call(S);
  int calls = 1;
  int prime_minister_friends = 0;
  bool minister_called = false;
  while (prime_minister_friends < p * 10000) {
    if (people[call.first] == 0 and people[call.second] == 0) {
      people[call.first] = group;
      people[call.second] = group;
      groups[group].push_back(call.first);
      groups[group].push_back(call.second);
      group++;
    } else if (people[call.first] == 0) {
      people[call.first] = people[call.second];
      groups[people[call.second]].push_back(call.first);
    } else if (people[call.second] == 0) {
      people[call.second] = people[call.first];
      groups[people[call.first]].push_back(call.second);
    } else if (people[call.first] != people[call.second]) {
      int group_second = people[call.second];
      std::vector<int> people_in_second_group = groups[group_second];
      for (int person : people_in_second_group) {
        people[person] = people[call.first];
        groups[people[call.first]].push_back(person);
      }
      groups[group_second].clear();
    }

    if (!minister_called && (call.first == NUMBER || call.second == NUMBER)) {
      minister_called = true;
    }
    if (minister_called) {
      if (groups[people[NUMBER]].size() > 10) {
        auto a = people[NUMBER];
        auto b = groups[a];
      }
      prime_minister_friends = groups[people[NUMBER]].size();
    }
    call = get_next_call(S);
    while (call.first == call.second) {
      call = get_next_call(S);
    }
    calls++;
  }
  return calls;
}

int main() {
  int NUMBER, p;
  std::cin >> NUMBER >> p;
  std::cout << solution(NUMBER, p);
}
