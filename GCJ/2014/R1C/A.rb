#!/usr/bin/env ruby

require 'rational'

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  p, q = gets.split('/').map(&:to_i)
  r = p.to_r / q
  if r.denominator.to_s(2).count('1') != 1
    "impossible"
  else
    res = nil
    ok = false
    (1..40).each do |i|
      sum = r * 2
      if sum == 1
        res ||= i
        ok = true
        break
      end
      if sum >= 1
        res ||= i
        r = sum - 1
      else
        r *= 2
      end
    end
    if ok && res
      res
    else
      "impossible"
    end
  end
end
