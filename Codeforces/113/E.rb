#!/usr/bin/ruby

n = gets.to_i
t = 1
n.times do 
  t *= 3
  t %= 1000000007
end

p ((t + (-1)**(n%2)*3 + 1000000007) / 4 ) % 1000000007
