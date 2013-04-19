#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

def check_row(field, player)
  field.each do |row|
    won = true
    row.each do |ch|
      if ch != "T" and ch != player
        won = false
        break
      end
    end
    return true if won
  end
  false
end

def check(field, player)
  return true if check_row(field, player)
  return true if check_row(field.transpose, player)
  # Check diagonal
  won = true
  field.each_with_index do |row, ri|
    if row[ri] != "T" and row[ri] != player
      won = false
      break
    end
  end
  return true if won
  won = true
  field.each_with_index do |row, ri|
    if row[3-ri] != "T" and row[3-ri] != player
      won = false
      break
    end
  end
  won
end

def completed?(field)
  field.flatten.all?{|ch| ch != '.'}
end

solve do
  field = []
  4.times do
    field << gets.chomp.each_char.to_a
  end
  gets

  if check(field, "O")
    "O won"
  elsif check(field, "X")
    "X won"
  elsif completed?(field)
    "Draw"
  else
    "Game has not completed"
  end
end
