class Card
	def initialize(card)
		@card = card
	end

	def suit
		@card[1]
	end

	def number
		@card[0]
	end

	def joker?
		@card == "J1" || @card == "J2"
	end

	def to_s
		@card
	end

	def ==(other)
		self.number == other.number && self.suit == other.suit
	end
end

def check(arr, row, col)
	return false if row < 0 || col < 0 || row+3 > arr.size || col+3 > arr[0].size

	numbers = []
	suits = []
	3.times do |r|
		3.times do |c|
			return false if arr[row+r][col+c].joker?
			numbers << arr[row+r][col+c].number
			suits << arr[row+r][col+c].suit
		end
	end

	numbers.uniq.size == 9 || suits.uniq.size == 1
end

def wrap(rect1, rect2)
	(rect1[0]-rect2[0]).abs < 3 && (rect1[1]-rect2[1]).abs < 3
end

cards = []
"A23456789TJQK".each_char do |num|
	"CDHS".each_char do |suit|
		cards << Card.new(num + suit)
	end
end

n,m = gets.split.map(&:to_i)
arr = []
joker = []
n.times do |row|
	a = gets.split.map{|cd| Card.new(cd)}
	a.each_with_index do |card,col|
		if card.number == "J" && (card.suit == "1" || card.suit == "2")
			joker << [row, col, card.suit]
		else
			cards.delete(card)
		end
	end
	arr << a
end

rects = []
(0..n-3).each do |row|
	(0..m-3).each do |col|
		rects << [row, col] if check(arr, row, col)
	end
end

ans = nil
rects.combination(2) do |cb|
	if !wrap(cb[0], cb[1])
		ans = cb
		joker.each_with_index do |jk,idx|
			arr[jk[0]][jk[1]] = cards[idx]
		end
		break
	end
end

if !ans && joker.size > 0
	catch(:check_loop) {
		cards.combination(joker.size).each do |cb|
			cb.permutation do |perm|
				joker.each_with_index do |jk,idx|
					arr[jk[0]][jk[1]] = perm[idx]
				end
				nr = []
				joker.each_with_index do |jk|
					(-2..0).each do |dr|
						row = jk[0]+dr
						(-2..0).each do |dc|
							col = jk[1]+dc
							if check(arr, row, col)
								nr << [row, col]
							end
						end
					end
				end
				(nr+rects).each do |r1|
					nr.each do |r2|
						if !wrap(r1, r2)
							ans = [r1, r2]
							throw :check_loop
						end
					end
				end
			end
		end
	}
end

if !ans
	puts "No solution."
else
	puts "Solution exists."
	joker.sort_by!{|a| a[2]}
	if joker.size == 0
		puts "There are no jokers."
	elsif joker.size == 1
		puts "Replace J#{joker[0][2]} with #{arr[joker[0][0]][joker[0][1]]}."
	else
		puts "Replace J1 with #{arr[joker[0][0]][joker[0][1]]} and J2 with #{arr[joker[1][0]][joker[1][1]]}."
	end
	puts "Put the first square to (#{ans[0][0]+1}, #{ans[0][1]+1})."
	puts "Put the second square to (#{ans[1][0]+1}, #{ans[1][1]+1})."
end
