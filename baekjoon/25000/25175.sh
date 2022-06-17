read n m k
m=$(((m + k - 4) % n))
m=$(((m + n) % n + 1))
echo $m
