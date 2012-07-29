#!/usr/bin/ruby

lines = File.readlines('heart.txt')
lines.each { |line|
    h = {}
    line.each_char { |c|
        next if c == ' '
        h[c] ||= 0
        h[c] += 1
    }
    p h.to_a.sort{|a,b| b[1]<=>a[1]}[0]
}
