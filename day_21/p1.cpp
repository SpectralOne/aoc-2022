#include <bits/stdc++.h>
using namespace std;

class Monkey {
 public:
  char op;
  string m1, m2;
  long long result;

  Monkey() {}
  Monkey(long long r) : result(r) {}
  Monkey(char op, string m1, string m2) : op(op), m1(m1), m2(m2) {}
  ~Monkey(){};

  void calc(const Monkey &lhs, const Monkey &rhs) {
    const long long lval = lhs.result;
    const long long rval = rhs.result;
    switch (op) {
      case '+':
        result = lval + rval;
        break;
      case '-':
        result = lval - rval;
        break;
      case '*':
        result = lval * rval;
        break;
      case '/':
        result = lval / rval;
        break;
    }
  }
};

void yell(map<string, Monkey> &yells, map<string, Monkey> &waits) {
  while (true) {
    bool yelling = false;
    for (auto it = waits.begin(); it != waits.end() && !yelling;) {
      auto &[name, monkey] = *it++;
      if (yells.count(monkey.m1) && yells.count(monkey.m2)) {
        monkey.calc(yells[monkey.m1], yells[monkey.m2]);
        yells[name] = monkey;
        waits.erase(name);
        yelling = true;
      }
    }
    if (!yelling) break;
  }
}

int main(const int argc, char **argv) {
  ifstream cin(argv[1]);

  map<string, Monkey> yells;
  map<string, Monkey> waits;

  string line = "";
  while (cin >> line) {
    line.pop_back();
    string name = line;

    cin >> line;
    if (all_of(line.begin(), line.end(), ::isdigit)) {
      Monkey m(stoi(line));
      yells[name] = m;
    } else {
      string m2, op;
      cin >> op >> m2;
      waits[name] = Monkey(op[0], line, m2);
    }
  }

  yell(yells, waits);

  cout << yells["root"].result << endl;

  return 0;
}
