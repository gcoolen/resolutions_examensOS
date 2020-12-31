mkdir dir
mkdir dir/subdir

while IFS= read line; do
    touch $line
done < "files.txt"

for f in $(find dir -iname \*.tex); do
    cp example_tex.tex $f
done