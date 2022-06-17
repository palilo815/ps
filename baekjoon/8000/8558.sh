d=(1 1 2 6 4 0)
read n
echo ${d[$((n < 5 ? n : 5))]}
