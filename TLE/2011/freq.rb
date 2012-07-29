#!/usr/bin/ruby

src = $<.read
hash = {}
hash.default = 0
src.each_char { |c|
    hash[c] += 1
}
freq = {}
hash.each_pair { |c,v|
    freq[v] ||= []
    freq[v] << c
}

freq.keys.sort.each { |v|
    puts "#{v}: #{freq[v].join(' ')}"
}
