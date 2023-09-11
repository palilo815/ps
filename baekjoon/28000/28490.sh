read n
for ((i = 0; i < n; ++i)); do
    read h w
    area=$((h * w))
    if [[ $r -lt $area ]]; then
        r=$area
    fi
done
echo $r
