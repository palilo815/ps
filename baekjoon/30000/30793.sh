read p r
if ((p * 5 < r)); then
	echo weak
elif ((p * 5 < r * 2)); then
	echo normal
elif ((p * 5 < r * 3)); then
	echo strong
else
	echo very strong
fi
