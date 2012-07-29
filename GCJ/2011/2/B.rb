#!/usr/bin/ruby

def eqv(a, b)
	(a-b).abs < 1e-10
end

1.upto(gets.to_i) do |cases|
	r, c, d = gets.split.map(&:to_i)
	ws = []
	r.times { ws << gets.chomp.scan(/./).map{|c| c.to_i+d} }
	ans = nil
	3.upto([r,c].min) do |size|
		#p size
		(0..r-size).each do |sr|
			(0..c-size).each do |sc|
				g = [0,0]
				hsum = 0
				size.times do |r|
					size.times do |c|
						rflg = r==0 || r==size-1
						cflg = c==0 || c==size-1
						next if rflg && cflg

						g[0] += (r+0.5) * ws[sr+r][sc+c]
						g[1] += (c+0.5) * ws[sr+r][sc+c]
						hsum += ws[sr+r][sc+c]
					end
				end
				g[0] /= (hsum).to_f
				g[1] /= (hsum).to_f
				#p g
				if eqv(g[0], size/2.0) && eqv(g[1], size/2.0)
					ans = size
					#p [sr, sc]
				end
			end
		end
	end

	puts "Case ##{cases}: #{ans || 'IMPOSSIBLE'}"
end

