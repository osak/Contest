#!/usr/bin/env ruby

DIGITS = (0..9).to_a.freeze
ALL_PAIR = DIGITS.product(DIGITS).freeze
CARRY_PAIR, NON_CARRY_PAIR = ALL_PAIR.partition{|a| a[0]+a[1] >= 10}
NON_ZERO_CARRY_PAIR = CARRY_PAIR.reject{|a| (a[0] == 0) or (a[1] == 0)}
NON_ZERO_NON_CARRY_PAIR = NON_CARRY_PAIR.reject{|a| (a[0] == 0) or (a[1] == 0)}

even = proc{|a| (a[0]+a[1]).even?}
odd = proc{|a| (a[0]+a[1]).odd?}

puts NON_ZERO_CARRY_PAIR.count(&odd)
puts NON_CARRY_PAIR.count(&even)

ans = 0
(1..3).each do |len|
  paircnt = (len+1) / 2
  # all non_carry case
  ans += NON_ZERO_NON_CARRY_PAIR.count(&odd) * NON_CARRY_PAIR.count(&odd)**(paircnt-1)
  puts ans
  # carry case
  if len.odd?
    carry_cnt = (paircnt-1) / 2
    non_carry_cnt = (paircnt-1) - carry_cnt
    puts "#{carry_cnt} #{non_carry_cnt}"
    ans += NON_ZERO_CARRY_PAIR.count(&odd) * NON_CARRY_PAIR.count(&even)**non_carry_cnt * CARRY_PAIR.count(&odd)**carry_cnt
  end
  puts ans
end
puts ans
