#!/usr/bin/ruby

src = $<.read
str = ''
pos = 0
while pos < src.length
    cur = src[pos]
    if cur == 0.chr
        org = pos
        pos += 1 while pos < src.length && src[pos] == cur
        str += cur + (pos-org).chr
    else
        str += cur
        pos += 1
    end
end
puts str
