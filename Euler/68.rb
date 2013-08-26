#!/usr/bin/env ruby

# 和を求める箇所はハードコーディングし、DFSでマスを埋めていく。
# それぞれのラインで和が確定したときに整合性がとれているかで枝刈りを行う。

SEQS = [
  [0, 1, 2],
  [3, 2, 4],
  [5, 4, 6],
  [7, 6, 8],
  [9, 8, 1]
].map(&:freeze).freeze

CHECK_POINT = {
  2 => 0,
  4 => 1,
  6 => 2,
  8 => 3,
  9 => 4
}.freeze

def to_magic_str(arr)
  start_value = SEQS.map{|a| arr[a[0]]}.min
  start_index = SEQS.map{|a| arr[a[0]]}.index(start_value)
  SEQS.rotate(start_index).flatten.map{|i| arr[i]}.join
end

def calc(arr, line)
  sum = 0
  SEQS[line].each do |i|
    sum += arr[i]
  end
  sum
end

def dfs(pos=0, sum=0, acc=Array.new(10), used={})
  if pos == 10
    str = to_magic_str(acc)
    return str.length == 16 ? str : nil
  end

  ans = nil
  (1..10).each do |i|
    next if used.has_key?(i)
    acc[pos] = i
    if line = CHECK_POINT[pos]
      if line == 0
        sum = calc(acc, line)
      else
        if calc(acc, line) != sum
          next
        end
      end
    end

    # valid
    used[i] = true
    if res = dfs(pos+1, sum, acc, used)
      if ans.nil? or res > ans
        ans = res
      end
    end
    used.delete(i)
  end
  ans
end

puts dfs
