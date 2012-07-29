#!/usr/bin/env ruby

def check(state, row)
  (0...row).each do |r|
    return false if state[r] == state[row]
    return false if r+state[r] == row+state[row]
    return false if r-state[r] == row-state[row]
  end
  true
end

def rec(state, row)
  if row == state.size
    throw :found, true
  elsif state[row]
    rec(state, row+1) if check(state, row)
  else
    8.times do |c|
      state[row] = c
      rec(state, row+1) if check(state, row)
    end
    state[row] = nil
  end
  false
end

valid = true
state = Array.new(8, nil)
8.times do |r|
  line = gets.chomp
  if line.count("Q") >= 2
    valid = false
  end

  q = line.index("Q")
  if q
    state[r] = q
  end
end

found = valid && catch(:found) {
  rec(state, 0)
}

if found
  state.each do |c|
    line = "."*8
    line[c] = "Q"
    puts line
  end
else
  puts "No Answer"
end
