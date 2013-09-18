#!/usr/bin/env ruby

# dp[mod] = 和がmodになるsubsetの数 でDP。
require_relative 'util'

dp = Array.new(250, 0)
dp[0] = 1
(1..250250).each do |x|
  mod = fastpow_mod(x, x, 250)
  next_dp = dp.dup
  dp.each_with_index do |val, i|
    next_dp[(i+mod)%250] += val
  end
  dp = next_dp.map{|i| i % (10**16)}
end

puts sprintf("%016d", dp[0]-1)
