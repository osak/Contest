#!/usr/bin/env ruby

require 'prime'

LIMIT = 1_000_000

ans = 0
Prime.take_while{|pr| pr < LIMIT}.each do |pr|
  lim = pr / 3
  (1..lim).each do |k|
    rhs = k**3
    l, r = 0, k
    res = nil
    while l+1 < r
      n = (l+r) / 2
      val = n*n*(n+pr)
      if val == rhs
        res = n
        break
      elsif val < rhs
        l = n+1
      else
        r = n
      end
    end
    if res
      puts "#{res}^3 + #{res}^2*#{pr} = #{k}^3"
      ans ++ 1
      break
    end
  end
end

puts ans
