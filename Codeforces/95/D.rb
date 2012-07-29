#!/usr/bin/env ruby

n = gets.to_i
roads = Array.new(n) { [] }
n.times do
    r = gets.split.map(&:to_i)
    r[0] -= 1
    r[1] -= 1
    roads[r[0]] << r[1]
    roads[r[1]] << r[0]
end

eliminated = [false]*n
loop {
    flag = false
    roads.each_with_index do |r, idx|
        next if eliminated[idx]
        cnt = 0
        r.each do |i|
            cnt += 1 if !eliminated[i]
        end
        if cnt == 1
            eliminated[idx] = true
            flag = true
        end
    end
    break if !flag
}
lp = []
eliminated.each_with_index do |e, i|
    lp << i if !e
end

res = [nil]*n
q = []
lp.each do |i|
    q << [i, 0]
end
while q.size > 0
    cur = q.shift
    next if res[cur[0]]

    res[cur[0]] = cur[1]
    roads[cur[0]].each do |nx|
        q << [nx, cur[1]+1] unless res[nx]
    end
end

puts res.join(' ')
