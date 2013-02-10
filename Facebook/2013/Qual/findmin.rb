#!/usr/bin/ruby

def solve
  gets.to_i.times do |i|
    res = yield
    puts "Case ##{i+1}: #{res}"
  end
end

class Heap
  def initialize
    @buf = [nil]
  end

  def push(val)
    @buf << val
    pos = @buf.size - 1
    while pos != 1 && @buf[pos/2] > @buf[pos]
      @buf[pos/2], @buf[pos] = @buf[pos], @buf[pos/2]
      pos /= 2
    end
  end
  alias :<< :push

  def pop
    res = @buf[1]
    @buf[1] = @buf.pop
    pos = 1
    loop do
      left = pos*2
      right = left+1
      min_one = right
      min_one = left if @buf[min_one].nil? || @buf[left] < @buf[min_one]
      if @buf[min_one] && @buf[pos] > @buf[min_one]
        @buf[pos],@buf[min_one] = @buf[min_one],@buf[pos]
        pos = min_one
      else
        break
      end
    end
    res
  end
end

solve do
  n, k = gets.split.map(&:to_i)
  a, b, c, r = gets.split.map(&:to_i)
  arr = [a]
  (k-1).times do |i|
    arr << (b*arr[i]+c) % r
  end

  in_arr = {}
  arr.each do |val|
    in_arr[val] ||= 0
    in_arr[val] += 1
  end
  
  heap = Heap.new
  (0..k).each do |i|
      heap << i if not in_arr.has_key?(i)
  end

  head = []
  arr.each do |val|
    min = heap.pop
    head << min
    in_arr[min] ||= 0
    in_arr[min] += 1
    in_arr[val] -= 1
    if (0..k).include?(val) && in_arr[val] == 0
      heap << val
    end
  end
  head << heap.pop
  #p arr
  #p head
  head[(n-k-1) % (k+1)]
end
