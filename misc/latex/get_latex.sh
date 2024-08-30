# From https://github.com/tdas0/lib/blob/master/latex/getlatex.sh

g++ -std=c++17 -o get_latex get_latex.cpp -O2
./get_latex $1 > definitely-not-a-lib.tex
rubber -d definitely-not-a-lib
mv definitely-not-a-lib.pdf ../pdf
rm tmp.cpp pref.cpp
rm get_latex definitely-not-a-lib.aux definitely-not-a-lib.toc definitely-not-a-lib.out