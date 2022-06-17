read n
r=1
while [[ $n -ne 0 ]]; do
    ((r *= n))
    ((--n))
done
echo $r
