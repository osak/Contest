#!/usr/bin/env ruby

require 'prime'

class D
  def solve_part(arr, acc)
    size = arr.size
    Prime.each do |n| # every n-th elements
      break if n > size/2
      next if size % n != 0

      tmp = Array.new
      n.times do |start|
        

  def solve(arr)
    size = arr.size
    @ans = Array.new(size){[]} # @ans[i][j] = score of regular i-polygon starts from j
    solve_part(arr, 1)
    @ans.max
  end
end

n = gets.to_i
arr = gets.split.map(&:to_i)
