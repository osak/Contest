#!/usr/bin/ruby

n, x = gets.split.map(&:to_i)
arr = gets.split.map(&:to_i).sort

cnt = 0
if arr.index(x).nil?
  arr << x
  cnt += 1
  arr.sort!
end

median = (arr.size+1) / 2 - 1
ni = arr.index(x)
ri = arr.rindex(x)

if arr[median] == x
  p cnt
  exit
end

# right adjustment
rcnt = n*100
if ni > median
  rcnt = 0
  target = ni

  if arr.size.even?
    rcnt += 1
    target -= 1
  end
  rcnt += (target-median) * 2
end

# left adjustment
lcnt = n*100
if ri < median
  lcnt = 0
  target = ri

  if arr.size.odd?
    lcnt += 1
    target += 1
  end
  lcnt += (median-target) * 2
end

p [rcnt,lcnt].min + cnt
