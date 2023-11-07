read a b c d n
sum=$((a + b + c + d))
need=$((4 * n))
if [[ $sum -lt $need ]]; then
	echo $((need - sum))
else
	echo 0
fi
