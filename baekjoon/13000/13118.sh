read -a p
read x y r
r=0
for ((i = 0; i < 4; ++i)); do
    if [[ ${p[$i]} = $x ]]; then
        r=$((i + 1))
    fi
done
echo $r
