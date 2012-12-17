#!/usr/bin/ruby

n, m, a, b = gets.split.map(&:to_i)
ans = "complete"
(1..m).each do |day|
  if n <= a
    n += b
  end
  c = gets.to_i
  n -= c
  if n < 0
    ans = day
    break
  end
end
puts ans
