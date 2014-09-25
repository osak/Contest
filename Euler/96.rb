#!/usr/bin/env ruby

# Naiive sieving

require 'set'

def enum_candidate(field)
  res = {}
  9.times do |r|
    9.times do |c|
      if field[r][c] == 0
        cand = (1..9).to_a
        # reject by row
        cand.reject!{|a| field[r].index(a)}
        # reject by col
        cand.reject!{|a| field.any?{|row| row[c] == a}}
        # reject by grid
        base_r = r / 3 * 3
        base_c = c / 3 * 3
        cand.reject!{|a| (0..8).any?{|h| field[base_r+h/3][base_c+h%3] == a}}
        res[[r,c]] = cand
      end
    end
  end
  res
end

def solved?(field)
  field.flatten.all?{|a| a != 0}
end

def solve(field)
  return true if solved?(field)
  cand = enum_candidate(field)
  cell = cand.min_by{|k,v| v.size}
  return false if cell.nil?
  cell[1].each do |d|
    field[cell[0][0]][cell[0][1]] = d
    if solve(field)
      return true
    end
  end
  field[cell[0][0]][cell[0][1]] = 0
  false
end

ans = 0
while s = gets
  if !s.match(/Grid (\d+)/)
    break
  end
  puts "Grid #{$1}"

  field = 9.times.map{gets.chomp.chars.map(&:to_i)}
  solve(field)
  puts field.map(&:join)
  ans += field[0][0]*100 + field[0][1]*10 + field[0][2]
end

puts ans
