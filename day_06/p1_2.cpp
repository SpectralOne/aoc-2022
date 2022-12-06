#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  int dist_chars = atoi(argv[2]);
  string l;

  while (cin >> l) {
    int s = 0;
    for (int i = 0; i < l.size() - dist_chars; ++i) {
      __int32_t acc = 0UL;
      for (int j = 0; j < dist_chars; ++j) {
        __int32_t cur = acc;

        acc |= 1 << l[i + j] - 'a';

        if (cur == acc) break;
      }
      if (__builtin_popcount(acc) == dist_chars) break;
      ++s;
    }
    cout << s + dist_chars << endl;
  }

  return 0;
}
