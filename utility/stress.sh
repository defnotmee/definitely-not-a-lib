# Based on tyrowhiz's template.
# Usage: bash stress.sh wrong_sol bruteforce generator test_case_count
# Note that you won't put the extension on the arguments

#!/usr/bin/env bash
make $1
make $2
make $3

for ((testNum=0;testNum<$4;testNum++))
do
    ./$3 $testNum > input
    ./$2 < input > outSlow
    ./$1 < input > outWrong
    if !(cmp -s "outWrong" "outSlow")
    then
        echo "Error found!"
        echo "Input:"
        cat input
        echo "Wrong Output:"
        cat outWrong
        echo "Slow Output:"
        cat outSlow
        exit
    fi
    echo Passed Test:$testNum
done
echo Passed $4 tests