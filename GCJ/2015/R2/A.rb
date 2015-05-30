#!/usr/bin/env ruby

DR = [0, 1, 0, -1].freeze
DC = [1, 0, -1, 0].freeze
DIR_MAP = {
  '>' => 0,
  'v' => 1,
  '<' => 2,
  '^' => 3
}.freeze

def impossible?(field)
  field.size.times do |r|
    field[0].size.times do |c|
      next if field[r][c] == '.'
      found = catch(:found) {
        4.times do |dir|
          cur_r, cur_c = r + DR[dir], c + DC[dir]
          while (0...field.size).include?(cur_r) && (0...field[0].size).include?(cur_c)
            if field[cur_r][cur_c] != '.'
              throw :found, true
            end
            cur_r += DR[dir]
            cur_c += DC[dir]
          end
        end
        false
      }
      return true if !found
    end
  end
  false
end

def solve
  r, c = gets.split.map(&:to_i)
  field = r.times.map{gets}.map(&:chomp)
  if impossible?(field)
    "IMPOSSIBLE"
  else
    ans = 0
    field.size.times do |r|
      field[0].size.times do |c|
        next if field[r][c] == '.'
        dir = DIR_MAP[field[r][c]]
        cur_r, cur_c = r + DR[dir], c + DC[dir]
        found = false
        while (0...field.size).include?(cur_r) && (0...field[0].size).include?(cur_c)
          if field[cur_r][cur_c] != '.'
            found = true
            break
          end
          cur_r += DR[dir]
          cur_c += DC[dir]
        end
        if !found
          ans += 1
        end
      end
    end
    ans
  end
end

t = gets.to_i
t.times do |c|
  puts "Case ##{c+1}: #{solve}"
end

