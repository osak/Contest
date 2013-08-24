#!/usr/bin/env ruby

# 外側の1辺の長さを決めると、穴の最小の大きさがわかる。
# 穴の1辺の長さは2ずつ増えていくので、簡単にパターン数を求められる。

N = 1_000_000
#N = 12
#N = 100

res = 0
(1..N).each do |x|
  # With hole
  hole_min = (x*x > N) ? ((x*x - N)**0.5).to_i : 1
  if x.even? and hole_min.odd?
    hole_min += 1
  elsif x.odd? and hole_min.even?
    hole_min += 1
  end
  if x*x - hole_min*hole_min > N
    hole_min += 2
  end

  if hole_min <= x-2
    res += (x-2 - hole_min) / 2 + 1
    #puts "#{x}: #{hole_min} #{res}"
  end
end

puts res
