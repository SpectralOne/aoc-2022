#include <bits/stdc++.h>
using namespace std;

vector<string> grid;

size_t get(const int row, const int col) {
  int up_c = 0, down_c = 0, left_c = 0, right_c = 0;
  int current = grid[row][col];

  int up = row;
  while (--up >= 0) {
    ++up_c;
    if (grid[up][col] >= current) break;
  }

  int down = row;
  while (++down < grid.size()) {
    ++down_c;
    if (grid[down][col] >= current) break;
  }

  int left = col;
  while (--left >= 0) {
    ++left_c;
    if (grid[row][left] >= current) break;
  }

  int right = col;
  while (++right < grid[0].size()) {
    ++right_c;
    if (grid[row][right] >= current) break;
  }

  if (up_c == 0) up_c = 1;
  if (down_c == 0) down_c = 1;
  if (left_c == 0) left_c = 1;
  if (right_c == 0) right_c = 1;

  return up_c * left_c * down_c * right_c;
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  string line;

  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int rows = grid.size();
  int cols = grid[0].size();

  size_t max = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      size_t score = get(i, j);
      if (score > max) max = score;
    }
  }

  cout << max << endl;

  return 0;
}
