#!/usr/bin/env ruby

perms = {}
File.open("perm.txt").each_line do |line|
  pos, perm = line.chomp.split
  perms[perm] = pos.to_i
end

field = 9.times.map{gets.chomp.gsub(/\s/, '')}
9.times do
  if field.all?{|s| perms.has_key?(s)}
    puts field.map{|s| perms[s]}
    break
  end
  field.map!{|r| r.chars.rotate.join('')}
end
