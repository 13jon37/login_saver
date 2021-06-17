#!/bin/bash
pushd build
g++ -c ../src/*.cpp -g -Wall && g++ *.o -o logins.out 
popd
