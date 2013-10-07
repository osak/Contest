#!/usr/bin/env ruby

# 愚直に計算する。

require 'prime'
require 'set'

def squarefree?(n)
  n.prime_division.all?{|d| d[1] == 1}
end

nums = Set.new
nums << 1
row = [1]
50.times do
  puts row.join(' ')
  tmp = [1]
  (0...row.size-1).each do |i|
    v = row[i] + row[i+1]
    tmp << v
    nums << v
  end
  tmp << 1
  row = tmp
end

puts nums.select{|a| squarefree?(a)}.inject(&:+)
