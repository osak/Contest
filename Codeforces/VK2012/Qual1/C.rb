#!/usr/bin/env ruby

def normalize(path)
  norm = []
  path.split("/").each do |dir|
    if dir == ".."
      norm.pop
    else
      norm.push(dir)
    end
  end

  norm.join("/") + "/"
end

n = gets.to_i
pwd = "/"
regexp = /^cd (.*)/

n.times do 
  cmd = gets.chomp
  case cmd
  when "pwd"
    puts pwd
  else
    m = regexp.match(cmd)
    path = m[1]
    if path[0] == "/"
      pwd = normalize(path)
    else
      pwd = normalize(pwd + path)
    end
  end
end
