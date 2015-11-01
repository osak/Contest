#!/usr/bin/ruby

arr = gets.chomp.split(',').map{|n| n.to_i}

for key in 'aaa'..'zzz' do
	str = '';
	idx = 0;
	sum = 0;
	wordlen = 0;
	valid = true;
	arr.each { |b|
		ch = b^key[idx]
		if ch == 0x20 then
			wordlen = 0;
		else
			wordlen += 1;
			if wordlen > 15 then
				valid = false;
				break;
			end
		end

		str << ch.chr;
		sum += ch;
		idx = (idx+1) % 3;
	}

	next if !valid;
	puts str + "(#{sum})";

end

