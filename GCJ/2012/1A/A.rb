#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  a, b = gets.split.map(&:to_i)
  ps = gets.split.map(&:to_f)
  b += 1

  keep = ps.inject(b-a){|a,v| a*v} + (2*b-a)*(1-ps.inject(&:*))
  #p keep
  bs = b*100
  prob = 1.0
  a.times do |backpos|
    bscnt = a-backpos
    bs = [bs, -prob*b + 2*b-a+2*bscnt].min
    prob *= ps[backpos]
  end
  enter = b+1

  sprintf "%.7f", [keep, bs, enter].min
end
