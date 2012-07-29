#!/usr/bin/ruby

n, p = gets.split.map(&:to_i)
v = Array.new(n) { [nil, nil, nil] }
p.times do
	a, b, d = gets.split.map(&:to_i)
	a -= 1
	b -= 1
	v[a][1..2] = [b, d]
	v[b][0] = a
end

ans = []
v.each_with_index do |item, idx|
	if item[0].nil?
		cur = idx
		d = 10000000
		while v[cur][1]
			d = [d, v[cur][2]].min
			cur = v[cur][1]
		end
		ans << [idx+1, cur+1, d] if idx != cur
	end
end

p ans.size
ans.each do |item|
	puts item.join(' ')
end
