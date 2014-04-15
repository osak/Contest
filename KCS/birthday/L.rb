#!/usr/bin/env ruby
a, b = gets.split.map(&:to_i)
puts (a+b)^(a-b)^(a/b)^(a*b)
