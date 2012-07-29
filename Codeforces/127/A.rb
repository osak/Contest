#!/usr/bin/env ruby

xval = gets.to_i
n = 1
catch(:found) do
  loop do
    field = Array.new(n){Array.new(n, false)}
    cnt = 0
    (1..(n+1)/2).each do |y|
      neigh_y = n-y+1
      next if (y-neigh_y).abs == 1
      (1..(n+1)/2).each do |x|
        neigh_x = n-x+1
        next if (x-neigh_x).abs == 1
        next if (x-1 >= 1 && field[x-1-1][y-1]) || (y-1 >= 1 && field[x-1][y-1-1])

        tmp = nil
        if neigh_x != x && neigh_y != y
          tmp = 4
        elsif neigh_x == x && neigh_y == y
          tmp = 1
        else
          tmp = 2
        end
        #puts "#{x} #{y} #{tmp}" if n == 5
        if cnt+tmp == xval
          throw :found
        elsif cnt+tmp < xval
          cnt += tmp
          field[x-1][y-1] = true
        end
      end
    end
    n += 1
  end
end

p n
