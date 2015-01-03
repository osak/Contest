# Name: ホリドッグ
# Level: 1
# Category: やるだけ
# Note:

# やるだけ。
# Rubyならprime?で一瞬。

require 'prime'
n = gets.to_i

puts ((1..n).inject(&:+).prime? ? "WANWAN" : "BOWWOW")
