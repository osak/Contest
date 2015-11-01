#!/usr/bin/env ruby

require 'prime'

def totient(n)
  res = n
  n.prime_division.each do |pr, x|
    res /= pr
    res *= pr - 1
  end
  res
end

memo = {1 => 1}
ans = 0
#Prime.each(40000000) do |pr|
2.upto(40000000).lazy.select(&:even?).each do |pr|
  puts "testing #{pr}"
  history = []
  cur = pr
  while not memo.has_key?(cur)
    history << cur
    cur = totient(cur)
  end
  len = memo[cur]
  history.reverse_each.with_index do |h, idx|
    memo[h] = len + idx + 1
  end
  if memo[pr] == 25
    ans += pr
    puts pr
  end
end

puts ans
