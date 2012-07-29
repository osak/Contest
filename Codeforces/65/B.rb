n,k,t = gets.split.map(&:to_i)
all = n*k
val = (t*n*k/100.0).to_i
arr = [0] * n
n.times do |i|
	arr[i] = [k, val].min
	val = [val-k, 0].max
end
puts arr.join(' ')
