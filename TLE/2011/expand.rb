#!/usr/bin/ruby

code = gets.chomp
h = {}
h.default = 0
code.each_char{|c| h[c] += 1}
code += "////"
h.each_pair {|c,k|
    code += c*(3-k)
}
puts code
