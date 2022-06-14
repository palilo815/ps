read x
ans=0
while [[ $x != 1 ]]; do
    ((++ans))
    if [[ $((x % 2)) = 1 ]]; then
        x=$((3 * x + 1))
    else
        ((x /= 2))
    fi
done
echo $ans
