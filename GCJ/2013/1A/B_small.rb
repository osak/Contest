#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  e, r, n = gets.split.map(&:to_i)
  vs = gets.split.map(&:to_i)

  ans = 0
  dp = Array.new(n+1){Array.new(e+1, 0)}
  vs.each_with_index do |v, vi|
    cur = vi+1
    prev = vi
    dp[prev].each_with_index do |pgain, pe|
      cure = [pe+r, e].min
      (0..cure).each do |ne|
        sum = pgain + (cure-ne)*v
        dp[cur][ne] = [dp[cur][ne], sum].max
        ans = [ans, sum].max
      end
    end
  end
  #puts dp.map{|e| e.join(' ')}
  ans
end
