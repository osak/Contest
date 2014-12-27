# Name: Little Pony and Sort by Shift
# Level: 2
# Category: Greedy
# Note:

# The array is sortable if and only if there is at most one index such that a[i-1] > a[i].
# If such index exists, a[i] must be the first element in sorted array, otherwise the array is 
# obviously not sorted.

def decpt(arr)
  res = nil
  (1...arr.size).each do |i|
    if arr[i] < arr[i-1]
      return nil if res
      res = i-1
    end
  end
  res
end

n = gets.to_i
arr = gets.split.map(&:to_i)
if arr.uniq.size == 1
  puts 0
else
  decpt = nil
  arr.size.times do |i|
    if arr[i] < arr[i-1]
      if decpt
        puts -1
        exit
      end
      decpt = i
    end
  end
  if decpt
    puts (arr.size - decpt) % arr.size
  else
    puts 0
  end
end
