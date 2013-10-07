#!/usr/bin/env ruby

# 2^xのテーブルを用意してDP。
# 大きい数から消費していき、途中で不可能であることが分かったら枝刈りすると速くなる。

require 'memoize'
include Memoize

POWS = (0..83).to_a.map{|a| 2**a}.reverse.freeze
LIM = POWS.reverse.reduce([0]){|acc, val| acc + [acc[-1]+val*2]}.reverse.freeze

puts LIM[-2]
def calc(pos, rem)
  #puts "#{pos} #{rem}"
  if rem == LIM[pos]
    return 1
  end
  if rem > LIM[pos]
    return 0
  end

  res = calc(pos+1, rem)
  rem -= POWS[pos]
  if rem >= 0
    res += calc(pos+1, rem)
    rem -= POWS[pos]
    if rem >= 0
      res += calc(pos+1, rem)
    end
  end
  res
end
memoize :calc

puts calc(0, 10**25)
