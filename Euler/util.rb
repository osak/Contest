def infinite_num(start=0)
	n = start;
	while true do
		yield n;
		n += 1;
	end
end

def infinite_odd
	n = 3;
	while true do
		yield n;
		n += 2;
	end
end

def limit_odd(lim)
	n = 3;
	while n < lim do
		yield n;
		n += 2;
	end
end

def prime_list(lim)
	primes = Array.new;
	primes.push(2);

	limit_odd(lim) { |n|
		root = Math.sqrt(n);
		ok = true;
		primes.each { |p|
			break if p > root;
			if n % p == 0 then
				ok = false;
				break;
			end
		}
		if ok then
			primes.push(n);
		end
	}

	return primes.dup;
end

def infinite_prime
	primes = Array.new;
	primes.push(2);

	infinite_odd { |n|
		root = Math.sqrt(n);
		ok = true;
		primes.each { |p|
			break if p > root;
			if n % p == 0 then
				ok = false;
				break;
			end
		}
		if ok then
			primes.push(n);
			yield n;
		end
	}
end

