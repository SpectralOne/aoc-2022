#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");
  int a1, a2, b1, b2;
  int s = 0;

  while (fscanf(f, "%d-%d,%d-%d", &a1, &a2, &b1, &b2) == 4) {
    if (a1 <= b1 && b1 <= a2 || b1 <= a1 && a1 <= b2) {
      s += 1;
    }
  }

  std::cout << s << endl;

  return 0;
}
