#!/usr/bin/ruby

s = gets
pos = s.index('0') || 0
puts s[0...pos] + s[pos+1..-1]
