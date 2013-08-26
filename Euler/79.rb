#!/usr/bin/env ruby

# 先頭、中央、末尾の文字種から適当に並びを手動で推測する。

KEYLOG = File.read("keylog.txt").each_line.map(&:chomp).to_a.uniq
puts KEYLOG.size
puts KEYLOG
CHARS = KEYLOG.flatten.join.chars.uniq.sort.join
TOP = KEYLOG.map{|a| a[0]}.uniq.sort.join
MID = KEYLOG.map{|a| a[1]}.uniq.sort.join
LAST = KEYLOG.map{|a| a[2]}.uniq.sort.join

puts TOP, MID, LAST

