read n
if [[ $n -le 99 ]]; then
    echo 99
    exit
fi
a=$n
while [[ $a != *99 ]]; do
    ((++a))
done
b=$n
while [[ $b != *99 ]]; do
    ((--b))
done
if [[ $((n - b)) -lt $((a - n)) ]]; then
    a=$b
fi
echo $a
