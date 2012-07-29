#!/usr/bin/ruby

require 'set'

1.upto(gets.to_i) do |cases|
    pl, w = gets.split.map(&:to_i)
    v = Array.new(pl) { Array.new(pl, false) }
    gets.chomp.split.each do |s|
        a,b = s.split(',').map(&:to_i)
        v[a][b] = v[b][a] = true
    end

    threat = Array.new(pl, nil)
    pl.times do |i|
        threat[i] = v[i].count { |a| a } - (i == 0 ? 1 : 2) if i != 1
    end

    cache = Array.new(pl, 0)
    mincost = nil
    ans = 0
    q = []
    q << [0, 0, Set[0], Set[*(1..pl).to_a.select { |i| v[0][i] }]]
    while !q.empty?
        tag = q.shift

        next if cache[tag[1]] > tag[3].size
        cache[tag[1]] = tag[3].size
        break if mincost && tag[0] > mincost
        if tag[1] == 1
            mincost = tag[0]
            #p [tag[3], tag[2]]
            cnt = tag[3].size
            ans = [ans, cnt].max
        elsif mincost
            next
        end

        pl.times do |i|
            next if tag[2].include?(i)
            if v[tag[1]][i]
                new_set = tag[3].dup
                (1..pl).each do |j|
                    new_set << j if i != j && v[i][j] && !tag[2].include?(j)
                end
                new_set.delete(i)
                next if cache[i] > new_set.size
                q << [tag[0]+1, i, tag[2]+Set[i], new_set]
            end
        end
    end

    puts "Case ##{cases}: #{mincost-1} #{ans+1}"
end

