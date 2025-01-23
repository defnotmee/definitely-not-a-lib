#!/usr/bin/env bash

# Based on tyrowhiz's template.
# Usage: bash stress.sh wrong_sol checker generator test_case_count
# - checker should return 0 if the solution is correct and anything else otherwise
# - if the checker needs the original input, it will be on a file named input and
# you could use something like "ifstream ccin("input"); ccin >> something" to read it

# wrong_sol, checker and generator must be WITHOUT extensions

make $1
make $2
make $3

for ((testNum=0;testNum<$4;testNum++))
do
    ./$3 $testNum > input
    ./$1 < input > out
    
    if !(./$2 < out > veredict)
    then
        echo "Error found!"
        echo "Input:"
        cat input
        echo "Output:"
        cat out
        echo "Checker Veredict:"
        cat veredict
        exit
    fi
    echo Passed Test:$testNum
done
echo Passed $4 tests