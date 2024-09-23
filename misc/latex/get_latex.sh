# From https://github.com/tdas0/lib/blob/master/latex/getlatex.sh

g++ -std=c++17 -o get_latex get_latex.cpp -O2
./get_latex $1 > definitely-not-a-lib.tex
rm get_latex definitely-not-a-lib.aux definitely-not-a-lib.toc definitely-not-a-lib.out pref.cpp tmp.cpp