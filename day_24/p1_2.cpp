#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<vector<string>> grids;
int rows = 0, cols = 0;

struct Blizzard {
  pii pos;
  char dir;
};

int solve(pii start, pii end, int start_time) {
  const int period = grids.size();
  int fastest = INT_MAX;
  queue<pair<pii, int>> Q;
  set<pair<pii, int>> seen;

  Q.push({start, start_time});
  while (!Q.empty()) {
    auto [pos, time] = Q.front();
    Q.pop();

    if (time >= fastest) continue;

    if (pos == end) {
      fastest = min(time, fastest);
      continue;
    }

    auto key = make_pair(pos, time);
    if (seen.find(key) != seen.end()) continue;

    seen.insert(key);

    vector<string> &grid = grids[(time + 1) % period];

    if (pos.first + 1 <= rows - 1 && grid[pos.first + 1][pos.second] == '.') {
      Q.push({{pos.first + 1, pos.second}, time + 1});
    }

    if (grid[pos.first][pos.second + 1] == '.') {
      Q.push({{pos.first, pos.second + 1}, time + 1});
    }

    if (pos.first - 1 >= 0 && grid[pos.first - 1][pos.second] == '.') {
      Q.push({{pos.first - 1, pos.second}, time + 1});
    }

    if (grid[pos.first][pos.second - 1] == '.') {
      Q.push({{pos.first, pos.second - 1}, time + 1});
    }

    if (grid[pos.first][pos.second] == '.') {
      Q.push({{pos.first, pos.second}, time + 1});
    }
  }

  return fastest;
}

int main(const int argc, char **argv) {
  ifstream cin(argv[1]);

  string line;
  vector<Blizzard> blizzards;
  vector<string> grid;

  while (cin >> line) {
    for (auto i = 0; i < line.length(); ++i)
      if (line[i] != '#' && line[i] != '.') {
        blizzards.push_back({{int(grid.size()), i}, line[i]});
        line[i] = '.';
      }

    grid.push_back(line);
  }

  rows = int(grid.size()), cols = int(grid[0].size());
  int period = lcm(rows - 2, cols - 2);

  for (int i = 0; i < period; ++i) {
    auto temp_grid = grid;

    for (auto &b : blizzards) temp_grid[b.pos.first][b.pos.second] = '#';

    grids.push_back(temp_grid);

    for (auto &b : blizzards) {
      auto &row = b.pos.first, &col = b.pos.second;

      switch (b.dir) {
        case '^':
          if (--row == 0) row = rows - 2;
          break;
        case 'v':
          if (++row == rows - 1) row = 1;
          break;
        case '<':
          if (--col == 0) col = cols - 2;
          break;
        case '>':
          if (++col == cols - 1) col = 1;
          break;
      }
    }
  }

  int p1 = solve({0, 1}, {rows - 1, cols - 2}, 0);
  int p2 = solve({rows - 1, cols - 2}, {0, 1}, p1);
  p2 = solve({0, 1}, {rows - 1, cols - 2}, p2);

  cout << "p1: " << p1 << endl;
  cout << "p2: " << p2 << endl;

  return 0;
}
