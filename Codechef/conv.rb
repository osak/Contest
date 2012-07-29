#!/usr/bin/ruby

puts ARGF.read.split.map(&:to_i).pack("V*").gsub(/\\/){"\\\\"}.gsub(/'/){"\\'"}
