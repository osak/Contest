#!/usr/bin/env ruby

# [何日目][Lの数][連続したAの数] = パターン数 でDP。

require 'memoize'
include Memoize

def calc(pos, ls, as)
  return 0 if ls == 2 || as == 3
  return 1 if pos == 30
  res = 0
  res += calc(pos+1, ls+1, 0) # L
  res += calc(pos+1, ls, 0) # O
  res += calc(pos+1, ls, as+1) # A
  res
end
memoize :calc

puts calc(0, 0, 0)
