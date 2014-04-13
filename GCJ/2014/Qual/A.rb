#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  a = gets.to_i
  candidates = nil
  4.times do |i|
    arr = gets.split.map(&:to_i)
    if i == a-1
      candidates = arr
    end
  end

  b = gets.to_i
  4.times do |i|
    arr = gets.split.map(&:to_i)
    if i == b-1
      candidates = candidates & arr
    end
  end

  if candidates.size == 1
    candidates.first
  elsif candidates.size == 0
    "Volunteer cheated!"
  else
    "Bad magician!"
  end
end
