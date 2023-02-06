read s
t=${s//[^_]}
echo $((${#s} + 2 + ${#t} * 5))
