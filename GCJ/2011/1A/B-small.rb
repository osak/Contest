#!/usr/bin/ruby

class Dict
	def initialize(str)
		@str = str
		@mask = Array.new(26, 0)
		str.size.times do |i|
			c = str[i]
			idx = c.ord - 'a'.ord
			@mask[idx] |= 1 << i
		end
	end

	def has_pattern?(c, pat)
		@mask[c.ord - 'a'.ord] == pat
	end

	def pattern_of(c)
		@mask[c.ord - 'a'.ord]
	end

	def size
		@str.size
	end

	def to_s
		@str
	end
end

1.upto(gets.to_i) do |case_num|
	n, m = gets.split.map(&:to_i)
	dict = []
	n.times do
		dict << Dict.new(gets.chomp)
	end
	dict.freeze

	ans = []
	m.times do
		line = gets.chomp
		max = -1
		best = nil
		dict.each do |answer|
			candidate = dict.select { |d| d.size == answer.size }
			penalty = 0
			line.each_char do |guess|
				next unless candidate.any? { |d| d.pattern_of(guess) != 0 }
				pat = answer.pattern_of(guess)
				candidate.select! { |d| d.has_pattern?(guess, pat) }
				penalty += 1 if pat == 0
			end
			if penalty > max
				max = penalty
				best = answer
			end
		end
		ans << best
	end

	puts "Case ##{case_num}: #{ans.join(' ')}"
end
