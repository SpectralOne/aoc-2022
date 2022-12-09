#include <bits/stdc++.h>
using namespace std;

#define KNOTS_SIZE 10
#define pii pair<int, int>

pii new_tail(pii old_tail, pii head) {
  if (abs(old_tail.first - head.first) <= 1 &&
      abs(old_tail.second - head.second) <= 1) {
    return old_tail;
  }

  int xd = head.first - old_tail.first;
  int yd = head.second - old_tail.second;

  int xs = xd == 0 ? 0 : xd / abs(xd);
  int ys = yd == 0 ? 0 : yd / abs(yd);

  return make_pair(old_tail.first + xs, old_tail.second + ys);
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  set<pii> locations;
  vector<pii> snake(KNOTS_SIZE);
  locations.insert(snake[0]);
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

    pii* head = &snake[KNOTS_SIZE - 1];
    for (int i = 1; i <= n; ++i) {
      *head = make_pair(head->first + xd, head->second + yd);

      for (int j = KNOTS_SIZE - 2; j >= 0; --j) {
        snake[j] = new_tail(snake[j], snake[j + 1]);
      }

      locations.insert(snake[0]);
    }
  }

  cout << locations.size() << endl;

  return 0;
}
