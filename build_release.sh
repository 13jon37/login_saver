#!/bin/bash
mkdir -p build
pushd build
<<<<<<< HEAD
g++ -c ../src/*.cpp -O3 && g++ *.o -o logins
=======
g++ -c ../src/*.cpp -O3 && g++ *.o -o logins_release.out
>>>>>>> 6de833577c3b0341534438f3272fb05972f3f199
popd
