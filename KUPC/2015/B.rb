def upd(field, r, c)
  field[r][c] = 'X' if (0..9).include?(r) && (0..9).include?(c) && field[r][c] != 'C'
end

def calc(field)
  dp = Array.new(10, 1)
  10.times do |r|
    dp[r] = 0 if field[r][0] != '.'
  end
  (1...10).each do |c|
    ndp = Array.new(10, 0)
    10.times do |r|
      if field[r][c] == '.'
        ndp[r] = (r > 0 ? dp[r-1] : 0) + dp[r] + (r+1 < 10 ? dp[r+1] : 0)
      end
    end
    dp = ndp
  end
  dp.inject(&:+) == 1
end

loop do
  #field = $<.each_line.map(&:chomp).map(&:chars)
  field = Array.new(10){Array.new(10){'.'}}
  4.times do
    r = rand(10)
    c = rand(10)
    field[r][c] = 'C'
  end
  field.each_with_index do |row, r|
    row.each_with_index do |chr, c|
      if chr == 'C'
        upd(field, r-1, c+1)
        upd(field, r-1, c)
        upd(field, r-1, c-1)
        upd(field, r, c+1)
        upd(field, r, c-1)
        upd(field, r+1, c+1)
        upd(field, r+1, c)
        upd(field, r+1, c-1)
        upd(field, r-2, c+2)
        upd(field, r-2, c)
        upd(field, r-2, c-2)
        upd(field, r, c+2)
        upd(field, r, c-2)
        upd(field, r+2, c+2)
        upd(field, r+2, c)
        upd(field, r+2, c-2)
      end
    end
  end
  if calc(field)
    puts field.map(&:join)
    exit
  end
end
