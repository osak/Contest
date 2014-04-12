#!/usr/bin/env ruby

n, w = gets.split.map(&:to_i)
items = n.times.map{gets.split.map(&:to_i)}
dp = Array.new(w+1, nil)
dp[0] = 0
items.each do |x, v|
  (0..w-x).each do |pw|
    if dp[pw]
      val = dp[pw] + v
      dp[pw+x] = val if dp[pw+x].nil? or dp[pw+x] < val
    end
  end
end
puts dp.compact.max
