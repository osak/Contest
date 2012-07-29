#!/usr/bin/env ruby

s = gets
if s.match(/^[a-z][A-Z]*$/) || s.match(/^[A-Z]+$/)
  s.tr!('a-zA-Z', 'A-Za-z')
end
puts s
