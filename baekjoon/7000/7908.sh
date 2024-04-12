read n
if [[ $((n & (n - 1))) = 0 ]]; then
	echo TAK
else
	echo NIE
fi
