#!/usr/bin/ruby

$facts = Array.new(17) { |i| (1..i).inject(&:*) }
$facts[0] = 1

def create_arr(n, depth, max)
	return [n] if depth == max
	this = n / $facts[max-depth] 
	[this] + create_arr(n % $facts[max-depth], depth+1, max)
end

n, y, m = gets.split.map(&:to_i)
v = []
m.times do
	a = gets.split.map(&:to_i)
	v << a.dup
end

ok = true
ans = []

if $facts[n] <= y-2001
	ok = false
else
	arr = create_arr(y-2001, 1, n)
	profs = (1..n).to_a
	arr.each do |idx|
		ans << profs[idx]
		profs.delete_at(idx)
	end
	p ans

	v.each do |cont|
		ok = false if ans[cont[0]-1] > ans[cont[1]-1]
	end
end

if ok
	puts ans.join(' ')
else
	puts "The times have changed"
end
