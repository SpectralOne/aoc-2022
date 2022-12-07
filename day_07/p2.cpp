#include <bits/stdc++.h>
using namespace std;

#define CAPACITY_MULTIPLIER 2
#define SYSTEM_SPACE 70000000
#define NEEDED_TO_UPDATE 30000000

vector <size_t> TOTALS;

typedef struct Dir {
  string name;
  size_t total;

  Dir *parent;

  Dir **children;
  size_t size; // -> children.size()
  size_t capacity; // -> children.capacity()
} Dir;

size_t total_size_d(Dir *dir) {
  size_t total = dir->total;
  for (int i = 0; i < dir->size; ++i) total += total_size_d(dir->children[i]);
  return total;
}

void insert_d(Dir *dir, string name) {
  if (dir->size == dir->capacity) {
    dir->capacity = (dir->size + 1) * CAPACITY_MULTIPLIER;
    dir->children =
        (Dir **)realloc(dir->children, dir->capacity * sizeof(Dir *));
  }

  Dir *child = (Dir *)calloc(1, sizeof(Dir));
  child->name = name;
  child->parent = dir;

  dir->children[dir->size++] = child;
}

Dir *find_d(Dir *dir, string name) {
  for (int i = 0; i < dir->size; ++i) {
    if (dir->children[i]->name == name) return dir->children[i];
  }

  return NULL;
}

// Main solve
void solve_part_2(Dir *dir) {
  TOTALS.push_back(total_size_d(dir));
  for (int i = 0; i < dir->size; ++i) solve_part_2(dir->children[i]);
}

void destroy_d(Dir *dir) {
  Dir** childs = dir->children;
  if (childs && dir->size != 0) {
    for (int i = 0; i < dir->size; ++i) destroy_d(dir->children[i]);
  }

  if (childs) free(dir->children);
  dir->name.~basic_string();
  free(dir);
}

int main(const int argc, char **argv) {
  ifstream cin(argv[1]);

  Dir *current = NULL;
  Dir *root = (Dir *)calloc(1, sizeof(Dir));
  root->name = "/";

  vector<string> vl;
  string l;
  while (getline(cin, l)) vl.push_back(l);

  int idx = 0;
  string $;
  string cmd;
  while (idx < vl.size()) {
    string line = vl[idx];
    stringstream ss(line);

    // $
    ss >> $;

    ss >> cmd;
    if (cmd == "cd") {
      string name;
      ss >> name;

      if (name == "/") current = root;
      else if (name == "..") current = current->parent;
      else current = find_d(current, name);

      ++idx;
    } else {
      while (++idx < vl.size()) {
        line = vl[idx];
        if (line[0] == '$') break;

        stringstream cmd_ss(line);
        string cmd, args;
        cmd_ss >> cmd >> args;

        if (cmd == "dir") insert_d(current, args);
        else current->total += atoi(cmd.c_str());
      }
    }
  }

  solve_part_2(root);

  sort(TOTALS.begin(), TOTALS.end());
  size_t free_space = SYSTEM_SPACE - TOTALS.back();
  for (size_t sz : TOTALS) {
    bool suitable = free_space + sz >= NEEDED_TO_UPDATE ? true : false;
    if (suitable) {
      cout << sz << endl;
      break;
    }
  }

  destroy_d(root);

  return 0;
}
