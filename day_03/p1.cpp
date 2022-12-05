#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  string bag;
  int s = 0;

  while (cin >> bag) {
    auto half = bag.size() / 2;
    char uc = *find_first_of(begin(bag), next(begin(bag), half),
                             next(begin(bag), half), end(bag));
    s += uc >= 'a' ? uc - 'a' + 1 : uc - 'A' + 27;
  }

  cout << s << endl;

  return 0;
}
