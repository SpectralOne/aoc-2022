#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

pii new_tail(pii old_tail, pii head) {
  int xd = head.first - old_tail.first;
  int yd = head.second - old_tail.second;

  int xs = xd == 0 ? 0 : xd / abs(xd);
  int ys = yd == 0 ? 0 : yd / abs(yd);

  return make_pair(old_tail.first + xs, old_tail.second + ys);
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  set<pii> locations;
  pii head = make_pair(0, 0);
  pii tail = make_pair(0, 0);
  locations.insert(tail);
  int n, xd = 0, yd = 0;
  string action;

  while (cin >> action >> n) {
    xd = 0, yd = 0;
    switch (action[0]) {
      case 'R':
        xd = 1;
        break;
      case 'L':
        xd = -1;
        break;
      case 'U':
        yd = 1;
        break;
      case 'D':
        yd = -1;
        break;
    }

    for (int i = 1; i <= n; ++i) {
      pii new_head = make_pair(head.first + xd, head.second + yd);
      if (!(abs(tail.first - new_head.first) <= 1 &&
            abs(tail.second - new_head.second) <= 1)) {
        tail = new_tail(tail, new_head);
        locations.insert(tail);
      }
      head = new_head;
    }
  }

  cout << locations.size() << endl;

  return 0;
}
