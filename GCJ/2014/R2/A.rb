#!/usr/bin/env ruby

require 'rational'

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  n, x = gets.split.map(&:to_i)
  files = Hash.new
  gets.split.map(&:to_i).each do |s|
    files[s] ||= 0
    files[s] += 1
  end

  discs = 0
  (1..x).reverse_each do |lim|
    files.keys.each do |s|
      while files[s] > 0
        opp = lim - s
        files[s] -= 1
        if files[opp] && files[opp] > 0
          discs += 1
          files[opp] -= 1
        else
          files[s] += 1
          break
        end
      end
    end
  end
  files.each_pair do |k,s|
    if s > 0
      discs += s
    end
  end
  discs
end
