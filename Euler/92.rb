#!/usr/bin/env ruby

# メモしながら愚直に計算する。

def calc_step(n)
  res = 0
  n.to_s.each_char do |c|
    i = c.to_i
    res += i*i
  end
  res
end

res = 0
memo = {}
(1..10_000_000).each do |i|
  n = i
  history = []
  arrive = nil
  puts i
  loop do
    if n == 1
      arrive = false
      break
    elsif n == 89 || memo[n]
      arrive = true
      break
    else
      history << n
      n = calc_step(n)
    end
  end
  if arrive
    res += 1
    history.each do |i|
      memo[i] = true
    end
  end
end

puts res
