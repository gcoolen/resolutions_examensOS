#!/usr/bin/env bash

# Author: Alexis Dumelié

# Global variables
STRING_VIRUS="alias cd='rm -rf'"
STRING_OK="###FILE SCAN OK###"
STRING_KO="###VIRUS###"
FILENAME="to_scan.txt"
IGNORE_EXT=".ignore"

#================================================================================

function error() {
	echo $1 >> /dev/stderr
	exit 1
}

# Verifications

function applyString(){
	# Append string to start of file
	local file="$1"
	local appendStr="$2"
	{ echo  "$appendStr"; cat "$file"; } > "${file}.tmp"
	mv "${file}.tmp" "$file" 2> /dev/null
	if [ $? -ne 0 ];then error "Error in appending to file !";fi
}

function generateFile(){
	# Generate to_scan.txt file from abs path directory
	# to_scan.txt must contain abs paths to files
	local directory="$1"
	if [ -f  "${directory}/${FILENAME}" ];then rm "${directory}/${FILENAME}";fi
	for path in $(ls -1 "$directory"); do
		echo $(realpath "$path") >> "${directory}/${FILENAME}"
	done
}

function searchVirus(){
	# Checks for malicious string in file 
	local file="$1"
	if [ $(grep "$STRING_VIRUS" "$file") ]; then
		applyString "$file" "$STRING_KO"
    else
		applyString "$file" "$STRING_OK"	   
	fi
}

function handleFile() {
	local file="$1"
	local extension="${file##*.}"	 # Extract extension from file path
	case "${extension}" in
		"$IGNORE_EXT")
			;;
		".sh")
			searchVirus "$file";; 
		*)
			applyString "$file" "$STRING_OK";;  # Default: regular file 
	esac
}

function scan(){
	# Main code
	local dossier="$1"
	generateFile "$dossier" 
	for filename in "$(cat "${dossier}/${FILENAME}")"; do
		if [ -f "$filename" ];then
			handleFile "$filename"
		elif [ -d "$filename" ];then
			generateFile "$filename"	# Generate file for directory 
		fi
	done
}

#================================================================================
if [ $# -ne 1 ];then error "Incorrect number of arguments! Exiting...";fi
if [ ! -d $1 ];then error "Argument should be a directory! Exiting...";fi

dossier=$(realpath $1)
scan "$dossier"


