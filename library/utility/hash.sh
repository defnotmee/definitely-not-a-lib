# From https://github.com/tdas0/lib/blob/master/library/contest/hash.sh

# Usage: bash hash.sh arquivo.cpp l1 l2
# Finds hash of file from line l1 to line l2

sed -n $2','$3' p' $1 | sed '/^#w/d' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6