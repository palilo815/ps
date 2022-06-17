read n
digit=$(((n + 8) / 9))
if [[ $((n & 1)) -eq 1 && $((digit & 1)) -eq 0 ]]; then
    ((++digit))
fi
echo $digit
