#!/usr/bin/ruby

n = gets.to_i

ret = "BigInteger"
ret = "long" if n <= 9223372036854775807
ret = "int" if n <= 2147483647
ret = "short" if n <= 32767
ret = "byte" if n <= 127
puts ret
