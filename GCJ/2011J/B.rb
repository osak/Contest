#!/usr/bin/env ruby

require './pq'

class Tag
    attr_accessor :time, :idx, :event

    include Comparable

    EVENT_ENDOF = 0
    EVENT_EXHAUST = 1
    EVENT_LAST = 2

    def initialize(t, i, e)
        @time = t
        @idx = i
        @event = e
    end

    def <=>(other)
        @time <=> other.time
    end
end

gets.to_i.times do |cases|
    n, k = gets.split.map(&:to_i)
    coffees = []
    coffees << {:rem => k, :end => k, :sat => 0}
    n.times do
        c, t, s = gets.split.map(&:to_i)
        coffees << {:rem => c, :end => t, :sat => s}
    end

    q = PriorityQueue.new
    coffees.each_with_index do |c,i|
        q << Tag.new(c[:end], i, Tag::EVENT_ENDOF)
    end
    q << Tag.new(0, 0, Tag::EVENT_LAST)

    ans = 0
    prev = k
    curidx = 0
    while q.size > 0
        tag = q.pop
        idx = tag.idx
        ans += coffees[curidx][:sat] * (prev - tag.time)
        coffees[curidx][:rem] -= (prev - tag.time)

        case tag.event
        when Tag::EVENT_ENDOF
            if coffees[curidx][:sat] < coffees[idx][:sat]
                curidx = idx
                q << Tag.new(curidx, tag.time - coffees[curidx][:rem], Tag::EVENT_EXHAUST)
            end
        when Tag::EVENT_EXHAUST
            curidx = 0
            coffees.each_with_index do |c, i|
                next if c[:rem] == 0
                next if c[:end] < tag.time

                if coffees[curidx][:sat] < c[:sat]
                    curidx = i
                end
            end
        when Tag::EVENT_LAST
            break
        end
    end

    puts "Case ##{cases+1}: #{ans}"
end
