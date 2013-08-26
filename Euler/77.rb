#!/usr/bin/env ruby

# メモ化再帰で計算する。
# すごく大きい数になるかと思ったが、答えは意外すぎるほど小さかった……。

require 'prime'
require 'memoize'

include Memoize
$primes = Prime.each.take(10000).freeze

def calc_pat(n, lim=$primes.index{|k| k>n}-1)
  return 1 if n == 0
  res = 0
  (0..lim).each do |idx|
    break if $primes[idx] > n
    nval = n - $primes[idx]
    res += calc_pat(nval, idx)
  end
  res
end
memoize :calc_pat

puts calc_pat(10)
(1..Float::INFINITY).each do |i|
  if calc_pat(i) > 5000
    puts i
    break
  end
end
