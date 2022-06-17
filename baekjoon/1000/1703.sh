while true; do
	read a
	if [[ $a = "0" ]]; then
		break
	fi
	res=1
	flag=0
	for x in $a; do
		if [[ flag -eq 1 ]]; then
			res=$(($res*$x))
		elif [[ flag -eq 2 ]]; then
			res=$(($res-$x))
		fi
		flag=$(($flag+1))
		if [[ flag -eq 3 ]]; then
			flag=1
		fi

	done
	echo $res
done
