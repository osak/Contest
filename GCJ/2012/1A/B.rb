#!/usr/bin/env ruby

def solve
  gets.to_i.times do |casenum|
    res = yield
    puts "Case ##{casenum+1}: #{res}"
  end
end

solve do
  n = gets.to_i
  levels = []
  n.times do
    levels << gets.split.map(&:to_i)
  end

  rating = Array.new(n, 0)
  clearcnt = 0
  stars = 0
  step = 0
  loop do
    target = nil
    targetrank = -1
    targetlevel = -1
    rating.each_with_index do |r, i|
      next if r == 2
      if levels[i][1] <= stars
        target = i
        targetrank = 2
        targetlevel = levels[i][1]
        break
      elsif r == 0 and levels[i][0] <= stars and targetrank < 2
        if targetlevel < levels[i][1]
          target = i
          targetrank = 1
          targetlevel = levels[i][1]
        end
      end
    end

    #puts "#{stars} #{target} #{targetrank}"
    if target.nil?
      step = "Too Bad"
      break
    end
    stars += targetrank - rating[target]
    rating[target] = targetrank
    step += 1
    if targetrank == 2
      clearcnt += 1
      break if clearcnt == n
    end
  end

  step
end
