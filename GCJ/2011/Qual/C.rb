#!/usr/bin/ruby

cases = gets.to_i
1.upto(cases) do |num|
	t = gets.to_i
	cs = gets.split.map(&:to_i)
	sum_bit = cs.inject(&:^)
    sum = cs.inject(&:+)
	ans = "NO"
	if sum_bit == 0
        tbl = Array.new(2) { Array.new(1<<20) {0} }
        cs.each do |c|
            tbl[0].each_with_index do |val,bit|
                new_bit = bit^c
                new_val = val+c
                tbl[1][new_bit] = [tbl[1][new_bit], tbl[0][bit]+c].max
            end
            tbl[0],tbl[1] = tbl[1],tbl[0]
        end
        1.upto(t-1) do |i|
            ans = [ans, tbl[i]].max
        end
	end
	puts "Case ##{num}: #{ans}"
end
