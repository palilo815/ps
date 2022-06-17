read n m
if [[ $(((n - 1) % (m + 1))) -eq 0 ]]; then
    echo "Can't win"
else
    echo "Can win"
fi
