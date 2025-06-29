
# From https://github.com/tdas0/lib/blob/master/library/contest/gethash.sh

# Gets hash of file to compare to the pdf of the library
# Usage: bash gethash.sh arquivo.cpp

echo "" > pref.txt
while IFS= read -r l; do
	echo "$l" >> pref.txt
	echo "$l" > line.txt
	hp=$(echo $(bash hash.sh pref.txt 1 1000) | cut -c-2)
	hl=$(echo $(bash hash.sh line.txt 1 1000) | cut -c-2)
	echo -e "$hp $hl $l"
done < "$1"