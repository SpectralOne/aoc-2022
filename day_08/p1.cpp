#include <bits/stdc++.h>
using namespace std;

vector<string> grid;

tuple<int, int, int, int> get(const int row, const int col) {
  int current = grid[row][col];

  int up = row;
  while (--up >= 0) {
    if (grid[up][col] >= current) break;
  }

  int down = row;
  while (++down < grid.size()) {
    if (grid[down][col] >= current) break;
  }

  int left = col;
  while (--left >= 0) {
    if (grid[row][left] >= current) break;
  }

  int right = col;
  while (++right < grid[0].size()) {
    if (grid[row][right] >= current) break;
  }

  return {up, down, left, right};
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  string line;

  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int rows = grid.size();
  int cols = grid[0].size();

  int v = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (i == 0 || i == rows - 1) {
        ++v;
        continue;
      }

      if (j == 0 || j == cols - 1) {
        ++v;
        continue;
      }

      const auto [up, down, left, right] = get(i, j);

      if (up == -1) {
        ++v;
        continue;
      }

      if (down == rows) {
        ++v;
        continue;
      }

      if (left == -1) {
        ++v;
        continue;
      }

      if (right == cols) {
        ++v;
        continue;
      }
    }
  }

  cout << v << endl;

  return 0;
}
