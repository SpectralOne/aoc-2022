#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  string l;
  fstream f(argv[1]);
  int m = 0, t = 0;

  while (getline(f, l)) {
    if (l.size() == 0) {
      m = max(m, t);
      t = 0;
    } else {
      t += stoi(l);
    }
  }
  cout << max(m, t) << endl;

  return 0;
}
