#!/bin/bash

filedir=$1
searchstr=$2
lines=0
files=0
old_file=""

if [ $# -lt 2 ];
then
	echo "Wrong format"
	exit 1
fi

if [ ! -d $filedir ]
then
	echo "Directory does not exist"
	exit 1
fi

grep -R $searchstr $filedir > result.txt

while read -r line;
do
	lines=$(( $lines + 1 ))
	tmp=$(echo "$line" | awk -F ':' '{print $1}')
	if [ "$tmp" != "$old_file" ]
	then
		files=$(( $files + 1 ))
		old_file=$tmp
	fi	
done < result.txt
rm -rf result.txt

echo "The number of files are $files and the number of matching lines are $lines"
