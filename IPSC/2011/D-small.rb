#!/usr/bin/ruby

class String
	def oppose
		self == 'R' ? 'B' : 'R'
	end
end


class Field
	def initialize(r, c)
		@field = Array.new(r) { "." * c }
	end

	def height
		@field.size
	end

	def width
		@field[0].size
	end

	def color(r, c, cl)
		@field[r][c] = cl
		@field[height-r-1][width-c-1] = cl.oppose
	end

	def get(r, c)
		@field[r][c].freeze
	end

	def to_s
		@field.join("\n")
	end

end

gets.to_i.times do |cases|
	gets
	r,c = gets.split.map(&:to_i)
	field = Field.new(r, c)

	rr,rc = gets.split.map(&:to_i)
	field.color(rr-1, rc-1, 'R')
	br,bc = gets.split.map(&:to_i)
	field.color(br-1, bc-1, 'B')

	r.times do |row|
		c.times do |col|
			if field.get(row,col) == '.'
				field.color(row, col, 'R')
			end
		end
	end

	puts if cases > 0
	if r*c % 2 == 0
		puts field
	else
		puts "IMPOSSIBLE"
	end
end

