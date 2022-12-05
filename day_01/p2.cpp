#include <bits/stdc++.h>
using namespace std;

#define UPD(a, v)                                              \
  ({                                                           \
    int i = distance(begin(a), min_element(begin(a), end(a))); \
    a[i] = a[i] < v ? v : a[i];                                \
  })

int main(const int argc, char** argv) {
  string l;
  fstream f(argv[1]);
  vector<int> top(3, -1);
  int t = 0;

  while (getline(f, l)) {
    if (l.size() == 0) {
      UPD(top, t), t = 0;
    } else {
      t += stoi(l);
    }
  }

  if (t) {
    UPD(top, t);
  }
  cout << reduce(top.begin(), top.end()) << endl;

  return 0;
}
