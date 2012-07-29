#!/usr/bin/env ruby

n = gets.to_i
list = {}
n.times do
  str = gets.chomp
  if str =~ /\((.*)\)/
    order = 10**($1.size)
    a = Rational($` + "0")
    b = Rational($` + $1) * order
    n = (b-a) / (order-1)
    list[n] = true
  else
    a = Rational(str)
    list[a] = true
  end
end

puts list.size
