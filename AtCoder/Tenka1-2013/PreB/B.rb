#!/usr/bin/env ruby

q, l = gets.split.map(&:to_i)
stack = []
size = 0
queries = []
q.times do
  queries << gets.chomp
end

state = "SAFE"
queries.each do |query|
  case query
  when /^Push/
    _, n, m = query.split.map(&:to_i)
    stack << {val: m, count: n}
    size += n
    if size > l
      state = "FULL"
      break
    end
  when /^Pop/
    _, n = query.split.map(&:to_i)
    size -= n
    while !stack.empty?
      topcnt = stack[-1][:count]
      cnt = [n, topcnt].min
      topcnt -= cnt
      n -= cnt
      if topcnt == 0
        stack.pop
      else
        stack[-1][:count] = topcnt
        break
      end
    end
    if stack.empty? && n > 0
      state = "EMPTY"
      break
    end
  when "Top"
    if stack.empty?
      state = "EMPTY"
      break
    end
    puts stack[-1][:val]
  when "Size"
    puts size
  end
end

puts state
