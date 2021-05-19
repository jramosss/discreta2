make

for file in "../grafos"/*
do
    echo $file
    ./test $((1 + $RANDOM % 10)) $((1 + $RANDOM % 10)) $((1 + $RANDOM % 50)) $((1 + $RANDOM % 10)) $((1 + $RANDOM % 10)) $((1 + $RANDOM % 10)) < "$file"
done