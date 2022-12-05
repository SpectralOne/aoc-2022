#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");
  int n, from, to;
  int s = 0;

  vector<vector<char>> in(9);
  char* line = NULL;
  size_t len = 0;
  int i = 0;
  while ((getline(&line, &len, f))) {
    if (line[1] == '1') break;
    for (int si = 1, idx = 0; idx < 9 && line[si]; si += 4, ++idx) {
      if (line[si] != ' ') {
        in[idx].push_back(line[si]);
      }
    }
    ++i;
  }

  // empty line
  getline(&line, &len, f);

  for (auto& v : in) reverse(v.begin(), v.end());

  vector<stack<char>> ss(9);
  for (int i = 0; i < 9; ++i) {
    for (char c : in[i]) {
      ss[i].push(c);
    }
  }

  int x = 0;
  while (fscanf(f, "move %d from %d to %d", &n, &from, &to) == 3) {
    vector<char> vc;
    for (int i = 0; i < n; ++i) {
      vc.push_back(ss[from - 1].top());
      ss[from - 1].pop();
    }
    for (int i = vc.size() - 1; i >= 0; --i) ss[to - 1].push(vc[i]);
    // LF
    fgetc(f);
  }

  for (auto& x : ss) {
    cout << x.top();
  }

  fclose(f);

  return 0;
}
