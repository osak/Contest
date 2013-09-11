#!/usr/bin/env ruby

# 3項の組をメモしておき、mod Nの上で1回も0を出さずに巡回したらNは条件を満たす。

require 'prime'
require 'set'

cnt = 0
catch(:found) {
  (3..Float::INFINITY).step(2) do |n|
    n = n.to_i
    memo = Set.new
    a, b, c = 1, 1, 1
    loop do
      tag = [a, b, c]
      if memo.include?(tag)
        cnt += 1
        puts n
        if cnt == 124
          throw :found
        end
        break
      end
      memo << tag
      a, b, c = b, c, (a+b+c) % n
      if c == 0
        break
      end
    end
  end
}
