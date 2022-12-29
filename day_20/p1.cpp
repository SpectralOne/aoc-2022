#include <bits/stdc++.h>
using namespace std;

int at(const vector<int>& data, const vector<int>& positions, const int pos) {
  for (int i = 0; i < positions.size(); ++i) {
    if (positions[i] == pos % (int)positions.size()) return data[i];
  }
}

int get_new_pos(const vector<int>& data, const int i, const int old_pos,
                const int m) {
  int new_pos = old_pos + data[i] % (m - 1);
  if (0 < new_pos && new_pos < m) return new_pos;
  if (new_pos <= 0) return new_pos + m - 1;
  return new_pos - m + 1;
}

void mix(vector<int>& data, vector<int>& pos) {
  const int modulus = data.size();
  for (int i = 0; i < modulus; ++i) {
    if (data[i] % (modulus - 1) == 0) continue;

    const auto old_pos = pos[i];
    const auto new_pos = get_new_pos(data, i, old_pos, modulus);
    for (auto& ele : pos) {
      if (old_pos < new_pos && old_pos <= ele && ele <= new_pos) {
        ele = (ele - 1 + modulus) % modulus;
      } else if (new_pos < old_pos && new_pos <= ele && ele <= old_pos) {
        ele = (ele + 1) % modulus;
      }
    }
    pos[i] = new_pos;
  }
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  vector<int> data;
  vector<int> pos;

  int x = 0, idx = 0, zero = 0;
  while (cin >> x) {
    data.push_back(x);
    if (!data.back()) zero = idx;
    pos.push_back(idx++);
  }

  mix(data, pos);

  int d1 = at(data, pos, 1000 + pos[zero]);
  int d2 = at(data, pos, 2000 + pos[zero]);
  int d3 = at(data, pos, 3000 + pos[zero]);

  cout << d1 + d2 + d3 << endl;

  return 0;
}
