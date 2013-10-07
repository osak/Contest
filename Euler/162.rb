#!/usr/bin/env ruby

# [桁位置][leading zero][0出現][1出現][A出現] = パターン数
# でDigit DP。

require 'memoize'
include Memoize

def calc(pos, lz, zero, one, a)
  #puts "#{pos} #{lz} #{zero} #{one} #{a}"
  if pos == 16
    return (zero and one and a) ? 1 : 0
  end
  res = 0
  16.times do |digit|
    nlz = lz && (digit == 0)
    nz = zero || (!lz && (digit == 0))
    no = one || (digit == 1)
    na = a || (digit == 10)
    res += calc(pos+1, nlz, nz, no, na)
  end
  res
end
memoize :calc

puts "%X" % calc(0, true, false, false, false)
