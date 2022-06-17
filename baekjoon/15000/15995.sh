read a m
for ((i = 1;; ++i)); do
    if [[ $(($a * $i % $m)) = 1 ]]; then
        echo $i
        exit
    fi
done
