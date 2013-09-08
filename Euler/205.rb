#!/usr/bin/env ruby

# ある合計値になるパターン数はDPで求められる。
# あとはPeterの各合計に対し、Colinが負けるパターンの確率を掛けて合計する。

require 'pry'

def do_dp(dice, n)
  max = dice.max * n
  arr = Array.new(max+1, 0)
  arr[0] = 1
  n.times do
    n_arr = Array.new(max+1, 0)
    arr.each_with_index do |pat, sum|
      next if pat == 0
      dice.each do |die|
        n_arr[sum+die] += pat
      end
    end
    arr = n_arr
  end rescue binding.pry
  arr
end

peter = do_dp([1,2,3,4], 9)
colin = do_dp([1,2,3,4,5,6], 6)
colin_sum = colin.dup
(1..colin_sum.size-1).each do |idx|
  colin_sum[idx] += colin_sum[idx-1]
end

n_peter = peter.inject(&:+).to_f
n_colin = colin.inject(&:+).to_f
prob = 0.0
peter.each_with_index do |val, idx|
  next if idx == 0
  prob += val/n_peter * colin_sum[idx-1]/n_colin
end
puts "%.7f" % prob
