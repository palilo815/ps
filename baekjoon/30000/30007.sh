read n
for ((i = 0; i < n; i++)); do
	read a b x
	echo $((a * (x - 1) + b))
done
