#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

keys = [
  ["ejp mysljylc kd kxveddknmc re jsicpdrysi", "our language is impossible to understand"],
  ["rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd", "there are twenty six factorial possibilities"],
  ["de kr kd eoya kw aej tysr re ujdr lkgc jv", "so it is okay if you want to just give up"]
]

mapping = {"y" => "a", "e" => "o", "q" => "z"}
keys.each do |dat|
  dat[0].each_char.to_a.zip(dat[1].each_char.to_a) do |from, to|
    if mapping.has_key?(from)
      STDERR.puts("ERROR: #{from}->#{mapping[from]}, #{to}") if mapping[from] != to
    end
    mapping[from] = to
  end
end

rem_from = ("a".."z").to_a - mapping.keys
rem_to = ("a".."z").to_a - mapping.values
mapping[rem_from.first] = rem_to.first

solve do
  gets.chomp.gsub(/./){|c| mapping[c]}
end
