#!/usr/bin/zsh

name=$1
len=`wc -c ${name}.c | cut -d ' ' -f 1 `
for ((i=0; i<$len; i+=1)) do
    res=`echo "1\n$i" | ./$name`
    cor=`cat ${name}.c | ruby -e "s=$<.read;p s.count(s[$i])"`

    if (( res != cor )) then
        echo "$i: exp: $cor, got: $res"
    fi
done
