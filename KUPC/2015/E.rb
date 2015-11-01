gets.to_i.times do
  h, w = gets.chomp.split.map(&:to_f)
  h, w = w, h if h > w
  ans = [Math.hypot(w/2, h), w].min 
  10000.times do |i|
    cand = [Math.hypot(w, h/10000*i), Math.hypot(w/2, h/10000*(10000-i))].min
    ans = [ans, cand].max
  end
  puts ans
end
