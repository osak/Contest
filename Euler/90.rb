#!/usr/bin/env ruby

# 全探索。

require 'set'

def check_pair(a, b, d1, d2)
  (a.include?(d1) && b.include?(d2)) || (a.include?(d2) && b.include?(d1))
end

SQUARES = (1..9).to_a.map{|i| i**2}.freeze
SQ_DIGITS = SQUARES.map{|n| ("%02d" % n).split(//).map(&:to_i)}.freeze

def check(a, b)
  SQ_DIGITS.all?{|d1, d2| check_pair(a, b, d1, d2)}
end

DIGITS = (0..9).to_a
ans = 0
DIGITS.combination(6) do |dice1|
  puts dice1.join(' ')
  s1 = Set.new(dice1)
  s1 << 6 if s1.include?(9)
  s1 << 9 if s1.include?(6)
  DIGITS.combination(6) do |dice2|
    s2 = Set.new(dice2)
    s2 << 6 if s2.include?(9)
    s2 << 9 if s2.include?(6)
    ans += 1 if check(s1, s2)
  end
end
puts ans / 2
