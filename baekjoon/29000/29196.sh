read k
k=${k:2}
echo YES
echo ${k#"${k%%[!0]*}"} $((10 ** ${#k}))
