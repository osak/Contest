#!/usr/bin/env ruby

# 114のコードでmを指定できるようにして、全探索。

require 'memoize'

include Memoize

def calc(prev, len, m)
  return 1 if len == 0
  # place black
  res = calc(:black, len-1, m)
  # place red
  if prev == :black
    (m..len).each do |rl|
      res += calc(:red, len - rl, m)
    end
  end
  res
end
memoize :calc

len = 0
loop do
  val = calc(:black, len, 50)
  if val > 1000000
    puts len, val
    break
  end
  len += 1
end


