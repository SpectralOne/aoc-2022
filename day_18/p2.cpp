#include <bits/stdc++.h>
using namespace std;

#define Obsidian tuple<int, int, int>

constexpr int dx[] = {1, -1, 0, 0, 0, 0};
constexpr int dy[] = {0, 0, 1, -1, 0, 0};
constexpr int dz[] = {0, 0, 0, 0, 1, -1};

int main(const int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");

  int x, y, z;
  set<Obsidian> obsidians;
  set<Obsidian> water;

  while (fscanf(f, "%d,%d,%d", &x, &y, &z) == 3) {
    obsidians.emplace(x, y, z);
  }

  queue<Obsidian> Q;
  Q.push(make_tuple(-1, -1, -1));

  while (!Q.empty()) {
    auto [x, y, z] = Q.front();
    water.emplace(x, y, z);
    Q.pop();

    for (int i = 0; i < 6; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      int nz = z + dz[i];
      if (nx < -1 || nx >= 30 || ny < -1 || ny >= 30 || nz < -1 || nz >= 30)
        continue;

      Obsidian next(nx, ny, nz);
      if (!water.count(next) && !obsidians.count(next)) {
        water.emplace(next);
        Q.push(next);
      }
    }
  }

  int s = 0;
  for (auto& o : obsidians) {
    auto [x, y, z] = o;
    for (int i = 0; i < 6; ++i) {
      Obsidian lookup(x + dx[i], y + dy[i], z + dz[i]);
      if (water.count(lookup)) {
        ++s;
      }
    }
  }

  cout << s << endl;

  fclose(f);
  return 0;
}
