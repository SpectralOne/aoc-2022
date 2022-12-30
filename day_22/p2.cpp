#include <bits/stdc++.h>
using namespace std;

#define SIDE_SIZE 50

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {1, 0, -1, 0};

/*
.12
.3.
54.
6..
*/
void step(vector<string> &grid, const int N, const int M, int &dir, int &x,
          int &y) {
  int sx = x, sy = y, sdir = dir;
  x += dx[dir];
  y += dy[dir];
  x = (x + N) % N;
  y = (y + M) % M;

  if (dir == 1) {
    // 4v
    if (x == 3 * SIDE_SIZE && y < 2 * SIDE_SIZE && y >= 1 * SIDE_SIZE) {
      dir = 2;  // <
      x = (y - 1 * SIDE_SIZE) + 3 * SIDE_SIZE;
      y = 1 * SIDE_SIZE - 1;
    }

    // 2v
    else if (x == 1 * SIDE_SIZE && y < 3 * SIDE_SIZE && y >= 2 * SIDE_SIZE) {
      dir = 2;
      x = (y - 2 * SIDE_SIZE) + 1 * SIDE_SIZE;
      y = 2 * SIDE_SIZE - 1;
    }
    // 6v
    else if (x == 0 && y < 1 * SIDE_SIZE && y >= 0) {
      x = 0;
      y += 2 * SIDE_SIZE;
    }
  }

  else if (dir == 3) {
    // 5^
    if (x == 2 * SIDE_SIZE - 1 && y < 1 * SIDE_SIZE && y >= 0) {
      dir = 0;  // >
      x = (y - 0 * SIDE_SIZE) + 1 * SIDE_SIZE;
      y = 1 * SIDE_SIZE;
    }

    // 1^
    else if (x == 4 * SIDE_SIZE - 1 && y < 2 * SIDE_SIZE &&
             y >= 1 * SIDE_SIZE) {
      dir = 0;  // >
      x = (y - 1 * SIDE_SIZE) + 3 * SIDE_SIZE;
      y = 0 * SIDE_SIZE;
    }

    // 2^
    else if (x == 4 * SIDE_SIZE - 1 && y < 3 * SIDE_SIZE &&
             y >= 2 * SIDE_SIZE) {
      y -= 2 * SIDE_SIZE;
    }

  }

  else if (dir == 0) {
    // 2>
    if (y == 0 && x < 1 * SIDE_SIZE && x >= 0) {
      dir = 2;  // <
      x = (SIDE_SIZE - (x - 0 * SIDE_SIZE) - 1) + 2 * SIDE_SIZE;
      y = 2 * SIDE_SIZE - 1;
    }

    // 3>
    else if (y == 2 * SIDE_SIZE && x < 2 * SIDE_SIZE && x >= 1 * SIDE_SIZE) {
      dir = 3;  // ^
      y = (x - 1 * SIDE_SIZE) + 2 * SIDE_SIZE;
      x = 1 * SIDE_SIZE - 1;
    }

    // 4>
    else if (y == 2 * SIDE_SIZE && x < 3 * SIDE_SIZE && x >= 2 * SIDE_SIZE) {
      dir = 2;  // <
      x = (SIDE_SIZE - (x - 2 * SIDE_SIZE) - 1) + 0 * SIDE_SIZE;
      y = 3 * SIDE_SIZE - 1;
    }

    // 6>
    else if (y == 1 * SIDE_SIZE && x < 4 * SIDE_SIZE && x >= 3 * SIDE_SIZE) {
      dir = 3;  // ^
      y = (x - 3 * SIDE_SIZE) + 1 * SIDE_SIZE;
      x = 3 * SIDE_SIZE - 1;
    }
  }

  else if (dir == 2) {
    // 6< -> (top of 1)
    if (y == 3 * SIDE_SIZE - 1 && x < 4 * SIDE_SIZE && x >= 3 * SIDE_SIZE) {
      dir = 1;  // v
      y = (x - 3 * SIDE_SIZE) + 1 * SIDE_SIZE;
      x = 0;
    }

    // 5< -> (left of 1, flipped)
    else if (y == 3 * SIDE_SIZE - 1 && x < 3 * SIDE_SIZE &&
             x >= 2 * SIDE_SIZE) {
      dir = 0;  // >
      x = (SIDE_SIZE - (x - 2 * SIDE_SIZE) - 1) + 0 * SIDE_SIZE;
      y = 1 * SIDE_SIZE;
    }

    // 3< -> (top of 5)
    else if (y == 1 * SIDE_SIZE - 1 && x < 2 * SIDE_SIZE &&
             x >= 1 * SIDE_SIZE) {
      dir = 1;  // v
      y = (x - 1 * SIDE_SIZE) + 0 * SIDE_SIZE;
      x = 2 * SIDE_SIZE;
    }

    // 1< -> (left of 5, flipped)
    else if (y == 1 * SIDE_SIZE - 1 && x < 1 * SIDE_SIZE && x >= 0) {
      dir = 0;  // v
      x = (SIDE_SIZE - (x - 0 * SIDE_SIZE) - 1) + 2 * SIDE_SIZE;
      y = 0;
    }
  }

  if (grid[x][y] != '#') {
    sx = x, sy = y, sdir = dir;
  }
  x = sx, y = sy, dir = sdir;
}

int main(const int argc, char **argv) {
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
