read n
if [[ $((n % 2)) -eq 1 ]]; then
    echo -n $n ""
fi
half=$((n / 2))
for ((i = half; i; --i)); do
    echo -n $i $((i + half)) ""
done
