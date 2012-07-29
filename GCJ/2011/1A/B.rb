#!/usr/bin/ruby

class Dict
	attr_reader :idx

	def initialize(str, idx)
		@str = str
		@idx = idx
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

class Cluster
	attr_accessor :penalty

	def initialize(penalty)
		@arr = []
		@penalty = penalty
	end

	def push(elem)
		@arr << elem
	end

	def reconstruct(c)
		tmp = Array.new(1024)
		new_arr = []
		@arr.each do |dict|
			pat = dict.pattern_of(c)
			if !tmp[pat]
				tmp[pat] = Cluster.new(@penalty + (pat == 0 ? 1 : 0))
				new_arr << tmp[pat]
			end
			tmp[pat].push(dict)
		end
		new_arr[0].penalty = @penalty if new_arr.size == 1
		new_arr
	end

	def first
		@arr.min_by { |e| e.idx }
	end

	def size
		@arr.size
	end

end

1.upto(gets.to_i) do |case_num|
	n, m = gets.split.map(&:to_i)
	dict = []
	n.times do |n|
		dict << Dict.new(gets.chomp, n)
	end
	dict.freeze

	ans = []
	m.times do |m_cnt|
		print "\n",m_cnt
		line = gets.chomp
		best = nil
		best_penalty = -1
		1.upto(10) do |dict_size|
			clusters = [Cluster.new(0)]
			dict.select{ |d| d.size == dict_size }.each do |d|
				clusters[0].push(d)
			end

			res = []
			line.each_char do |guess|
				print guess
				next_clusters = []
				clusters.each do |cl|
					next_clusters += cl.reconstruct(guess)
				end
				clusters, drop = next_clusters.partition { |cl| cl.size > 1 }
				res += drop
			end
			#print clusters.size, ' '

			res.each do |cl|
				#puts "#{cl.first} #{cl.penalty}"
				if cl.penalty > best_penalty
					best = cl.first
					best_penalty = cl.penalty
				elsif cl.penalty == best_penalty
					best = [best, cl.first].min_by(&:idx)
				end
			end
		end

		ans << best
	end

	puts "Case ##{case_num}: #{ans.join(' ')}"
end
