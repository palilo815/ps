read t
while [[ $t -ne 0 ]]; do
    ((--t))
    read x y
    echo $((x + y))
done
