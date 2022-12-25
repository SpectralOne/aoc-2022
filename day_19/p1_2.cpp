#include <bits/stdc++.h>
using namespace std;

#define State tuple<int, int, int, int, int, int, int, int, int>

int solve(int cost_ore, int cost_clay, int cost_obs_ore, int cost_obs_obs,
          int cost_geode_ore, int cost_geode_obs, int time) {
  int best = 0;
  State S = make_tuple(0, 0, 0, 0, 1, 0, 0, 0, time);
  queue<State> Q;
  Q.push(S);
  set<State> dp;

  while (!Q.empty()) {
    State state = Q.front();
    Q.pop();
    auto [ore, clay, obsidian, geode, rate_ore, rate_clay, rate_obs, rate_geode,
          time] = state;
    best = max(best, geode);

    if (time == 0) {
      continue;
    }

    int Core = max(cost_ore, max(cost_clay, max(cost_obs_ore, cost_geode_ore)));

    rate_ore = min(rate_ore, Core);
    rate_clay = min(rate_clay, cost_obs_obs);
    rate_obs = min(rate_obs, cost_geode_obs);
    ore = min(ore, time * Core - rate_ore * (time - 1));
    clay = min(clay, time * cost_obs_obs - rate_clay * (time - 1));
    obsidian = min(obsidian, time * cost_geode_obs - rate_obs * (time - 1));

    state = make_tuple(ore, clay, obsidian, geode, rate_ore, rate_clay,
                       rate_obs, rate_geode, time);

    if (dp.find(state) != dp.end()) continue;

    dp.insert(state);

    Q.push(make_tuple(ore + rate_ore, clay + rate_clay, obsidian + rate_obs,
                      geode + rate_geode, rate_ore, rate_clay, rate_obs,
                      rate_geode, time - 1));

    if (ore >= cost_ore) {
      Q.push(make_tuple(ore - cost_ore + rate_ore, clay + rate_clay,
                        obsidian + rate_obs, geode + rate_geode, rate_ore + 1,
                        rate_clay, rate_obs, rate_geode, time - 1));
    }

    if (ore >= cost_clay) {
      Q.push(make_tuple(ore - cost_clay + rate_ore, clay + rate_clay,
                        obsidian + rate_obs, geode + rate_geode, rate_ore,
                        rate_clay + 1, rate_obs, rate_geode, time - 1));
    }

    if (ore >= cost_obs_ore && clay >= cost_obs_obs) {
      Q.push(make_tuple(ore - cost_obs_ore + rate_ore,
                        clay - cost_obs_obs + rate_clay, obsidian + rate_obs,
                        geode + rate_geode, rate_ore, rate_clay, rate_obs + 1,
                        rate_geode, time - 1));
    }

    if (ore >= cost_geode_ore && obsidian >= cost_geode_obs) {
      Q.push(make_tuple(ore - cost_geode_ore + rate_ore, clay + rate_clay,
                        obsidian - cost_geode_obs + rate_obs,
                        geode + rate_geode, rate_ore, rate_clay, rate_obs,
                        rate_geode + 1, time - 1));
    }
  }

  return best;
}

int main(const int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");

  int p1 = 0, p2 = 1;
  int n, ore_robot, clay_robot, obsidian_ore, obsidian_obs, geode_ore,
      geode_obs;

  while (fscanf(f,
                "Blueprint %d: Each ore robot costs %d ore. Each clay robot "
                "costs %d ore. Each obsidian robot costs %d ore and %d clay. "
                "Each geode robot costs %d ore and %d obsidian.\n",
                &n, &ore_robot, &clay_robot, &obsidian_ore, &obsidian_obs,
                &geode_ore, &geode_obs) == 7) {
    int s1 = solve(ore_robot, clay_robot, obsidian_ore, obsidian_obs, geode_ore,
                   geode_obs, 24);
    p1 += n * s1;

    if (n < 4) {
      int s2 = solve(ore_robot, clay_robot, obsidian_ore, obsidian_obs,
                     geode_ore, geode_obs, 32);
      p2 *= s2;
    }
  }

  cout << "Part 1: " << p1 << endl;
  cout << "Part 2: " << p2 << endl;

  fclose(f);
  return 0;
}
