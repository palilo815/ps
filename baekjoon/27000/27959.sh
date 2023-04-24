read n m
if [[ $((n * 100)) -ge $m ]]; then
    echo Yes
else
    echo No
fi
