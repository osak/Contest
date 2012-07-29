#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  n = gets.to_i
  vines = []
  n.times do
    vines << gets.split.map(&:to_i)
  end
  d = gets.to_i

  most_far_from = Array.new(n) {|i| i}

