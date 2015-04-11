#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  smax, str = gets.chomp.split
  acc = 0
  ans = 0
  str.each_char.with_index do |n, i|
    if acc < i
      ans += i - acc
      acc = i
    end
    acc += n.to_i
  end
  ans
end
