read t
while [[ $t != 0 ]]; do
    ((--t))
    read n
    now=0
    ans=0
    while [[ $n != 0 ]]; do
        ((--n))
        read i o
        ((now += i))
        if [[ $now -lt $o ]]; then
            ((ans += o - now))
            now=$o
        fi
        ((now -= o))
    done
    echo $ans
done
