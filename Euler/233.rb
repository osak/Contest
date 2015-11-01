#!/usr/bin/env ruby

# memo: 円を8分割して、各区間でa^2 = x^2 + y^2の形で52通りに表せるものの個数を求めればよい。
# 半径はかならず√2が絡むので無理数である。
require 'set'

SQUARES = (1..5000).to_a.map{|a| a**2}.freeze
SQUARES_SET = Set.new(SQUARES)

#puts SQUARES.count{|a| 5000**2-a < a && SQUARES_SET.include?(5000**2-a)}
10000.times do |i|
  l = i**2
  cnt = SQUARES.count{|a| l-a < a && SQUARES_SET.include?(l-a)}
  puts "%4d: %d" % [i, cnt]
end
