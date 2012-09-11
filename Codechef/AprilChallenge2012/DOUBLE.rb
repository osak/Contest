#!/usr/bin/ruby

t = gets.to_i
t.times do
  n = gets.to_i
  n -= 1 if n.odd?
  p n
end
