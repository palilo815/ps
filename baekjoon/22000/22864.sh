read a b c m
deg=0
work=0
t=24
while [[ $t != 0 ]]; do
    ((--t))
    if [[ $((deg + a)) -le $m ]]; then
        deg=$((deg + a))
	work=$((work + b))
    else
        deg=$((deg-c))
	if [[ $deg -lt 0 ]]; then
            deg=0
	fi
    fi
done
echo $work
