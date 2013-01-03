#!/usr/bin/zsh

echo 26 >> LETTER_ALL.in
for f in `ls LETTER_CHARS`; do
    cat LETTER_CHARS/$f >> LETTER_ALL.in
    echo >> LETTER_ALL.in
done
