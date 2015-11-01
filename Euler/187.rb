#!/usr/bin/env ruby

require 'prime'

PRIMES = Prime.each(1_0000_0000).to_a
puts PRIMES.size
