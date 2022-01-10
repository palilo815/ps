#if [ $# -ne 3 ]; then
#    echo "Usage --- {file name} {problem #} {'problem name'}"
#    echo "e.g. ---- a.rs 1000 'A + B'"
#    exit 1
#fi

PASSED=$1

if [[ -d $PASSED ]]; then
    # multiple tests in directory
    echo "run all tests in directory:$PASSED"
    for file in "$PASSED"/*
    do
        if [[ "$file" =~ "in" ]]; then
            echo "$file is input!"
            #out=("${file//in/out}")
            #if [ -e $out ]
            #then
            #    ./a < $file > out && diff out $out
            #else
            #    echo "oops... output does not exist"
            #fi
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
