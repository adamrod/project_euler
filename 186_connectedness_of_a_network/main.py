S = [0] * 10000000
for k in range(1, 56):
    S[k] = (100003 - 200003*k + 300007*k*k*k) % 1000000

for k in range(56, 10000000):
    S[k] = (S[k-24] + S[k-55]) % 1000000

n = 1
def get_next_call():
    global n
    caller = S[2*n - 1]
    called = S[2*n]
    n += 1
    return (caller, called)

def solution(NUMBER, p):
    people = [0] * 1000000
    groups = [[] for _ in range(1000000)]
    call = get_next_call()
    calls = 1
    group = 1
    prime_minister_friends = 0
    minister_called = False
    while (prime_minister_friends < p * 10000):
        if people[call[0]] == 0 and people[call[1]] == 0:
            people[call[0]] = group
            people[call[1]] = group
            groups[group].append(call[0])
            groups[group].append(call[1])
            group += 1
        elif people[call[0]] == 0:
            people[call[0]] = people[call[1]]
            groups[people[call[1]]].append(call[0])
        elif people[call[1]] == 0:
            people[call[1]] = people[call[0]]
            groups[people[call[0]]].append(call[1])
        elif people[call[0]] != people[call[1]]:
            group_to_delete = people[call[1]]
            for person in groups[group_to_delete]:
                people[person] = people[call[0]]
            groups[people[call[0]]] += groups[group_to_delete]
            groups[group_to_delete].clear()

        if not minister_called and (call[0] == NUMBER or call[1] == NUMBER):
            minister_called = True
        
        if minister_called:
            prime_minister_friends = len(groups[people[NUMBER]])

        call = get_next_call()
        while call[0] == call[1]:
            call = get_next_call()
        calls += 1
        
    return calls

print(solution(0, 1))
