read n
r=6
for ((i = 11; i <= n; ++i)); do
    ((r *= i))
done
echo $r
