#!/usr/bin/env ruby

gets.to_i.times do
  r, c, d = gets.split.map(&:to_i)
  height, width = r, c

  field = Array.new(r){Array.new(c, 0)}
  step = 1
  loop do
    break if height.zero? or width.zero?
    if height > width
      width.times do |col|
        [height,d].min.times do |row|
          field[r+row][c+col] = step
        end
      end
      diff = [width, d].min
      height -= diff
      r += diff
    else
      height.times do |row|
        [width,d].min.times do |col|
          field[r+row][c+col] = step
        end
      end
      diff = [height, d].min
      width -= diff
      c -= diff
    end

    step += 1
  end

  puts field.map{|col| col.join(' ')}
end
