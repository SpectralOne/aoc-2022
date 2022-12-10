#include <bits/stdc++.h>
using namespace std;

long long x = 1, cycles = 0, total = 0;

void cycle() {
  int d = abs(cycles % 40 - x);
  cout << ((d <= 1) ? '#' : '.');

  ++cycles;

  int i = cycles % 40;
  if (i == 0) cout << endl;
  if (i == 20) total += x * cycles;
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  cout << "part 2:" << endl;

  string op;
  int n;

  while (cin >> op) {
    if (op[0] == 'n') {
      cycle();
    } else {
      cycle();
      cycle();

      cin >> n;
      x += n;
    }
  }

  cout << "part 1: " << total << endl;

  return 0;
}
