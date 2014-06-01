#!/usr/bin/env ruby

require 'rational'

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

def node_count(words)
  res = 1
  root = {}
  words.each do |w|
    cur = root
    w.each_char do |c|
      if cur.has_key?(c)
        cur = cur[c]
      else
        res += 1
        cur = cur[c] = {}
      end
    end
  end
  res
end

solve do
  nstr, nsvr = gets.split.map(&:to_i)
  strs = nstr.times.map{gets.chomp}
  x, y = 0, 0
  (nsvr**nstr).times do |pat|
    words = Array.new(nsvr){Array.new}
    strs.each do |str|
      words[pat % nsvr] << str
      pat /= nsvr
    end
    next if words.any?{|ws| ws.empty? }
    cnt = words.reduce(0){|acc,ws| acc + node_count(ws)}
    if cnt > x
      x = cnt
      y = 1
    elsif cnt == x
      y += 1
      y %= 1000000007
    end
  end
  "#{x} #{y}"
end
