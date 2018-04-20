#!/bin/bash

outdir=(./hell_out)
# outdir=$(dirname `pwd`)

# for pathname in ./hell_out/*_ft_; do
# 	filename_ft=${pathname##*/}
# 	filename=${filename_ft%"_ft_"}
# 	filename_nm=$filename"_nm_"
# 	diff "$outdir"/"$filename_nm" "$outdir"/"$filename_ft"
# 	echo "\n"
# done

for pathname in $outdir/*_ft_; do
	filename_ft=${pathname##*/}
	filename=${filename_ft%"_ft_"}
	filename_nm=$filename"_nm_"
	outputs=(
		"$outdir/$filename_nm"
		"$outdir/$filename_ft"
	)
	# echo "pathname: "$pathname
	# echo "filename: "$filename
	# diff -y "$outdir"/"$filename_nm" "$outdir"/"$filename_ft"
	echo "\033[36m- diff on $filename_nm $filename_ft\033[0m"
	# if result="$(diff <(find ${outputs[0]}) <(find ${outputs[1]}))"; then
	if result="$(diff -y $outdir/$filename_nm $outdir/$filename_ft)"; then
		echo "- Files are the sames"
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