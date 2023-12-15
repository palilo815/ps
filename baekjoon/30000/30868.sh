read t
for ((i = 0; i < t; ++i)); do
	read n
	for ((j = 0; j < n / 5; ++j)); do
		printf "++++ "
	done
	for ((j = 0; j < n % 5; ++j)); do
		printf "|"
	done
	echo
done
