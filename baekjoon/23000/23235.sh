for (( i=1; ; ++i )); do
    read n
    if [[ $n = "0" ]]; then
        break
    fi
    printf "Case %d: Sorting... done!\n" $i
done
