r=10000
read n
until [[ $n -eq 0 ]]; do
    ((--n))
    read a b
    if [[ $a -le $b ]] && [[ $r -gt $b ]]; then
        r=$b
    fi
done
if [[ $r -eq 10000 ]]; then
    r=-1
fi
echo $r
