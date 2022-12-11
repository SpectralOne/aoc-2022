#include <bits/stdc++.h>
#define int long long
#define ROUNDS 10000

using namespace std;

class Monkey {
 public:
  int idx;
  vector<int> items;
  string op;
  int test;
  int true_i;
  int false_i;

  Monkey() : idx(-1) {}
  ~Monkey(){};
};

int M = 1;

vector<int> inspects(8, 0);

int apply(int wl, string op) {
  wl %= M;
  int operand;
  if (op[1] == 'o') {
    operand = wl;
  } else {
    sscanf(op.c_str() + 1, "%lld", &operand);
  }

  if (op[0] == '+') {
    wl += operand;
  } else {
    wl *= operand;
  }

  return wl %= M;
}

__int32_t main(const int argc, char **argv) {
  ifstream cin(argv[1]);

  string line;

  vector<Monkey> monkeys(8);
  int idx = 0;
  while (getline(cin, line)) {
    monkeys[idx].idx = idx;

    getline(cin, line);
    stringstream items(line);

    items >> line >> line;
    int item;
    while (items >> item) {
      monkeys[idx].items.push_back(item);
      items >> line;  // ,
    }

    getline(cin, line);
    stringstream op(line);

    op >> line >> line >> line >> line;  // Operation: new =

    op >> monkeys[idx].op;
    op >> line;
    monkeys[idx].op += line;

    getline(cin, line);
    stringstream test(line);
    test >> line >> line >> line;  // Test: divisible by
    test >> monkeys[idx].test;
    M *= monkeys[idx].test;

    getline(cin, line);
    stringstream ss_t(line);
    for (int i = 0; i < 5; i++) ss_t >> line;

    ss_t >> monkeys[idx].true_i;

    getline(cin, line);
    stringstream ss_f(line);
    for (int i = 0; i < 5; i++) ss_f >> line;

    ss_f >> monkeys[idx].false_i;

    getline(cin, line);  // empty line

    ++idx;
  }

  for (int i = 1; i <= ROUNDS; i++) {
    for (int i = 0; i < idx; ++i) {
      inspects[i] += monkeys[i].items.size();
      for (auto &wl : monkeys[i].items) {
        wl = apply(wl, monkeys[i].op);
        int to =
            wl % monkeys[i].test == 0 ? monkeys[i].true_i : monkeys[i].false_i;
        monkeys[to].items.push_back(wl);
      }
      monkeys[i].items.clear();
    }
  }

  sort(inspects.begin(), inspects.end(), greater<int>());
  cout << inspects[0] * inspects[1] << endl;

  return 0;
}
