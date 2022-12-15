#include <bits/stdc++.h>
using namespace std;

#define int long long
#define Y 2000000
#define pii pair<int, int>

__int32_t main(const int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");

  int s_x, s_y, b_x, b_y, c = 0;
  vector<pii> vs;

  while (
      fscanf(f,
             "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld\n",
             &s_x, &s_y, &b_x, &b_y) == 4) {
    int distance = abs(s_x - b_x) + abs(s_y - b_y);

    int diff = abs(s_y - Y);
    int interval = distance - diff;

    if (interval < 0) continue;

    vs.push_back(make_pair(s_x - interval, s_x + interval));
  }

  sort(vs.begin(), vs.end());
  pii cur = vs[0];
  for (int i = 1; i < vs.size(); ++i) {
    pii next = vs[i];

    if (cur.first <= next.first && next.second <= cur.second) continue;

    if (cur.first <= next.first && cur.second <= next.second &&
        next.first <= cur.second) {
      cur.second = next.second;
      continue;
    }

    c += (cur.second - cur.first) + 1;
    cur = next;
  }

  cout << c + cur.second - cur.first << endl;

  fclose(f);
  return 0;
}
