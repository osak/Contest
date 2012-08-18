#!/usr/bin/env ruby

class TimeSpan
  attr_reader :range
  attr_accessor :used
  def initialize(starttime, endtime)
    sh, sm = starttime.split(/:/).map(&:to_i)
    eh, em = endtime.split(/:/).map(&:to_i)
    @range = Range.new(sh*60+sm, eh*60+em-1)
    @used = false
  end

  def overwrap?(other)
    (-1..1).each do |d|
      delta = d*24*60
      if other.range.include?(range.begin+delta) || other.range.include?(range.end+delta)
        return true
      end
    end
    false
  end
end

n = gets.to_i

spans = []
n.times do 
  ts, te = gets.chomp.split
  spans << TimeSpan.new(ts, te)
end
spans.sort!{|a,b| a.range.begin <=> b.range.begin}

cnt = 0
spans.each do |span|
  next if span.used
  set = [span]
  span.used = true
  cnt += 1
  spans.each do |other|
    next if other.used
    if set.all?{|s| !s.overwrap?(other) && !other.overwrap?(s)}
      set << other
      other.used = true
    end
  end
end

p cnt 
