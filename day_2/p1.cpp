#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  string l;
  fstream f(argv[1]);
  int s = 0;

  while (std::getline(f, l)) {
    s += l[2] - 'X' + 1;
    int d = (l[2] - l[0] - 23 + 3) % 3;

    if (d == 2) continue;
    if (d == 0) s += 3;
    if (d == 1) s += 6;
  }

  std::cout << s << endl;

  return 0;
}
