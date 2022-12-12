#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define vvi vector<vector<int>>

const auto suitable = [](const vvi& g, const pii& p) {
  return p.first >= 0 && p.second >= 0 && p.first < g.size() &&
         p.second < g[0].size();
};

constexpr pii d[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int part_1(const vvi& g, const pii start, const pii end) {
  deque<pair<pii, int>> dq;
  dq.push_back({start, 0});
  set<pii> v;
  v.insert(start);
  while (!dq.empty()) {
    auto [cur, dist] = dq.front();
    dq.pop_front();
    for (int i = 0; i < 4; ++i) {
      pii nbr = make_pair(cur.first + d[i].first, cur.second + d[i].second);

      if (!suitable(g, nbr)) continue;
      if (g[nbr.first][nbr.second] - g[cur.first][cur.second] > 1) continue;
      if (nbr == end) return dist + 1;
      if (v.count(nbr)) continue;

      v.insert(nbr);
      dq.push_back({nbr, dist + 1});
    }
  }

  // should never happen
  return INT_MAX;
}

int part_2(const vvi& g, const pii end) {
  int m = INT_MAX;
  for (int i = 0; i < g.size(); ++i) {
    for (int j = 0; j < g[i].size(); ++j) {
      if (g[i][j]) continue;
      m = min(m, part_1(g, {i, j}, end));
    }
  }

  return m;
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  vvi g;
  pii start, end;
  string line;

  for (int i = 0; getline(cin, line); ++i) {
    g.emplace_back();
    for (int j = 0; j < line.size(); ++j) {
      if (char ch = line[j]; ch == 'S') {
        start = {i, j};
        g.back().push_back(0);
      } else if (ch == 'E') {
        end = {i, j};
        g.back().push_back('z' - 'a');
      } else {
        g.back().push_back(ch - 'a');
      }
    }
  }

  cout << part_1(g, start, end) << endl;
  cout << part_2(g, end) << endl;

  return 0;
}
