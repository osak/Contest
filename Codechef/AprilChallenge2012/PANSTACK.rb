#!/usr/bin/ruby

MOD = 1000000007
gets.to_i.times do
  n = gets.to_i

  dp = Array.new(n+1) { Array.new(n+1, 0) }
  dp[1][1] = 1
  (2..n).each do |i|
    (1..i).each do |r|
      dp[i][r] = dp[i-1][r]*r + dp[i-1][r-1]
      dp[i][r] %= MOD
    end
  end

  p dp[n].reduce{|acc,i| (acc+i) % MOD}
end
