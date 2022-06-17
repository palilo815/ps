read a b n w
cnt_ans=0
for ((i = 1; i < $n; ++i)); do
  if [[ $(($a * $i + $b * ($n - $i))) -eq w ]]; then
    ((++cnt_ans))
    x=$i
    y=$(($n - $i))
  fi
done
if [[ $cnt_ans = 1 ]]; then
  echo $x $y
else
  echo -1
fi
