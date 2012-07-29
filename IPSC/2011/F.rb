#!/usr/bin/ruby

def check(pat)
	cnt = 0
	8.times do |i|
		arr = []
		arr[0] = i & 1
		arr[1] = (i>>1)&1
		arr[2] = (i>>2)&1
		guess = []
		guess[0] = pat[0][arr[1]*2+arr[2]]
		guess[1] = pat[1][arr[0]*2+arr[2]]
		guess[2] = pat[2][arr[0]*2+arr[1]]
		succ = 0
		3.times do |i|
			if guess[i] != "P"
				if "HT".index(guess[i]) == arr[i]
					succ += 1
				else
					succ = -100
				end
			end
		end
		if succ > 0
			cnt += 1
		end
	end
	cnt / 8.0
end

(3**12).times do |i|
	num = i
	pat = ["HHHH","HHHH","HHHH"]
	3.times do |row|
		4.times do |col|
			idx = num % 3
			pat[row][col] = "HTP"[idx]
			num /= 3
		end
	end

	prob = check(pat)
	if prob > 0.5
		p [pat, prob]
	end
end
