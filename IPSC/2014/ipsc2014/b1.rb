#!/usr/bin/env ruby

class Random
  M = 2**32
  def initialize(init)
    @x = init.dup
    @cy = 0
  end

  def rand
    val = @x[-22] - @x[-43] - @cy
    @cy = val < 0 ? 1 : 0
    val = (val + M) % M
    @x << val
    val
  end
end

def move(field)
  size = field.size
  nums = field.select{|x| x > 0}
  new_field = []
  merged = false
  nums.each do |x|
    if new_field[-1] == x && !merged
      new_field[-1] *= 2
      merged = true
    else
      merged = false
      new_field << x
    end
  end
  new_field += [0]*(size - new_field.size)
  raise if field.size != new_field.size
  [new_field, new_field != field]
end

gets.to_i.times do
  gets
  len = gets.to_i
  field = gets.split.map(&:to_i)
  init = gets.split.map(&:to_i)
  rng = Random.new(init)
  moves = gets.to_i

  gets.chomp.each_char do |c|
    case c
    when "l"
      field, moved = move(field)
    when "r"
      field, moved = move(field.reverse)
      field.reverse!
    end
    #puts field.join(' '), moved
    if moved
      num_empty = field.count{|x| x == 0}
      pos = rng.rand % num_empty
      if rng.rand % 10 == 0
        new_val = 4
      else
        new_val = 2
      end
      field.each_with_index do |v, i|
        if v == 0
          if pos == 0
            field[i] = new_val
            break
          end
          pos -= 1
        end
      end
    end
  end
  puts field.join(' ')
end
