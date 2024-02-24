# Generates json for vscode snippet
# run this program like this:
# python3 file_to_json.py <file>

import sys


f = open(sys.argv[1],"r")

lines = f.readlines()

for i in range(0, len(lines)-1):
    print('"' + lines[i][:-1] + '",')

print('"' + lines[-1] + '"')