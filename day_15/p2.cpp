#include <bits/stdc++.h>
using namespace std;

#define int long long
#define Sensor tuple<int, int, int>
#define MAX 4000000

__int32_t main(const int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");

  vector<Sensor> vs;
  int s_x, s_y, b_x, b_y;

  while (
      fscanf(f,
             "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld\n",
             &s_x, &s_y, &b_x, &b_y) == 4) {
    int distance = abs(s_x - b_x) + abs(s_y - b_y);
    vs.push_back({s_x, s_y, distance});
  }

  sort(vs.begin(), vs.end());

  for (int y = 0; y <= MAX; ++y) {
    for (int x = 0; x <= MAX; ++x) {
      bool found = true;
      for (const auto& sensor : vs) {
        auto [s_x, s_y, distance] = sensor;
        const int dx = abs(s_x - x);
        const int dy = abs(s_y - y);
        if (dy + dx <= distance) {
          const int delta = distance - dy;
          if (s_x >= x) {
            x += dx + delta;
          } else {
            x += -dx + delta;
          }

          found = false;
          break;
        }
      }
      if (found) {
        cout << x * 4000000 + y << endl;

        fclose(f);
        return 0;
      }
    }
  }
  /* unreachable */
}
