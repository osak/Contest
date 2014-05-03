#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  a, b, k = gets.split.map(&:to_i)
  cnt = 0
  a.times do |av|
    b.times do |bv|
      if av & bv < k
        cnt += 1
      end
    end
  end
  cnt
end
