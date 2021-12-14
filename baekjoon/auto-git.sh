if [ $# -ne 3 ]; then
    echo "Usage --- {file name} {problem #} {'problem name'}"
    echo "e.g. ---- a.rs 1000 'A + B'"
    exit 1
fi

FILE=("$1")
EXTENSION=${FILE##*.} # rs, cpp, py, txt ...

let D=$2/1000*1000

cp $FILE $D/$2.$EXTENSION
git add --all
git commit -m '$3'

echo "done"
