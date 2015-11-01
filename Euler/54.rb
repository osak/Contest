#!/usr/bin/ruby

#カードは強さ->番号に変換。
#2が0番で以降Aceの12番まで。

def check_hand(hand)
	flush = true;
	straight = -1;
	cnt = Array.new(13,0);

	#Check flush and count nums
	flushsuit = hand[0][1];
	hand.each { |card|
		if card[1] != flushsuit then
			flush = false;
		end
		cnt[card[0]] += 1;
	}

	#Check straight
	straight = hand[4][0];
	4.times { |i|
		if hand[i][0] != hand[i+1][0]-1 then
			straight = -1;
			break;
		end
	}

	if flush then
		if straight == 12 then
			#Royal Flush
			return 13*9;
		elsif straight != -1 then
			#Straight Flush
			return 13*8;
		end
	end

	#Check Ncards
	pair1 = pair2 = three = four = -1;
	cnt.each_with_index { |c,idx|
		case c
		when 2:
			if pair1 == -1 then
				pair1 = idx;
			else 
				pair2 = idx;
			end
		when 3:
			three = idx;
		when 4:
			four = idx;
		end
	}
	if four != -1 then
		#Four card
		hand.delete_if { |card|
			card[0] == four;
		}
		return 13*7 + four;
	end
	if pair1 != -1 && three != -1 then
		#Full House
		hand.delete_if { |card|
			card[0] == three;
		}
		return 13*6+three;
	end
	if flush then
		return 13*5 + hand[4][0];
	end
	if straight != -1 then
		return 13*4 + straight;
	end
	if three != -1 then
		hand.delete_if { |card|
			card[0] == three;
		}
		return 13*3 + three;
	end
	if pair1 != -1 && pair2 != -1 then
		hand.delete_if { |card|
			card[0] == pair2;
		}
		return 13*2 + pair2;
	end
	if pair1 != -1 then
		hand.delete_if { |card|
			card[0] == pair1;
		}
		return 13*1 + pair1;
	end
	return hand[4][0];
end

cnt = 0;
while gets() do
	arr = $_.split;
	num = '23456789TJQKA';
	arr.map! { |card|
		[(num.index(card[0]))%13, card[1].chr]
	}
	hand1 = arr[0,5].sort;
	hand2 = arr[5,5].sort;

	score1 = check_hand(hand1);
	score2 = check_hand(hand2);

	if score1 == score2 then
		p hand1
		p hand2
		hand1.reverse!;
		hand2.reverse!;
		hand1.size.times { |i|
			next if hand1[i][0] == hand2[i][0];
			if hand1[i][0] > hand2[i][0] then
				score1 += 1;
			end
			break;
		}
	end

	cnt += 1 if score1 > score2;
end
p cnt;
