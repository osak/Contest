#!/usr/local/bin/zsh

cnt=0
for year in `seq 1901 2000`;
do
	for month in `seq 1 12`;
	do
		num=`cal $month $year | head -n3 | tail -n1 | wc -w`
		if [ $num -eq 7 ]; then
			let cnt="${cnt}+1"
		fi
	done
	echo $year
done

echo $cnt
