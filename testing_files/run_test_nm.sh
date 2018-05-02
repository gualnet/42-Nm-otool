#!/bin/bash

testdir=$1
outdir=(./$1_out)

rm ./ft_nm
rm -r $outdir

mkdir -p $outdir

for pathname in $testdir/*; do
	filename=${pathname##*/}
	# echo "$outdir"/"$filename""_nm_"
	nm "$pathname" > "$outdir"/"$filename""_nm_"
done

make -C ../ && mv ../ft_nm ./

for pathname in $testdir/*; do
	filename=${pathname##*/}
	# echo "$outdir"/"$filename""_nm_"
	./ft_nm "$pathname" > "$outdir"/"$filename""_ft_"
done

for pathname in $testdir/*; do
	filename=${pathname##*/}
	echo "->>" "$outdir"/"$filename""_nm_" "$outdir"/"$filename""_ft_"
	diff "$outdir"/"$filename""_nm_" "$outdir"/"$filename""_ft_"
done

rm ./ft_nm
# rm -r $outdir
