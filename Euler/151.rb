#!/usr/bin/env ruby

# 期待値DP。
# A5の紙は16枚取れて、それぞれが既に使われたかの2^16状態が状態数の上限である。
# （実際にはずっと少ない）
require 'memoize'
include Memoize

def partition(n, main)
  if n == 5
    return [5]
  elsif main
    [partition(n+1, false), partition(n+1, true)].flatten
  else
    [n]
  end
end
memoize :partition

LAST = [5].freeze

def calc(state)
  puts state.join(' ')
  if state == LAST
    # Last day
    return 0
  end
  n = state.size
  res = n == 1 ? 1 : 0
  state.each_with_index do |s, idx|
    next_state = state[0, idx] + state[idx+1...n]
    if s != 5
      next_state += partition(s, true)
      next_state.pop
    end
    next_state.sort!
    res += 1.0/n * calc(next_state)
  end
  res
end
memoize :calc

init = partition(1, true).dup
init.pop
ans = calc(init)
puts "%.6f" % ans
