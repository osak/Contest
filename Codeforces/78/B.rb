def check(a, b, n)
	diff = b[0]-a[0]
	if diff.odd? || (a[0]+b[0])/2 != n
		puts "Unrecoverable configuration."
		exit
	end
	puts "#{(diff)/2} ml. from cup ##{a[1]} to cup ##{b[1]}."
	exit
end

n = gets.to_i
arr = Array.new(n) { |idx| [gets.to_i, idx+1] }.sort.freeze

if arr[0][0] == arr[-1][0]
	puts "Exemplary pages."
	exit
end

if arr.size == 2
	diff = arr[1][0]-arr[0][0]
	if diff.odd?
		puts "Unrecoverable configuration."
		exit
	end
	check(arr[0], arr[1], (arr[0][0]+arr[1][0])/2)
end

if arr[1][0] != arr[-2][0]
	puts "Unrecoverable configuration."
	exit
end

check(arr[0], arr[-1], arr[1][0])
