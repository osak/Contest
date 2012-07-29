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

	def check
		@field.each do |line|
			return false if line.index('.')
		end
		return true
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

	ok = false
	catch(:challenge) {
		p1 = [rr-1, rc-1]
		p2 = [r-br, c-bc]
		pos = [p1, p2].min_by(&:first)
		dest = pos == p1 ? p2 : p1

		q = []
		while pos[0] < dest[0]
			pos[0] += 1
			break if field.get(pos[0], pos[1]) == 'B'
			field.color(pos[0], pos[1], 'R')
			q << pos
		end

		step = pos[1] < dest[1] ? 1 : -1
		while pos[1] != dest[1]
			pos[1] += step
			throw :challenge if field.get(pos[0], pos[1]) == 'B'
			field.color(pos[0], pos[1], 'R')
			q << pos
		end

		while pos[0] < dest[0]
			pos[0] += 1
			throw :challenge if field.get(pos[0], pos[1]) == 'B'
			field.color(pos[0], pos[1], 'R')
			q << pos
		end

		while !q.empty?
			delta = [[0,1], [1,0], [0,-1], [-1,0]]
			pos = q.shift
			delta.each do |dl|
				np = pos.dup
				np[0] += dl[0]
				np[1] += dl[1]
				next unless (0...r).include?(np[0]) && (0...c).include?(np[1])
				if field.get(np[0], np[1]) == '.'
					field.color(np[0], np[1], 'R')
					q << np
				end
			end
		end

		ok = true
	}

	puts if cases > 0
	if r*c % 2 == 0 && ok && field.check
		puts field
	else
		puts "IMPOSSIBLE"
	end
end

