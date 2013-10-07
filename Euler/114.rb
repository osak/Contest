#!/usr/bin/env ruby

# 愚直にDP。

require 'memoize'

include Memoize

def calc(prev, len)
  return 1 if len == 0
  # place black
  res = calc(:black, len-1)
  # place red
  if prev == :black
    (3..len).each do |rl|
      res += calc(:red, len - rl)
    end
  end
  res
end
memoize :calc

puts calc(:black, 50)
