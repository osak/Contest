#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

def include?(r1, r2)
  r2.include?(r1[0]) and r2.include?(r1[1])
end

def intersect?(r1, r2)
  (not include?(r1, r2)) and ((r2[0] < r1[0] and r1[0] < r2[1]) or (r2[0] < r1[1] and r1[1] < r2[1]))
end

def generate_mounts(n, range)
  width = range[1] - range[0]
  mounts = Array.new(n){|i| width*i / (n-1) + (n-i-1)}
end

def generate(levels, target, range)
  #p levels
  indices = []
  levels.each_with_index do |level,idx|
    indices << idx if level == target
  end
  return nil if indices.empty?

  psuedo_last = false
  if levels[-1] != target
    indices << levels.size-1
    psuedo_last = true
  end

  res = []
  mounts = generate_mounts(indices.size, range)
  #p mounts
  (indices.size-1).times do |left|
    cur = indices[left]
    nx = indices[left+1]
    right_val = mounts[left+1]
    right_val -= 1 unless psuedo_last
    mid = generate(levels[cur+1..nx], target+1, [mounts[left], right_val])
    res << mounts[left]
    res.push(*mid)
  end
  res << mounts[-1] unless psuedo_last
  res
end

solve do
  n = gets.to_i
  peaks = gets.split.map(&:to_i).map{|i| i-1}

  catch(:impossible) do
    ranges = []
    levels = Array.new(n, 0)
    peaks.each_with_index do |peak,from|
      range = [from,peak]
      throw :impossible, "Impossible" if ranges.any?{|r| intersect?(r, range)}
      ranges << range

      (from+1..peak-1).each do |i|
        levels[i] += 1
      end
    end
    generate(levels, 0, [0, 100]).join(" ")
  end
end

