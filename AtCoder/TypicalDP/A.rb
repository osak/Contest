#!/usr/bin/env ruby

# Name: コンテスト
# Level: 2
# Category: DP,動的計画法
# Note: Typical DP Contest A

# 先頭から順に点数をなめていき、その時点で可能な合計点をSetで持ち回す。
# オーダーはO(N^2 P)。
# ただし P = max p_i。

require 'set'

n = gets.to_i
ps = gets.split.map(&:to_i)
dp = Set.new
dp << 0

ps.each do |pi|
  nx = Set.new
  dp.each do |cur|
    nx << cur
    nx << cur+pi
  end
  dp = nx
end

puts dp.size
