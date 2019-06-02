#!/usr/bin/env ruby

require 'rational'

Molecule = Struct.new(:a, :b)
INFINITY = 1.0 / 0.0

t = gets.to_i
(1..t).each do |cn|
  n = gets.to_i
  break if n >= 10

  mols = []
  n.times do
    a, b = gets.split.map(&:to_i)
    mols << Molecule.new(a, b)
  end

  ans = 0
  mols.permutation do |perm|
    range = [0, INFINITY]
    (1...n).each do |i|
      mol1 = perm[i-1]
      mol2 = perm[i]
      if mol1.b == mol2.b
        range = [INFINITY, 0] if mol1.a >= mol2.a
        next
      end

      ratio = (mol1.a - mol2.a).to_r / (mol2.b - mol1.b)
      if mol2.b > mol1.b
        range[0] = [ratio, range[0]].max
      else
        range[1] = [ratio, range[1]].min
      end
    end
    #puts "#{perm.join(' ')}: #{range.join(' ')}"
    if range[0] < range[1]
      ans += 1
    end
  end
  puts "Case ##{cn}: #{ans}"
end
