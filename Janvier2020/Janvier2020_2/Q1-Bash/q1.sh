#!/usr/bin/env bash

# Author: Alexis Dumelie

# Arg1: file with paths (1 per line)
# For path in file and switch file extensions based on table
# If path = dir, go through files in dir, but NOT recursive
# Log errors to : /tmp/log_renamer (Note: put as tmp/log_renamer)

#============================================================
log_file="tmp/log_renamer"
function logerror {
	echo $1 >> "${log_file}" 
}

function changeExt {
	local file=$1
	local newExt=$2
	
	mv "${file}" "${file%.*}.${newExt}" 2> "${log_file}"
}

function handleFile {
	local file="$1"
	local extension="${file##*.}"	 # Extract extension from file path
	case "${extension}" in
		"mp3")
			changeExt "${file}"  "ogg";;
		"mp4")
			changeExt "${file}"  "ogv";;
		"wav")
			changeExt "${file}" "flac";;
		"jpg")
			changeExt "${file}"  "png";;
		*)
			;;						# Default do nothing
	esac
}
#============================================================
# Check parameters
if [ $# -ne 1 ];then logerror "Incorrect number of arguments! Exiting..."; exit 1;fi
if [ ! -f $1 ];then logerror "Argument should be a file ! Exiting...";exit 1;fi

src_file=$1
while read -r file_path;do
	if [ -f "${file_path}" ];then
		handleFile "${file_path}"
	else
		# Go through files in given directory, but is not recursive
		for nested_file_path in "${file_path}"/*
	   	do
			handleFile "${nested_file_path}"
		done
	fi
done < "$src_file"   
