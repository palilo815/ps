read n
read a b
m=$((a / 2 + b))
echo $((n < m ? n : m))
