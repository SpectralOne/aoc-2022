#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct Hash {
  auto operator()(const pii& p) const -> size_t {
    return (p.first * 0x1F1F1F1F) ^ p.second;
  }
};

enum State { WALL, SAND };

int max_y = 0;

bool fill(unordered_map<pii, State, Hash>& map, pii coord) {
  auto it = map.find(coord);
  if (it != map.end()) return true;

  auto [x, y] = coord;
  if (y > max_y) return false;

  bool c = fill(map, pii(x, y + 1)) &&
           fill(map, pii(x - 1, y + 1)) &&
           fill(map, pii(x + 1, y + 1));

  if (c) map[coord] = SAND;

  return c;
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  unordered_map<pii, State, Hash> map;
  string line;

  while (getline(cin, line)) {
    vector<string> pairs;
    int pos = 0;

    while ((pos = line.find(" -> ")) != string::npos) {
      pairs.push_back(line.substr(0, pos));
      line.erase(0, pos + 4);
    }
    pairs.push_back(line);

    pos = pairs[0].find(',');
    int px = stoi(pairs[0].substr(0, pos));
    int py = stoi(pairs[0].substr(pos + 1));
    max_y = max(max_y, py);
    map[pii(px, py)] = WALL;

    for (int i = 1; i < pairs.size(); ++i) {
      pos = pairs[i].find(',');
      int x = stoi(pairs[i].substr(0, pos));
      int y = stoi(pairs[i].substr(pos + 1));
      max_y = max(max_y, y);

      if (px == x) {
        for (int j = min(py, y); j <= max(py, y); ++j) {
          map[pii(px, j)] = WALL;
        }
      } else {
        for (int j = min(px, x); j <= max(px, x); ++j) {
          map[pii(j, py)] = WALL;
        }
      }

      px = x;
      py = y;
    }
  }

  fill(map, pii(500, 0));

  cout << count_if(map.begin(), map.end(), [](const auto& p) {
    return p.second == SAND;
  }) << endl;

  return 0;
}
