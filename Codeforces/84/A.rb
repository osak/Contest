#!/usr/bin/ruby

n = gets
cnt = n.count('47')
if cnt.to_s.gsub(/[47]/, '') == ''
    puts 'YES'
else
    puts 'NO'
end
