#!/usr/bin/env ruby

# ローマ数字を数値に直してから、DPによって最短の表現を求める。
# IVのような表現は、各文字について1回しか使えないことに注意する。

require 'memoize'
include Memoize

ROMAN_DICT = {
  "I" => 1,
  "V" => 5,
  "X" => 10,
  "L" => 50,
  "C" => 100,
  "D" => 500,
  "M" => 1000
}.freeze

ROMAN_COST = {
  1 => 1,
  5 => 1,
  10 => 1,
  50 => 1,
  100 => 1,
  500 => 1,
  1000 => 1,
  4 => 2,
  9 => 2,
  40 => 2,
  90 => 2,
  400 => 2,
  900 => 2
}.freeze

def roman_to_i(_str)
  res = 0
  str = _str.dup
  str.gsub!(/I(V|X)/) {|m|
    res += ROMAN_DICT[m[1]] - 1
    ""
  }
  str.gsub!(/X(L|C)/) {|m|
    res += ROMAN_DICT[m[1]] - 10
    ""
  }
  str.gsub!(/C(D|M)/) {|m|
    res += ROMAN_DICT[m[1]] - 100
    ""
  }
  str.each_char do |c|
    res += ROMAN_DICT[c]
  end
  res
end

def calc_len(n, lim=1000)
  return 0 if n == 0
  return n if lim == 1
  res = 99999
  ROMAN_COST.each_pair do |key, cost|
    next if key > n or key > lim
    next_key = (cost == 2 ? key-1 : key)
    res = [res, cost+calc_len(n-key, next_key)].min
  end
  res
end
memoize :calc_len

puts calc_len(16)
saved = 0
$<.each_line do |line|
  line.chomp!
  saved += line.length - calc_len(roman_to_i(line))
end
puts saved
