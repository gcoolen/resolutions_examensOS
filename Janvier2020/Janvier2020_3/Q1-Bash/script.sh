#!/bin/bash
# 02.01.21
# Examen blanc de janvier 2021
# Info-f-201
# Author: Attilio Discepoli

change_extension () {
	if [[ -f "$1" ]]; then
		if [[ "${1:(-3)}" == "mp3" ]]; then
			mv "$1" "${1%%mp3}ogg"
		elif [[ "${1:(-3)}" == "mp4" ]]; then
			mv "$1" "${1%%mp4}ogv"
		elif [[ "${1:(-3)}" == "wav" ]]; then
			mv "$1" "${1%%wav}flac"
		elif [[ "${1:(-3)}" == "jpg" ]]; then
			mv "$1" "${1%%jpg}png"
		fi
	else
		echo "$1 doesn't exists" >> /tmp/log_renamer
	fi
}

[ ! "$#" -eq "1" ] && echo "[ ERROR ] Invalid number of parameters" >> /tmp/log_renamer && exit 1 # Nombre de paramètre == 1 ?
[ ! -f "$1" ] && echo "[ ERROR ] Parameter must be a file" >> /tmp/log_renamer && exit 1 

> /tmp/log_renamer # Flush log file

FILE_SRC=$1;

while read path; do
	if [ -d $path ]; then # Path is a directory
		ls "$path" | while read sub_file; do 
			if [ -f ${path}/${sub_file} ]; then
				echo $sub_file
				change_extension ${path}/${sub_file}
			fi
		done
	else 	# Path is a file1
		change_extension $path
	fi
done < "$FILE_SRC"
