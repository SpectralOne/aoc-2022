#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

enum {
  NW = 0x01,
  N = 0x02,
  NE = 0x04,
  W = 0x08,
  E = 0x10,
  SW = 0x20,
  S = 0x40,
  SE = 0x80
};

struct Rules {
  int check, row_dir, col_dir;
} const rules[] = {{NE | E | SE, 0, 1},
                   {NW | N | NE, -1, 0},
                   {SW | S | SE, 1, 0},
                   {NW | W | SW, 0, -1}};

int get_neighbors(const set<pii> &elves, const pii &elf) {
  int res = 0, mask = 0x1;

  for (auto i = -1; i <= 1; ++i) {
    for (auto j = -1; j <= 1; ++j) {
      if (i || j) {
        pii lookup = make_pair(elf.first + i, elf.second + j);
        if (elves.find(lookup) != elves.end()) {
          res |= mask;
        }
        mask <<= 1;
      }
    }
  }

  return res;
}

int count(const set<pii> &elves) {
  int min_row = INT_MAX, max_row = INT_MIN;
  int min_col = INT_MAX, max_col = INT_MIN;

  for (auto &[row, col] : elves) {
    min_row = min(row, min_row);
    max_row = max(row, max_row);
    min_col = min(col, min_col);
    max_col = max(col, max_col);
  }

  return (max_row - min_row + 1) * (max_col - min_col + 1) - elves.size();
}

int main(const int argc, char **argv) {
  ifstream cin(argv[1]);

  set<pii> elves;
  string line;
  int row = 0;

  while (cin >> line) {
    for (int i = 0; i < line.length(); ++i) {
      if (line[i] == '#') {
        elves.insert(make_pair(row, i));
      }
    }
    ++row;
  }

  bool moved = false;
  int round = 1;
  while (round++) {
    map<pii, vector<pii>> moves_state;

    for (auto &from : elves) {
      auto [row, col] = from;
      int neighbors = get_neighbors(elves, from);

      if (!neighbors) continue;

      for (int i = 0; i < 4; ++i) {
        const Rules r = rules[(round + i) % 4];
        if ((neighbors & r.check) == 0) {
          pii to = make_pair(row + r.row_dir, col + r.col_dir);
          moves_state[to].push_back(from);
          break;
        }
      }
    }

    bool moved = false;
    for (auto &p : moves_state) {
      if (p.second.size() == 1) {
        elves.insert(p.first);
        elves.erase(elves.find(p.second[0]));
        moved = true;
      }
    }

    if (!moved) {
      cout << "p2: " << round << endl;
      break;
    }

    if (round == 10) {
      cout << "p1: " << count(elves) << endl;
    }
  }
  return 0;
}
