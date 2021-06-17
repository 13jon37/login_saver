#!/bin/bash
pushd build
g++ -c ../src/*.cpp -O3 && g++ *.o -o logins_release.out 
popd
