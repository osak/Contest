#!/usr/bin/env ruby

class Queen
    attr_reader :r, :c
    attr_accessor :cnt

    def initialize(r, c)
        @r = r
        @c = c
        @cnt = 0
    end
end

def cnt(queens)
=begin
    queens.each_with_index do |q, i|
        if i > 0
            q.cnt += 1 if yield(q, queens[i-1])
        end
        if i+1 < queens.size
            q.cnt += 1 if yield(q, queens[i+1])
        end
    end
=end
    queens.each_with_index do |q,i|
        if i > 0
            flg = yield(q, queens[i-1])
            if flg
                q.cnt += 1
                queens[i-1].cnt += 1
            end
        end
    end
end


n, m = gets.split.map(&:to_i)
queens = []
m.times do
    r, c = gets.split.map(&:to_i)
    queens << Queen.new(r, c)
end

queens.sort!{ |a,b| (a.r != b.r) ? a.r<=>b.r : a.c<=>b.c }
cnt(queens) { |a,b| a.r == b.r }
queens.sort!{ |a,b| (a.c != b.c) ? a.c<=>b.c : a.r<=>b.r }
cnt(queens) { |a,b| a.c == b.c }
queens.sort!{ |a,b| (a.r+a.c != b.r+b.c) ? (a.r+a.c)<=>(b.r+b.c) : a.r<=>b.r } 
cnt(queens) { |a,b| a.r+a.c == b.r+b.c }
queens.sort!{ |a,b| (a.r-a.c != b.r-b.c) ? (a.r-a.c)<=>(b.r-b.c) : a.r<=>b.r }
cnt(queens) { |a,b| a.r-a.c == b.r-b.c }

res = [0]*9
queens.each do |q|
    res[q.cnt] += 1
end
puts res.join(' ')
