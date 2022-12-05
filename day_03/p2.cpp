#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  string b1, b2, b3;
  int s = 0;

  while (cin >> b1 && cin >> b2 && cin >> b3) {
    set<char> a, b, c, abi, r;
    for (const char ch : b1) a.insert(ch);
    for (const char ch : b2) b.insert(ch);
    for (const char ch : b3) c.insert(ch);

    set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                     inserter(abi, abi.begin()));

    set_intersection(abi.begin(), abi.end(), c.begin(), c.end(),
                     inserter(r, r.begin()));

    char ch = *r.begin();
    s += ch >= 'a' ? ch - 'a' + 1 : ch - 'A' + 27;
  }

  cout << s << endl;

  return 0;
}
