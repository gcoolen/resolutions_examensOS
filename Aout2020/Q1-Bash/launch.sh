#!/usr/bin/env bash

clear
rm -rf project/flaglist_output/ 
echo Launch: 
./flaglist project c TODO BUG
echo Done. 
ls project/flaglist_output/*
echo LOG:
cat project/flaglist_output/flaglist.log


