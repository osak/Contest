#!/usr/bin/ruby

def winning(list, target)
  str = ""
  list.keys.sort.reverse.each do |key|
    str << key*list[key]
  end
  str > target
end

def minstr(list)
  arr = []
  list.each_pair do |key,val|
    arr += [key]*val
  end
  arr.sort.join
end

def search(cur, max, list, target)
  substr = target[cur+1..-1] || ''
  tc = target[cur] || ''

  #puts "#{cur} #{list}"
  
  if list[tc] > 0
    list[tc] -= 1
    if winning(list, substr)
      res = search(cur+1, max, list, target)
      if res
        return tc+res
      end
    end
    list[tc] += 1
  end

  # find next char
  nc = list.keys.sort.find{|k| k>tc and list[k]>0}
  if nc
    list[nc] -= 1
    return nc+minstr(list)
  end
  
  nil
end

s = gets.chomp
t = gets.chomp

list = Hash.new(0)
s.each_char do |c|
  list[c] += 1
end

ans = search(0, s.size, list, t)
if ans.nil?
  ans = -1
end
puts ans
