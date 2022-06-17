read n
for ((i = 0; i != $n; ++i)); do
  read x y
  if [[ $x < $y ]]; then
    echo "NO BRAINS"
  else
    echo "MMM BRAINS"
  fi
done
