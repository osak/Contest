#!/usr/bin/ruby

a = (2..30000).to_a

primes = []

while !a.empty?
    n = a.shift
    a = a.select { |i| i % n != 0 }
    primes << n
end

str = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
ARGV[0].scan(/./).each { |c|
    k = (rand()*((primes.size-1) / 52)).to_i
    idx = str.index(c)
    if idx == nil
        puts '4'
    else
        puts primes[k*52+idx]
    end
}
puts -1
