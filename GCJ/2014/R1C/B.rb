#!/usr/bin/env ruby

require 'set'

MOD = 1000000007

class DisjointSet
  def initialize(n)
    @roots = Array.new(n){|i| i}
  end

  def root(k)
    return k if @roots[k] == k
    @roots[k] = root(@roots[k])
  end

  def unite(i, j)
    ri = root(i)
    rj = root(j)
    if ri == rj
      return false
    end
    @roots[rj] = ri
    true
  end
end

def perm(n)
  return 1 if n == 0
  (1..n).inject(&:*)
end

def detect_loop(next_of, cur)
  visited = {}
  while cur
    return true if visited[cur]
    visited[cur] = true
    cur = next_of[cur]
  end
  false
end

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  n = gets.to_i
  cars = gets.chomp.split.map(&:squeeze)
  if cars.any?{|s| s.chars.uniq != s.chars}
    0
  else
    chunk_by_head = {}
    chunk_by_last = {}
    middle_cnt = {}
    singleton_cnt = {}
    cars.each do |s|
      if s[0] == s[-1]
        singleton_cnt[s[0]] ||= 0
        singleton_cnt[s[0]] += 1
      else
        chunk_by_head[s[0]] ||= []
        chunk_by_head[s[0]] << s
        chunk_by_last[s[-1]] ||= []
        chunk_by_last[s[-1]] << s
      end
      s.chars[1..(s.length-2)].uniq.each do |c|
        middle_cnt[c] ||= 0
        middle_cnt[c] += 1
      end
    end
    ok = true
    next_of = {}
    group_of = DisjointSet.new(26)
    pattern_of = {}
    ('a'..'z').each_with_index do |c, i|
      h = chunk_by_head[c] || []
      l = chunk_by_last[c] || []
      s = singleton_cnt[c] || 0
      m = middle_cnt[c] || 0
      if h.size >= 2 || l.size >= 2
        ok = false
      end
      if m >= 2
        ok = false
      end
      if m >= 1 && (h.size > 0 || l.size > 0 || s > 0)
        ok = false
      end
      #if h.size > 0 && l.size > 0
      #  ok = false
      #end
      if h.size > 0
        #puts c
        next_of[i] = h.first[-1].ord - 'a'.ord
      end
      pattern_of[i] = perm(s)
    end
    #puts next_of
    #puts pattern_of.map(&:to_s).join(' ')
    if !ok || (0..25).any?{|i| detect_loop(next_of, i)}
      0
    else
      loop do
        changed = false
        26.times do |i|
          ri = group_of.root(i)
          if ri.nil? || next_of[ri].nil?
            next
          end
          gn = group_of.root(next_of[ri])
          if ri == gn
            # merged
            next
          end
          #puts "merge #{ri} #{gn}"
          pattern_of[ri] *= pattern_of[gn]
          next_of[ri] = next_of[gn]
          group_of.unite(ri, gn)
          changed = true
        end
        if !changed
          break
        end
      end
      res = 1
      chunks = 0
      s = Set.new(cars.map{|s| s[0] + s[-1]}.join.chars)
      26.times do |i|
        if s.include?((i+'a'.ord).chr) && group_of.root(i) == i
          res *= pattern_of[i]
          #puts i
          chunks += 1
        end
      end
      res * perm(chunks) % MOD
    end
  end
end
