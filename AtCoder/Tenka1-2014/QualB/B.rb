#!/usr/bin/env ruby

MOD = 1000000007
n = gets.to_i
s = gets.chomp

ts = n.times.map{gets.chomp}
dp = Hash.new
dp[-1] = 1
s.length.times do |i|
  next if dp[i-1].nil?
  ts.each do |t|
    if s[i,t.length] == t
      dp[i + t.length-1] ||= 0
      dp[i + t.length-1] += dp[i-1]
      dp[i + t.length-1] %= MOD
    end
  end
end
puts dp[s.length-1] || 0
