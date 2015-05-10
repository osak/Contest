#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  d = gets.to_i
  ps = gets.split.map(&:to_i).sort
  ans = ps.max
  (1..ps.max).each do |h|
    turn = 0
    ps.each do |p|
      if p > h
        turn += (p+h-1)/h - 1
      end
    end
    if ans > turn+h
      ans = turn+h
    end
  end
  ans
end
