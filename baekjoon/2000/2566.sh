mx=-1
for ((i = 0; i < 9; ++i)); do
    read -a a
    for ((j = 0; j < 9; ++j)); do
        if [[ ${a[j]} -gt $mx ]]; then
            mx=${a[j]}
            r=$i
            c=$j
        fi
    done
done
echo $mx
echo $((r + 1)) $((c + 1))

