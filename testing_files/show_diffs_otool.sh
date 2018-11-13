#!/bin/bash

testdir=$1
outdir=(./$1)
# outdir=$(dirname `pwd`)

for pathname in $outdir/*_ft_; do
	filename_ft=${pathname##*/}
	filename=${filename_ft%"_ft_"}
	filename_otool=$filename"_otool_"
	outputs=(
		"$outdir/$filename_otool"
		"$outdir/$filename_ft"
	)
	
	echo "\033[36m- diff on $filename_otool $filename_ft\033[0m"
	
	if result="$(diff -y $outdir/$filename_otool $outdir/$filename_ft)"; then
		echo "- No Diff"
	else
		echo "\033[31m- Files are differents\033[0m"
		# result=$result | grep -e "<" -e ">"
		# echo "\033[33m- result : \n$result\033[30m"
	fi
	echo "next file(enter) - print diff(p) - exit(e):"
	read stop_input
	if [ "$stop_input" == "e" ]
	then
		exit 0;
	elif [ "$stop_input" == "p" ]
	then
		result=$result | grep -e "<" -e ">" -e "|"
		echo "\033[33m- result : \n$result\033[30m"
	fi
	echo "-------------------\n"
done