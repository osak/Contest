#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  r, t = gets.split.map(&:to_i)
  left, right = -1, 2*10**18
  while left < right
    center = (left+right)/2
    need = 2*center**2 + (2*r+3)*center + 2*r+1
    #puts "#{left} #{right} #{need}"
    if need > t
      right = center
    else
      left = center+1
    end
  end
  left
end
