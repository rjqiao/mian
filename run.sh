#!/usr/bin/env bash

#function gg_build {
#  cd $(git rev-parse --show-toplevel);
#  cmake -H. -Bbuild &&
#  cmake --build build -- -j3 &&
#  cmake --build build --target install;
#  cd -;
#}

function rq-build-debug {
  cd $(git rev-parse --show-toplevel);
  cmake -S . -B "build-debug" -DCMAKE_BUILD_TYPE=Debug &&
  cmake --build "build-debug" -- -j 4
  cd -;
}

function rq-build-release {
  cd $(git rev-parse --show-toplevel);
  cmake -S . -B "build-release" -DCMAKE_BUILD_TYPE=Release &&
  cmake --build "build-release" -- -j 4
  cd -;
}


## Absolute path to this script, e.g. /home/user/bin/foo.sh
#SCRIPT=$(readlink -f "$0")
## Absolute path this script is in, thus /home/user/bin
#SCRIPTPATH=$(dirname "$SCRIPT")
#echo $SCRIPTPATH