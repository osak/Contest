#!/usr/bin/env ruby

# 173の結果より、タイル数100万以下のhollow laminaeは160万個程度しかない。
# よって、全て列挙してタイル数を数えればよい。

N = 1_000_000
#N = 12
#N = 100

cnt = Array.new(N+1, 0)
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
    (hole_min..x-2).step(2).each do |hole|
      num_tile = x*x - hole*hole
      cnt[num_tile] += 1
    end
  end
end

puts cnt.count{|a| a == 15}
res = 0
(1..10).each do |sum|
  res += cnt.count{|a| a == sum}
end
puts res
