#!/usr/bin/ruby

dp = Array.new(91){Array.new(10, 0)}
(0..9).each do |n|
  dp[n][1] = 1
end
(1..9).each do |k|
  dp[1][k] = 1
end

(2..9).each do |k|
  (2..90).each do |n|
    sum = 0
    min = [1, n-9].max
    (min..n).each do |prev|
      sum += dp[prev][k-1]*k
    end
    dp[n][k] = sum
  end
end

(0..90).each do |n|
  printf("%9d"*9, *dp[n][1..-1])
  puts ""
end
