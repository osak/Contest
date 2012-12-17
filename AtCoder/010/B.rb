#!/usr/bin/ruby

DAYS = [0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31].freeze

n = gets.to_i
holidays = []
n.times do
  holidays << gets.split('/').map(&:to_i)
end
holidays.sort!

day = 0
date = [1, 1]
rem = 0
acc = 0
ans = 0
loop do
  holiday = (day == 0 || day == 6)
  if !holiday && rem > 0
    holiday = true
    rem -= 1
  end

  if holidays.include?(date)
    if holiday
      rem += 1
    end
    holiday = true
  end

  if holiday
    acc += 1
    ans = [ans, acc].max
  else
    acc = 0
  end

  break if date == [12, 31]

  day += 1
  day %= 7
  date[1] += 1
  if date[1] > DAYS[date[0]]
    date = [date[0]+1, 1]
  end
end

puts ans
