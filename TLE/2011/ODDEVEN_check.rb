#!/usr/bin/ruby

src = gets
odd = ''
even = ''
src.length.times {|i|
    odd += src[i] if i.odd?
    even += src[i] if i.even?
}
puts odd
puts even
