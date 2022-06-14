read x
read y
ans=1
for i in {0..3}; do
    if [[ ${x:i:1} != ${y:i:1} ]]; then
        ((ans *= 2))
    fi
done
echo $ans
