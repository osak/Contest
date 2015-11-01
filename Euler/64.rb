#!/usr/bin/ruby

def findgcd(a, b)
	#Euclidの互除法でG.C.D.を見つける
	return findgcd(b, a) if a < b;

	while b != 0 do
		rem = a % b;
		a = b;
		b = rem;
	end

	return a;
end


cnt = 0;
(1..10000).each do |num|
	p num if num % 1000 == 0;
	rootf = Math.sqrt(num);
	root = Math.sqrt(num).to_i;
	next if root**2 == num;

	hash = Hash.new;

	#分数の形式：[実数部, 根号の係数]
	#さいしょ
	denom = [-root, 1]
	numer = [1, 0];

	period = 0;
	while true do
		#有理化
		#まず分母を有理化した値を出す
		denom_temp = (num*(denom[1]**2)) - (denom[0]**2);

		#次に分子と約分する
		gcd = findgcd(denom_temp, numer[0]);
		numer[0] /= gcd;
		denom_temp /= gcd;
		
		#最後に、分子に掛ける
		numer = [numer[0]*(-denom[0]), numer[0]*denom[1]];
		denom = [denom_temp, 0];
		#p numer,denom 

		#単位分数化
		#分子の実数部が初めて負になるまで分母を引きつづける
		#************************************
		#********ここ何か勘違いしてる********
		#************************************
		#↑0<分子<分母になるまで、だね
		#root <= sqrt(num) < root+1
		#numer[0] -= (numer[0]%denom[0]+1) * denom[0];
		numer[0] -= denom[0] while rootf*numer[1]+numer[0] > denom[0];
		#p numer,denom

		#この時点でのnumer, denomをハッシュに入れる
		key = numer + denom;

		#もしも既に来ていたら繰りかえした事になる
		break if hash.has_key?(key);
		hash[key] = true;
		period += 1;

		#逆数をとる
		tmp = numer;
		numer = denom;
		denom = tmp;
	end
	cnt += 1 if period % 2 == 1;
end

p cnt;
