#!/usr/bin/ruby

class Union
	def initialize(n)
		@roots = Array.new(n) { |i| i }
	end

	def getroot(n)
		root = @roots[n]
		if root == n
			root
		else
			@roots[n] = getroot(@roots[n])
		end
	end

	def unite(n, m)
		@roots[n] = getroot(@roots[m])
	end

	def roots
		@roots.map{ |i| getroot(i) }.sort.uniq
	end

	def count(n)
		@roots.count { |i| getroot(i) == n }
	end
end

cases = gets.to_i
1.upto(cases) do |num|
	n = gets.to_i
	arr = gets.chomp.split.map(&:to_i)
	union = Union.new(n+1)
	arr.each_with_index do |i,idx|
		union.unite(i, idx+1)
	end

	ans = 0
	union.roots.each do |r|
		next if r == 0
		cnt = union.count(r)
		ans += (cnt-1)*2
	end
	printf "Case ##{num}: %.6f\n", ans
end
