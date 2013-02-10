#!/usr/bin/ruby

require 'set'

def solve
  gets.to_i.times do |i|
    res = yield
    puts "Case ##{i+1}: #{res}"
  end
end

solve do
  str = gets.chomp
  dict = Set[0]
  str.each_char.each_with_index do |c, idx|
    case c
    when "("
      # Treat as open
      next_dict = Set.new(dict){|key| key+1}
      if idx > 0 && str[idx-1] == ":"
        # Treat as smily
        next_dict.merge(dict)
      end
      dict = next_dict
    when ")"
      # Treat as close
      next_dict = Set.new(dict){|key| key-1}
      next_dict.reject!{|key| key < 0}
      if idx > 0 && str[idx-1] == ":"
        # Treat as frowny
        next_dict.merge(dict)
      end
      dict = next_dict
    end
  end
  dict.include?(0) ? "YES" : "NO"
end
