#!/usr/bin/env ruby

# 素数の平方、立方、4乗をすべて列挙し、組み合わせをすべて試す。

require 'prime'
require 'set'

LIMIT = 50_000_000

squares = []
cubes = []
fourths = []
Prime.each do |pr|
  square = pr*pr
  cube = square*pr
  fourth = cube*pr
  if square > LIMIT
    break
  end

  squares << square
  cubes << cube if cube < LIMIT
  fourths << fourth if fourth < LIMIT
end

puts squares.size, cubes.size, fourths.size
list = Set.new
squares.each do |sq|
  cubes.each do |cube|
    fourths.each do |fourth|
      sum = sq + cube + fourth
      list << sum if sum < LIMIT
    end
  end
end

puts list.size
