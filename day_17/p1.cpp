#include <bits/stdc++.h>
using namespace std;

#define ROCKS 2022

const vector<int> stones[6] = {{0x1E},
                               {0x08, 0x1C, 0x08},
                               {0x1C, 0x04, 0x04},
                               {0x10, 0x10, 0x10, 0x10},
                               {0x18, 0x18}};

constexpr int sides[5][2] = {{-2, 1}, {-2, 2}, {-2, 2}, {-2, 4}, {-2, 3}};

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  string pattern;
  cin >> pattern;

  vector<int> field;
  int stone_idx = 0, pattern_idx = 0;

  field.push_back(0x7F);

  auto stonefit = [&](int stone, int dir, int bp) -> bool {
    for (int i = 0; i < stones[stone].size(); ++i) {
      int shifted =
          dir > 0 ? stones[stone][i] >> dir : stones[stone][i] << -dir;
      if (bp + i < field.size() && (field[bp + i] & shifted)) return false;
    }
    return true;
  };

  vector<int> heights;
  map<pair<int, int>, vector<int>> drops;
  map<int, int> loopcount;

  while (true) {
    int bp = field.size() + 3;
    int shift = 0;
    bool drop = true;
    do {
      if (pattern[pattern_idx] == '<') {
        if (shift != sides[stone_idx % 5][0] &&
            stonefit(stone_idx % 5, shift - 1, bp))
          --shift;
      }

      if (pattern[pattern_idx] == '>') {
        if (shift != sides[stone_idx % 5][1] &&
            stonefit(stone_idx % 5, shift + 1, bp))
          ++shift;
      }

      pattern_idx = (pattern_idx + 1) % pattern.size();
      drop = stonefit(stone_idx % 5, shift, bp - 1);
      if (drop) --bp;
    } while (drop);

    int top = bp + stones[stone_idx % 5].size();
    if (field.size() < top) field.resize(top);
    for (int i = 0; i < stones[stone_idx % 5].size(); ++i) {
      int sv = shift > 0 ? stones[stone_idx % 5][i] >> shift
                         : stones[stone_idx % 5][i] << -shift;
      field[bp + i] |= sv;
    }

    if (++stone_idx == ROCKS) {
      cout << field.size() - 1 << endl;

      return 0;
    }
  }
  /* unreachable */
}