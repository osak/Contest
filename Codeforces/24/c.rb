#!/usr/bin/ruby

n, j = gets.split.map(&:to_i)
as = Array.new

ix,iy = gets.split.map(&:to_i)
sum_x = 0
sum_y = 0
n.times { |i|
	sum_x *= -1
	sum_y *= -1

	x,y = gets.split.map(&:to_i)
	sum_x += 2*x
	sum_y += 2*y

	as << [x, y]
}
loopcnt = j / n
mod = j % n
coef_x = sum_x * loopcnt
coef_y = sum_y * loopcnt

mod.times { |i|
	coef_x *= -1
	coef_y *= -1
	coef_x += 2*as[i][0]
	coef_y += 2*as[i][1]
}

flg = (j&1) ? -1 : 1
puts "#{ix*flg + coef_x} #{iy*flg + coef_y}"
