#!/usr/bin/env ruby

class Point
	attr_reader :x, :y

	def initialize(x, y)
		@x = x
		@y = y
	end

	def +(pt)
		@x += pt.x
		@y += pt.y
		self
	end

	def *(coef)
		@x *= coef
		@y *= coef
		self
	end
end

width, height = gets.split.map(&:to_i)
field = []
symbol = []
height.times do
	arr = gets.split.map(&:to_i)
	field << arr
end
height.times do
	arr = gets.split.map(&:to_i)
	symbol << arr
end
er, ec = gets.split.map(&:to_i)
er -= 1
ec -= 1

DELTA = [Point.new(0, -1), Point.new(1, 0), Point.new(0, 1), Point.new(-1, 0)]
queue = []
queue << [Point.new(ec, er), field[er][ec], symbol[er][ec]]
symbol[er][ec] = -1
ans = 0
while queue.size > 0
	sym = queue.first
	queue.shift
	p sym

	dir = 0
	step = 1
	cnt = 0
	pos = sym[0]
	target = sym[1]
	to = sym[2]

	while (0...width).include?(pos.x) && (0...height).include?(pos.y)
		if field[pos.y][pos.x] == target && target != to
			field[pos.y][pos.x] = to
			ans += 1
		end
		if symbol[pos.y][pos.x] != -1
			queue << [pos.dup, field[pos.y][pos.x], symbol[pos.y][pos.x]]
			symbol[pos.y][pos.x] = -1
		end
		pos += DELTA[dir]
		cnt += 1
		if cnt % step == 0
			dir = (dir+1) % 4
			if cnt == step*2
				step += 1
				cnt = 0
			end
		end
	end
	p ans
end
p ans
