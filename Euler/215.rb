#!/usr/bin/env ruby

# 直前の行のパターンを覚えてDP。

require 'memoize'
include Memoize

W = 32
H = 10

def calc(row, col, prev_pat, cur_pat)
  return 0 if col == W-1
  return calc(row+1, 0, cur_pat ^ (1<<(W-1)), 0) if col == W
  return 1 if row == H

  #puts "#{row} #{col} #{prev_pat.to_s(2)} #{cur_pat.to_s(2)}"
  res = 0
  # put 2*1
  if prev_pat[col+1] == 0
    res += calc(row, col+2, prev_pat, cur_pat | (1<<(col+1)))
  end
  # put 3*1
  if col+2 < W && prev_pat[col+2] == 0
    res += calc(row, col+3, prev_pat, cur_pat | (1<<(col+2)))
  end
  res
end
memoize :calc

puts calc(0, 0, 0, 0)
