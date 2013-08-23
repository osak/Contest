#!/usr/bin/env ruby

n, m, a, b = gets.split.map(&:to_i)
if a == 0 && b == (n-2)*(m-2)
  if n > m
    n, m = m, n
  end

  if n == 2
    puts m-2
  else
    puts ((n-2+1)/2 + (m-2+1)/2)*2
  end
else
  puts 0
end
