read x
for (( i=1; ; ++i )); do
	if [[ $((x % i)) -ne 0 ]]; then
		mn=$i
		break
	fi
done
for (( i=x; ; --i )); do
	if [[ $((x % i)) -ne 0 ]]; then
		mx=$i
		break
	fi
done
echo $mn $mx
