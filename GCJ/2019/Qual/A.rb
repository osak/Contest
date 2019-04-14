#!/usr/bin/env ruby

t = gets.to_i
(1..t).each do |cn|
  n = gets.chomp
  if n =~ /^10+$/
    a = n.to_i - 1
    b = 1
  else
    n_digits = n.to_s.chars.map(&:to_i)
    a_digits = []
    b_digits = []

    n_digits.each do |d|
      if d == 0
        a_digits << d
	b_digits << 0
      elsif d == 5
	a_digits << d-2
	b_digits << 2
      else
	a_digits << d-1
	b_digits << 1
      end
    end

    a = a_digits.join.to_i
    b = b_digits.join.to_i
  end
  puts "Case ##{cn}: #{a} #{b}"
end
