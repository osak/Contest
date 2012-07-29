#!/usr/bin/ruby

$memo = {}
def rec(n, rem)
  return 1 if rem == 0
  if n == 0
    return 1 if rem == 0
    return 0
  end

  key = [n,rem]
  val = $memo.fetch(key, nil)
  return val if val

  res = 0
  (0..9).each do |d|
    break if d > rem
    res += rec(n-1, rem-d)
  end
  $memo[[n,rem]] = res
end

p rec(9, 50)
