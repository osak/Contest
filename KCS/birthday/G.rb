#!/usr/bin/env ruby

require 'prime'
require 'set'

primes = Set.new(Prime.take(100000))
#puts primes.to_a.max
start, h, w = gets.split.map(&:to_i)
raise if start + h*w - 1 > 1299709
i = start
h.times do
  arr = []
  w.times do
    arr << (primes.include?(i) ? :Y : :N)
    i += 1
  end
  puts arr.join(" ")
end
