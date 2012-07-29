arr = Array.new(1001)
arr[0] = arr[1] = 0
arr[2] = 1

(3..1000).each do |i|
    arr[i] = arr[i-3]+arr[i-2]+arr[i-1]
end

puts arr
