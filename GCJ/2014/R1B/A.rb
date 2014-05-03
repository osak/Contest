#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  n = gets.to_i
  strs = n.times.map{gets.chomp}
  squeezed = strs.map(&:squeeze)
  if squeezed.all?{|s| s == squeezed[0]}
    chunk_str = strs.map { |s|
      acc = []
      prev = ""
      s.each_char do |c|
        if c == prev
          acc.last[1] += 1
        else
          acc << [c, 1]
        end
        prev = c
      end
      acc
    }
    res = 0
    chunk_str[0].size.times do |i|
      best_cost = Float::INFINITY
      (1..100).each do |len|
        cost = 0
        chunk_str.each do |chunks|
          cost += (chunks[i][1] - len).abs
        end
        if cost < best_cost
          best_cost = cost
        end
      end
      res += best_cost
    end
    res
  else
    "Fegla Won"
  end
end
