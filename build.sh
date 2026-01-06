#!/bin/sh

for i in 1 2 3 4 5 6
do
    g++ -Ofast -std=c++20 exercice$i.cpp -o exercice$i
done

g++ -std=c++20 -o boosttest -Wall boosttest.cpp -lboost_unit_test_framework
