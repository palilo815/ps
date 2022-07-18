read n
until [[ $n = 0 ]]; do
    ((--n))
    read s
    s=${#s}
    if [[ 6 -le $s ]] && [[ $s -le 9 ]]; then
        echo yes
    else
        echo no
    fi
done
