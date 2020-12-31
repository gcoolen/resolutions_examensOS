mkdir dir
mkdir dir/sub_dir

while IFS= read line
do
    touch "$line"
done < "paths_for_gen.txt"


