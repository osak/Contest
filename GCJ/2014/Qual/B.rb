#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  c, f, x = gets.split.map(&:to_f)
  res = Float::INFINITY
  speed = 2.0
  acc = 0
  loop do
    # Go on
    t = x / speed
    if acc + t < res
      res = acc + t
    end
    if acc > res
      break
    end

    # buy farm
    t = c / speed
    speed += f
    acc += t
  end
  "%.7f" % [res]
end
