#!/usr/bin/env ruby

ANSWER = %w(
3776
fibonacci
unique_ptr
26
algeria
479
1440
7
1688
kruskal
)
n = gets.to_i - 1
raise if n >= ANSWER.size
puts ANSWER[n]
