#!/usr/bin/env ruby

def getmax(cur, lim, d)
  if d > 0
    (lim-cur) / d
  elsif d < 0
    (cur-1) / (-d)
  else
    1000000000
  end
end

n, m = gets.split.map(&:to_i)
x, y = gets.split.map(&:to_i)
k = gets.to_i

ans = 0
k.times do
  dx, dy = gets.split.map(&:to_i)
  max_x = getmax(x, n, dx)
  max_y = getmax(y, m, dy)
  maxstep =  [max_x, max_y].min
  x += dx*maxstep
  y += dy*maxstep
  ans += maxstep
end

p ans
