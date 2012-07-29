#!/usr/bin/ruby

def hash(s)
    h = 0
    s.each_byte { |b|
        h = (h*256+b) % 1009
    }
    h
end

str = ARGF.readlines.join('')
