#include <bits/stdc++.h>
using namespace std;

#define int long long

__int32_t main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  int s = 0;
  string line;
  while (cin >> line) {
    int number = 0;
    int size = line.size();
    int power = 1;

    while (size--) {
      if (line[size] == '-') {
        number -= power;
      } else if (line[size] == '=') {
        number -= 2 * power;
      } else {
        number += power * (line[size] - '0');
      }
      power *= 5;
    }
    s += number;
  }

  string out = "";
  while (s) {
    char c = '0' + (s % 5);
    bool high = c > '2';
    if (high) {
      if (c == '3') {
        c = '=';
      } else if (c == '4') {
        c = '-';
      } else {
        c = '0';
      }
    }
    out += c;
    s = s / 5 + high;
  }

  reverse(out.begin(), out.end());

  cout << out << endl;

  return 0;
}
