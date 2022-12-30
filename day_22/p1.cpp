#include <bits/stdc++.h>
using namespace std;

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {1, 0, -1, 0};

void step(vector<string>& grid, const int N, const int M, const int dir, int& x,
          int& y) {
  int sx = x, sy = y;
  do {
    x += dx[dir];
    y += dy[dir];
    x = (x + N) % N;
    y = (y + M) % M;
    if (grid[x][y] == '.') {
      sx = x, sy = y;
    }
  } while (grid[x][y] == ' ');
  x = sx, y = sy;
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  string line, pattern;
  vector<string> grid;

  while (getline(cin, line) && !line.empty()) grid.push_back(line);
  cin >> pattern;

  int N = grid.size();
  int M = 0;

  for (int i = 0; i < N; ++i) M = max(M, (int)grid[i].size());

  for (int i = 0; i < N; ++i) {
    while (grid[i].size() < M) grid[i] += " ";
  }

  int dir = 0;
  int y = find(grid[0].begin(), grid[0].end(), '.') - grid[0].begin();
  int x = 0;

  int steps;
  char cd;

  istringstream iss(pattern);
  while (iss >> steps) {
    for (int i = 0; i < steps; ++i) {
      step(grid, N, M, dir, x, y);
    }
    if (iss >> cd) {
      dir = (cd == 'L') ? (dir + 3) % 4 : (dir + 1) % 4;
    }
  }

  cout << 1000 * (x + 1) + 4 * (y + 1) + dir << endl;

  return 0;
}
