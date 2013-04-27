#!/usr/bin/env ruby

require 'set'

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

tbl = {}
(2..5).to_a.map{|v| [v]*3}.flatten.combination(3).to_a.uniq.each do |comb|
  s = Set.new
  (0..comb.size).each do |n|
    comb.combination(n).each do |sel|
      s << sel.reduce(1, &:*)
    end
  end
  tbl[s] = comb.join
end

solve do
  r, n, m, k = gets.split.map(&:to_i)
  res = ['']
  r.times do
    prods = Set.new(gets.split.map(&:to_i))
    cand = [1,1,1]
    tbl.each_pair do |key, val|
      #puts "#{key.inspect} #{prods.inspect}"
      if prods.subset?(key)
        cand = val
        break
      end
    end
    res << cand
  end
  res.join("\n")
end
