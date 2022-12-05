#!/bin/bash

for i in "$@"
do
case $i in
  -r|--replace)
    REPLACE=YES
    ;;
  *)
    ;;
esac
done

if [[ $# -lt 2 ]]
then
    printf "Insuficcient input!\nTry ./create_day DAY YEAR -r|--replace"
    exit 1
fi

DAY=${1}
YEAR=${2}

if [ -f .env ]
then
  export $(cat .env | xargs)
fi

DIR="day_$(printf "%02d" "${DAY}")"

if [[ -d "${DIR}" ]] && [[ ! "${REPLACE}" ]]
then
    echo "This day already exists. User -r|--replace to override!"
    exit 1
else
    rm -rf ${DIR} && mkdir "${DIR}"
fi

FILE_IN="${DIR}/in.txt"
URL="https://adventofcode.com/${YEAR}/day/${DAY}/input"

curl ${URL} --progress-bar -H "Cookie: session=${SESSION}" > $FILE_IN

cat > "${DIR}/p1.cpp" << EOF
#include <bits/stdc++.h>
using namespace std;

int main(const int argc, char** argv) {
  ifstream cin(argv[1]);
  //FILE* f = fopen(argv[1], "r");

  int s = 0;

  while (cin >> s) {
  }

  cout << s << endl;

  //fclose(f);
  return 0;
}
EOF

cp "${DIR}/p1.cpp" "${DIR}/p2.cpp"
