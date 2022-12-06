#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  int dist_chars = atoi(argv[2]);
  string l;

  while (cin >> l) {
    int s = 0;
    for (int i = 0; i < l.size() - dist_chars; ++i) {
      set<char> cs;

      for (int j = 0; j < dist_chars; ++j) cs.insert(l[i + j]);

      if (cs.size() == dist_chars) break;

      ++s;
    }
    cout << s + dist_chars << endl;
  }

  return 0;
}
