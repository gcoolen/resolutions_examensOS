#!/usr/bin/env bash

# Author: Alexis Dumelié

# Two params: src, dest
# Recursively go thourgh src, create a dir in dest for each file type
# If two files with same name: error
# (CANNOT use ls -r, find, awk)

#==================================================
function error {
	echo $1 > /dev/stderr
	exit 1
}

function error_noExit {
	echo $1 > /dev/stderr
}

#==================================================
# Check params

if [ $# -ne 2 ];then
	error "Must give 2 arguments !"
fi
if [ ! -d $1 ]; then
	error "Given SRC is not a dir !"
fi
if [ ! -d $2 ];then
	error "Given DEST is not a dir !"
fi

SRC=$1
DST=$2

# Go through DEST recursively:
#	- list files in DEST
#	- if dir list files in dir, etc
#	- else [create /SRC/extDir] and cp

to_visit=("${SRC}")	
while [ ${#to_visit[@]} -gt 0 ];do	# While len(to_visit) > 0
	cwd=${to_visit[0]}
	to_visit=(${to_visit[@]:1})	# Pop element into cwd

	for file in ${cwd}/*;do 
		if [ -d "$file" ];then
			to_visit+=("$file")
		else
			if [[ "${file}" == *"."* ]] && [[ -f "${file}" ]];then
				extension="${file##*.}"	
			else
				extension=""
			fi
			directory="${DST}/${extension}"
			mkdir -p "${directory}" 
			if [ -e "${directory}/${file}" ];then
				error "Cannot deal with duplicates !"
			fi
			if ! cp -p "${file}" "${directory}" 2> /dev/null;then
				# Redirect cp error to null and print custom message
				error_noExit "Bad permission on ${file}, skipping it..."
			fi
		fi
	done
done
