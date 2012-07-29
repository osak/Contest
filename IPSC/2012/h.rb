#!/usr/bin/env ruby

gets.to_i.times do
  gets
  height, width, d = gets.split.map(&:to_i)
  r = c = 0

  field = Array.new(height){Array.new(width, 0)}

  step = 1
  loop do
    break if height.zero? or width.zero?
    if height > width
      width.times do |col|
        [height,d].min.times do |row|
          field[r+row][c+col] = step
        end
        step += 1
      end
      diff = [height, d].min
      height -= diff
      r += diff
    else
      height.times do |row|
        [width,d].min.times do |col|
          field[r+row][c+col] = step
        end
        step += 1
      end
      diff = [width, d].min
      width -= diff
      c += diff
    end
  end

  puts field.map{|col| col.join(' ')}
  puts ""
end
