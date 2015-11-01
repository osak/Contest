#!/usr/bin/ruby

def all_permutation(arr)
	ans = arr.sort.dup;
	tmp = Array.new;

	while true do
		tmp.clear;
		tmp.push(ans.last);
		pos = ans.size - 2;
		while pos >= 0 do
			break if tmp.last >= ans[pos];
			tmp.push(ans[pos]).sort!;
			pos -= 1;
		end
		if pos == -1 then
			break;
		end
		tmp.each_index { |i|
			if tmp[i] >= ans[pos] then
				t = ans[pos];
				ans[pos] = tmp[i];
				tmp[i] = t;
				break;
			end
		}
		tmp.sort!;
		ans[pos+1..-1] = tmp;
		yield ans.dup;
	end
end

digits = [1,2,3,4,5,6,7,8,9];
8.times {
	digits.pop;
	next if digits.inject(0){|r,i| r+i} % 3 == 0;
	all_permutation(digits) { |numstr|
		num = numstr.join('').to_i;
		root = Math.sqrt(num);
		ok = true;
		for i in 2..root do
			if num % i == 0 then
				ok = false;
				break;
			end
		end
		if ok then
			p num;
		end
	}
}
