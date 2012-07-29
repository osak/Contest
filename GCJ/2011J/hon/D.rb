#!/usr/bin/env ruby

$pat = [ ["CC","O."], [".O","CC"], ["OC", ".C"], ["C.", "CO"] ].freeze
DELTA = [ [0, 1], [0, -1], [1, 0], [-1, 0] ].freeze

def check(field)
	start = []
	catch(:next) {
		field.each_with_index do |row, r|
			row.each_with_index do |ch, c|
				if ch == 'D'
					start = [r, c]
					throw :next 
				end
			end
		end
	}

	tmp = field.map(&:dup)
	tmp[start[0]][start[1]] = 'X'
	q = [start]
	while q.size > 0
		cur = q.shift
		#tmp[cur[0]][cur[1]] = 'X'
		DELTA.each do |dl|
			nx = [cur[0] + dl[0], cur[1] + dl[1]]
			if (0...field.size).include?(nx[0]) && (0...field[0].size).include?(nx[1])
				if tmp[nx[0]][nx[1]] != 'X' && tmp[nx[0]][nx[1]] != 'C'
					tmp[nx[0]][nx[1]] = 'X'
					q << nx
				end
			end
		end
	end

	ok = true
	catch(:check) {
		tmp.each do |row|
			row.each do |ch|
				if ch == 'O'
					ok = false
					throw :check
				end
			end
		end
	}

	ok
end

def dfs(field, row, col, cnt)
	if row == field.size-1
		check(field) ? cnt : 0
	elsif col == field[0].size-1
		dfs(field, row+1, 0, cnt)
	else
		ans = 0
		$pat.each do |arr|
			bak = []
			2.times do |dr|
				2.times do |dc|
					bak << field[row+dr][col+dc]
				end
			end

			catch(:test) do
				2.times do |dr|
					2.times do |dc|
						c = field[row+dr][col+dc]
						if (arr[dr][dc] == 'C' && c != '.') || (arr[dr][dc] == 'O' && (c != 'O' && c != '.'))
							throw :test
						end
						field[row+dr][col+dc] = arr[dr][dc] if arr[dr][dc] != '.'
					end
				end
				#field.each { |a| puts a.join }
				#puts "-----"
				throw :test if !check(field)
				ans = [ans, dfs(field, row, col+1, cnt+1)].max
			end

			2.times do |dr|
				2.times do |dc|
					field[row+dr][col+dc] = bak.shift
				end
			end
		end
		[ans, dfs(field, row, col+1, cnt)].max
	end
end


gets.to_i.times do |case_num|
	h, w = gets.split.map(&:to_i)
	field = []
	h.times do
		field << gets.chomp.each_char.to_a
	end
	ans = dfs(field, 0, 0, 0)
	puts "Case ##{case_num}: #{ans}"
end
