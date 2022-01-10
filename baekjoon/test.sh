if [ $# -ne 1 ]; then
    echo "Usage --- {file or directory}"
    exit 1
fi

PASSED=$1

if [[ -d $PASSED ]]; then
    # multiple tests in directory
    echo "run all tests in directory:$PASSED"
    for IN in "$PASSED"/*
    do
        if [[ "$IN" =~ "in" ]]; then
            OUT=("${IN//in/out}")
            ./a < $IN > out && diff out $OUT
        fi
    done
elif [[ -f $PASSED ]]; then
    # single test
    OUT=("${PASSED//in/out}")
    ./a < $PASSED > out && diff out $OUT
else
    echo "$PASSED is not valid"
    exit 1
fi

echo "done"
