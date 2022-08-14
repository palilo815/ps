read n m a k
echo $((a - k + 1 < n ? a - k + 1 : n)) $(((a - k + m - 1) / m + 1))
