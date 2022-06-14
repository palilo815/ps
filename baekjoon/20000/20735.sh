read n
r=0
while [[ $n != 0 ]]; do
    ((--n))
    read s
    if [[ $s = *[pP][iI][nN][kK]* ]] || [[ $s = *[rR][oO][sS][eE]* ]]; then
        ((++r))
    fi
done
if [[ $r = 0 ]]; then
    echo I must watch Star Wars with my daughter
else
    echo $r
fi
