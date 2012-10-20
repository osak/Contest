#!/usr/bin/ruby

# 消費税(切り捨て)は 合計金額*5/100 で計算できる．
# 小数は誤差死する可能性があるので使わない．
n = gets.to_i
sum = 0
n.times do
  a, b = gets.split.map(&:to_i)
  sum += a*b
end
tax = sum*5/100
puts sum+tax
