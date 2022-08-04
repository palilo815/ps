read z
until [[ $z -eq 0 ]]; do
    ((--z))
    read w k
    echo $((w * k / 2))
done
