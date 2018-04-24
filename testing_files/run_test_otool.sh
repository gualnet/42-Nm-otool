#!/bin/bash

testdir=$1
outdir=(./$1_out)

rm ./ft_otool
rm -r $outdir

mkdir -p $outdir
make -C ../ && mv ../ft_otool ./

for pathname in $testdir/*; do
	filename=${pathname##*/}
	# echo "$outdir"/"$filename""_nm_"
	echo "Processing $filename"
	otool -t "$pathname" > "$outdir"/"$filename""_otool_"
	./ft_otool -t "$pathname" > "$outdir"/"$filename""_ft_"
done


# for pathname in $testdir/*; do
# 	filename=${pathname##*/}
# 	# echo "$outdir"/"$filename""_otool_"
# done

# for pathname in $testdir/*; do
# 	filename=${pathname##*/}
# 	echo "->>" "$outdir"/"$filename""_otool_" "$outdir"/"$filename""_ft_"
# 	diff "$outdir"/"$filename""_otool_" "$outdir"/"$filename""_ft_"
# done

rm ./ft_otool
# rm -r $outdir