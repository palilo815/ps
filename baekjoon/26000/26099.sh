read n
while [[ $n -ge 0 ]]; do
    if [[ $((n % 5)) -eq 0 ]]; then
        ((r += n / 5, n = 0))
        break
    fi
    ((r += 1, n -= 3))
done
if [[ $n -eq 0 ]]; then
    echo "$r"
else
    echo -1
fi
