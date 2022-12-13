#include <bits/stdc++.h>

#include <compare>

using namespace std;

struct List : variant<vector<List>, int> {
  List* parent = nullptr;
  using variant<vector<List>, int>::variant;

  vector<List>& list() { return get<vector<List>>(*this); }
  int& Int() { return get<int>(*this); }

  weak_ordering compare(List& other) {
    if (index() == 1 && other.index() == 1) {
      return Int() <=> other.Int();
    }

    vector<List> lhs;
    if (index() == 1) {
      lhs.push_back(Int());
    } else {
      lhs = list();
    }

    vector<List> rhs;
    if (other.index() == 1) {
      rhs.push_back(other.Int());
    } else {
      rhs = other.list();
    }

    int ms = min(lhs.size(), rhs.size());

    for (int i = 0; i < ms; ++i) {
      auto res = lhs[i].compare(rhs[i]);
      if (res != weak_ordering::equivalent) {
        return res;
      }
    }

    if (lhs.size() < rhs.size()) return weak_ordering::less;
    if (lhs.size() > rhs.size()) return weak_ordering::greater;

    return weak_ordering::equivalent;
  }
};

// skips comma
void skip_check(ifstream& cin) {
  char comma;
  cin >> comma;
  if (comma != ',') cin.seekg(-1, ios::cur);
}

void next(ifstream& cin, List& list) {
  auto& l = list.list();

  char bracket;
  cin >> bracket;

  if (bracket == '[') {
    List nl = vector<List>{};
    nl.parent = &list;
    l.emplace_back(nl);
    next(cin, l.back());
  } else if (bracket == ']') {
    if (list.parent) {
      skip_check(cin);
      next(cin, *list.parent);
    }
  } else {
    cin.seekg(-1, ios::cur);
    int value;
    cin >> value;
    l.push_back(value);

    skip_check(cin);
    next(cin, list);
  }
}

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);

  vector<List> lists;
  char bracket;

  while (cin >> bracket) {
    List list = vector<List>{};

    if (bracket == '[') next(cin, list);

    lists.emplace_back(list);
  }

  vector<pair<List, List>> pairs;
  for (int i = 0; i < lists.size(); i += 2) {
    pairs.emplace_back(lists[i], lists[i + 1]);
  }

  int s = 0;
  for (int i = 0; i < pairs.size(); ++i) {
    if (pairs[i].first.compare(pairs[i].second) == weak_ordering::less) {
      s += i + 1;
    }
  }

  cout << s << endl;

  return 0;
}
