#!/usr/bin/env ruby

# ダイクストラ法で探索する。

require_relative 'pq'

class Tag
  include Comparable

  attr_reader :row, :col, :cost
  def initialize(row, col, cost)
    @row = row
    @col = col
    @cost = cost
  end

  def pos
    [row, col]
  end

  def <=>(other)
    other.cost <=> cost # Reversed order
  end
end

matrix = $<.each_line.to_a.map{|line| line.split(/,/).map(&:to_i)}
INF = matrix.flatten.inject(&:+)
GOAL = [matrix.size-1, matrix[0].size-1].freeze

memo = Hash.new{|h,k| h[k] = INF}
pq = PriorityQueue.new
pq << Tag.new(0, 0, matrix[0][0])
memo[pq.peek.pos] = pq.peek.cost
while not pq.empty?
  cur = pq.pop
  break if cur.pos == GOAL
  next if memo[cur.pos] < cur.cost
  [[0, 1], [1, 0], [0, -1], [-1, 0]].each do |dr, dc|
    npos = [cur.pos[0] + dr, cur.pos[1] + dc]
    next if not ((0...matrix.size).include?(npos[0]) and (0...matrix[0].size).include?(npos[1]))
    ncost = cur.cost + matrix[npos[0]][npos[1]]
    next if memo[npos] <= ncost
    memo[npos] = ncost
    pq << Tag.new(npos[0], npos[1], ncost)
  end
end

puts cur.cost
