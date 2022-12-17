#include <bits/stdc++.h>
using namespace std;

#define int long long

int sz = 0;
vector<int> rates;
vector<vector<int>> tunnels;

vector<int> DP;

int solve(int current, int opened, int time, bool elephant) {
  if (!time) {
    return elephant ? solve(0, opened, 26, false) : 0LL;
  }

  auto key = opened * sz * sz + current * sz + time * 2 + elephant;

  if (DP[key] >= 0) return DP[key];

  int ans = 0;
  // try to open
  bool already_opened = ((opened & (1LL << current)) == 0);
  if (already_opened && rates[current] > 0) {
    int next = opened | (1LL << current);
    ans = max(ans, (time - 1) * rates[current] +
                       solve(current, next, time - 1, elephant));
  }

  // next tunnel
  for (auto& v : tunnels[current]) {
    ans = max(ans, solve(v, opened, time - 1, elephant));
  }

  DP[key] = ans;

  return ans;
}

__int32_t main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  map<string, pair<int, vector<string>>> data;
  string line;

  while (getline(cin, line)) {
    stringstream ss(line);
    int rate;
    vector<string> tunnels;
    string word, id;

    ss.ignore(6);   // Valve
    ss >> id;       // XX
    ss.ignore(15);  // has flow rate=
    ss >> rate;     // XX
    ss.ignore(24);  // tunnels lead to valves
    while (ss >> word) {
      word = word.back() == ',' ? word.substr(0, word.size() - 1) : word;
      tunnels.push_back(word);
    }
    data[id] = make_pair(rate, tunnels);
  }

  map<string, int> flow;
  vector<string> idxes;
  int nonzero = 1;

  flow["AA"] = 0;
  idxes.push_back("AA");

  for (auto& entry : data) {
    string idx = entry.first;
    int rate = entry.second.first;
    if (rate) {
      flow[idx] = idxes.size();
      idxes.push_back(idx);
      ++nonzero;
    }
  }

  for (auto& entry : data) {
    string idx = entry.first;
    if (!flow.count(idx)) {
      flow[idx] = idxes.size();
      idxes.push_back(idx);
    }
  }

  sz = data.size();

  // rates checkup
  rates = vector<int>(sz, 0);
  for (int i = 0; i < sz; ++i) rates[i] = data[idxes[i]].first;

  // checkup tunnels (edges) amount of valves by indexes
  tunnels = vector<vector<int>>(sz, vector<int>{});
  for (int i = 0; i < sz; ++i) {
    for (auto& valve : data[idxes[i]].second) {
      tunnels[i].push_back(flow[valve]);
    }
  }

  DP = vector<int>((1 << nonzero) * sz * (sz + 1), -1);

  cout << "part 1: " << solve(0, 0, 30, false) << endl;
  cout << "part 2: " << solve(0, 0, 26, true) << endl;

  return 0;
}
