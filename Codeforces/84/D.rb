#!/usr/bin/ruby

lucky_numbers = []
1.upto(9) do |digits|
	(2**digits).times do |i|
		n = 0
		digits.times do |bit|
			n *= 10
			if i[bit] == 0
				n += 4
			else
				n += 7
			end
		end
		lucky_numbers << n
	end
end

lucky_numbers.sort!

pl, pr, vl, vr, k = gets.split.map(&:to_i)

arra = lucky_numbers.select { |n| (pl..pr).include?(n) }.sort
arra.unshift(pl) if arra[0] != pl
arra << pr if arra[-1] != pr

arrb = lucky_numbers.select { |n| (vl..vr).include?(n) }.sort
arrb.unshift(vl) if arrb[0] != vl
arrb << vr if arrb[-1] != vr

cnt = 0
a_clip = 0
b_clip = 0
arra.each_with_index do |a, aidx|
	next_a_clip = 0
	b_clip = 0
	arrb.each_with_index do |b, bidx|
		range = Range.new(*([a, b].sort))
		next if lucky_numbers.count { |n| range.include?(n) } != k

		mina = [aidx > 0 ? arra[aidx-1]+1 : a, a_clip].max
		maxa = aidx+1 < arra.size ? arra[aidx+1]-1 : a
		minb = [bidx > 0 ? arrb[bidx-1]+1 : b, b_clip].max
		maxb = bidx+1 < arrb.size ? arrb[bidx+1]-1 : b

		puts "#{a} #{b} #{mina} #{maxa} #{minb} #{maxb}"
		if range.begin == a || !lucky_numbers.index(a)
			cnt += (a-mina+1)*(maxb-b+1)
		end
		if range.begin == b || !lucky_numbers.index(b)
			cnt += (maxa-a+1)*(b-minb+1)
		end

		next_a_clip = maxa+1
		b_clip = maxb+1
	end
	a_clip = next_a_clip
end

printf "%.10f\n", (cnt.to_f / ((pr-pl+1)*(vr-vl+1)))

