#!/usr/bin/env bash

clear && echo "Running test: "
rm -rf testDir/
cp -r testDir.bk/ testDir/
echo --------------------------------------------------
./q1.sh src_file 
echo --------------------------------------------------
cat tmp/log_renamer && rm tmp/log_renamer

