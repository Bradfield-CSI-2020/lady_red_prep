#!ty/bin/bash
n=1
while true; do
    "./$1" >logout.txt 2>logerr.txt
    n=$((n+1))
    echo $n
    if grep -q 'wrong' logout.txt ;
        then
            cat logout.txt
            cat logerr.txt
            exit
        fi
done
