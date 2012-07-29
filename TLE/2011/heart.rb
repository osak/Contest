#!/usr/bin/ruby

lines = File.readlines('heart.txt')
str = ''
lines.each { |line|
    start = 0
    start += 1 while start<line.length && line[start]==' '
    tail = start
    tail += 1 while tail<line.length && line[tail]!=' '
    len = tail-start-1
    #len = 255 if len > 255
    start = 255 if start > 255
    str += start.chr
}
puts str.gsub(/"/, '\"')
