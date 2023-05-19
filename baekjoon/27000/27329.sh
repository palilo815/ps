read n
read s
half=$((n / 2))
if [[ ${s:0:half} = ${s:half} ]]; then
    echo Yes
else
    echo No
fi
