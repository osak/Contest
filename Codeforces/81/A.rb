#!/usr/bin/env ruby

arr = gets.split
n, m, k = arr[0].to_i, arr[1].to_i, arr[2].to_f

skills = {}
n.times do
    sk = gets.split
    exp = (sk[1].to_i * k).to_i
    skills[sk[0]] = exp if exp >= 100
end

m.times do
    sk = gets.chomp
    if !skills.has_key?(sk)
        skills[sk] = 0
    end
end

p skills.size
skills.keys.sort.each do |key|
    puts "#{key} #{skills[key]}"
end
