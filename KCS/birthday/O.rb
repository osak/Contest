#!/usr/bin/env ruby

require 'prime'

n, m = gets.split.map(&:to_i)
puts gets.split.map(&:to_i).count{|x| (x+m).prime?}
