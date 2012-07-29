#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

def max_sup(t)
  if t <= 2
    [-1, -1, 2][t%3]
  else
    [t/3+1, t/3+1, t/3+2][t%3]
  end
end

def max_nosup(t)
  if t <= 2
    [0, 1, 1][t%3]
  else
    [t/3, t/3+1, t/3+1][t%3]
  end
end

solve do
  n, s, p, *ts = gets.split.map(&:to_i)

  dp = Array.new(n+1){Array.new(s+1, 0)}
  (1..n).each do |ni|
    sup_d = max_sup(ts[ni-1]) >= p ? 1 : 0
    nosup_d = max_nosup(ts[ni-1]) >= p ? 1 : 0
    (0..s).each do |ns|
      dp[ni][ns] = dp[ni-1][ns] + nosup_d
      dp[ni][ns] = [dp[ni][ns], dp[ni-1][ns-1] + sup_d].max if ns > 0
    end
  end

  dp[n][s]
end
