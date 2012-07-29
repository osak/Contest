#!/usr/bin/ruby

cases = gets.to_i
1.upto(cases) do |num|
	arr = gets.chomp.split
	c = arr[0].to_i
	cl, arr = arr[1,c], arr[(1+c)..-1]
	d = arr[0].to_i
	dl, arr = arr[1,d], arr[(1+d)..-1]
	n = arr[0].to_i
	str = arr[1]

	combine = {}
	oppose = []
	cl.each do |cstr|
		combine[cstr[0,2].each_char.sort.join] = cstr[2]
	end
	dl.each do |dstr|
		oppose << (1<<(dstr[0].ord-'A'.ord)) + (1<<(dstr[1].ord-'A'.ord))
	end

	list = []
	mask = 0
	str.each_char do |elem|
		cb = nil
		cb = [list[-1],elem].sort.join if list.size > 0
		if combine[cb]
			last = list.pop
			mask &= ~(1<<(last.ord-'A'.ord)) unless list.index(last)
			list << combine[cb]
		else
			mask |= (1<<(elem.ord-'A'.ord))
			if oppose.any?{|i| (mask&i) == i}
				list = []
				mask = 0
			else
				list << elem
			end
		end
	end
	puts "Case ##{num}: [#{list.join(', ')}]"
end
