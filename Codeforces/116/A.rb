#!/usr/bin/ruby

# move sects[cur] to correct position using temporary
# return tmpidx
def move(sects, target, cur, tmp, acc)
  return tmp if sects[cur] == target[cur]
  return tmp if cur == tmp
  return tmp if sects[cur].nil?

  to = target.index(sects[cur])
  acc << [to, tmp] if to != tmp
  sects[tmp] = sects[to]

  acc << [cur, to]
  sects[to] = sects[cur]
  move(sects, target, tmp, cur, acc)
end

n, m = gets.split.map(&:to_i)
sects = Array.new(n, nil)
len = 0
target = []
m.times do |i|
  k, *as = gets.split.map(&:to_i)
  as.map{|v| v-1}.each_with_index do |a, j|
    sects[a] = [i,j]
    target << [i,j]
  end
  len = [len, as.max].max
end
target.freeze

tmpidx = sects.index(nil)

ans = []
cur = 0
while cur < len
  if cur != tmpidx and sects[cur] and sects[cur] != target[cur]
    tmpidx = move(sects, target, cur, tmpidx, ans)
  end
  cur += 1
end

puts ans.size
ans.each do |v|
  puts v.map{|a| a+1}.join(' ')
end
