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

  while (fscanf(f, "%d,%d,%d", &x, &y, &z) == 3) {
    obsidians.emplace(x, y, z);
  }

  int s = 0;
  for (auto& o : obsidians) {
    auto [x, y, z] = o;
    for (int i = 0; i < 6; ++i) {
      Obsidian lookup(x + dx[i], y + dy[i], z + dz[i]);
      if (!obsidians.count(lookup)) {
        ++s;
      }
    }
  }

  cout << s << endl;

  fclose(f);
  return 0;
}
