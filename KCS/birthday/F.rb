#!/usr/bin/env ruby

n = gets.to_i
while n > 1
  if n.odd?
    n = n * 3 + 1
  else
    n /= 2
  end
  puts n
end
