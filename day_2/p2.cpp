#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  string l;
  fstream f(argv[1]);
  int s = 0;

  while (std::getline(f, l)) {
    int op = l[0] - 'A';
    if (l[2] == 'X') {
      s += (op - 1 + 3) % 3 + 1;
    } else if (l[2] == 'Y') {
      s += 3 + op + 1;
    } else {
      s += 6 + (op + 1) % 3 + 1;
    }
  }

  std::cout << s << endl;

  return 0;
}
