#!/usr/bin/ruby

src = $<.readlines

str = ''
13.times { |i|
    b = 0
    src.size.times { |j|
        b <<= 1
        b += 1 if src[j][i] == '1'
        if j % 8 == 7
            str += b.chr
            b = 0
        end
    }
}
print str
