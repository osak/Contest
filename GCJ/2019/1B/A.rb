#!/usr/bin/env ruby

t = gets.to_i
(1..t).each do |cn|
  pv, q = gets.split.map(&:to_i)
  dp_x = [0] * (q+2) # coord - 1
  dp_y = [0] * (q+2) # coord - 1

  pv.times do
    x, y, c = gets.chomp.split
    x = x.to_i
    y = y.to_i
    case c
    when 'N'
      dp_y[y+2] += 1
    when 'S'
      dp_y[0] += 1
      dp_y[y+1] += -1
    when 'E'
      dp_x[x+2] += 1
    when 'W'
      dp_x[0] += 1
      dp_x[x+1] += -1
    end
  end

  max_x = 0
  max_y = 0
  (1..q+1).each do |pos|
    dp_x[pos] += dp_x[pos-1]
    dp_y[pos] += dp_y[pos-1]
    if dp_x[pos] > max_x
      max_x = dp_x[pos]
    end
    if dp_y[pos] > max_y
      max_y = dp_y[pos]
    end
  end

  ans_x = dp_x[1..q+1].index(max_x)
  ans_y = dp_y[1..q+1].index(max_y)
  puts "Case ##{cn}: #{ans_x} #{ans_y}"
end

