#!/usr/bin/env ruby

# 普通にDP。

require 'memoize'

include Memoize

def calc(sum, lim=sum-1)
  if sum == 0
    return 1
  end

  res = 0
  (1..[lim, sum].min).each do |i|
    res += calc(sum - i, [lim, i].min)
  end

  res
end
memoize :calc

puts calc(100)
