read n m
read -a a
read -a b
n=$((n > m ? n : m))
r=0
for ((i = 0; i < n; ++i)); do
    r=$((r < b[i] - a[i] ? b[i] - a[i] : r))
done
echo $r
