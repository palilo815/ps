declare -A cnt
read n
for ((t = 0; t < $n; ++t)); do
  read sentence
  for word in $sentence; do
    for ((i = 0 ; i < ${#word}; ++i)); do
     ((++cnt[${word:$i:1}]))
    done
  done
done
for c in {a..z}; do
  if [[ cnt[$c] -ne 0 ]]; then
    echo $c $((cnt[$c]))
  fi
done
for c in {A..Z}; do
  if [[ cnt[$c] -ne 0 ]]; then
    echo $c $((cnt[$c]))
  fi
done
