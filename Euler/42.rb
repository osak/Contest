#!/usr/bin/ruby

line = gets();
arr = line.split(',').map{|str| str.delete('"')}

maxlen = 0;
arr.each { |str|
	if str.length > maxlen then
		maxlen = str.length;
	end
}

p maxlen;
tri = Array.new(1,false);
n = 1;
while true do
	t = n*(n+1)/2;
	tri[t] = true;
	break if t > 26*maxlen;
	n += 1;
end

puts "end tri"
cnt = 0;
arr.each { |str|
	n = str.scan(/./).inject(0) { |res, c|
		res + c[0]-'A'[0]+1;
	}
	if tri[n] then
		cnt += 1;
	end
}

p cnt;
