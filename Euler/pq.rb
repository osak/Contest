class PriorityQueue

  def initialize(size=0)
    @arr = Array.new(size+1)
  end

  def push(obj)
    @arr << obj
    pos = @arr.size-1
    while pos > 1
      parent = pos >> 1
      if @arr[parent] < @arr[pos]
        @arr[pos], @arr[parent] = @arr[parent], @arr[pos]
        pos = parent
      else
        break
      end
    end
  end

  alias << push

  def pop
    ret = @arr[1]
    last = @arr.pop
    if @arr.size > 1
      @arr[1] = last
      pos = 1
      loop do
        left = (pos << 1)
        right = (pos << 1) + 1
        to_swap = nil
        if @arr.size > left && @arr[left] > @arr[pos]
          to_swap = left
        end
        if @arr.size > right && @arr[right] > @arr[pos]
          to_swap = right if to_swap.nil? || @arr[to_swap] < @arr[right]
        end

        if to_swap
          @arr[pos], @arr[to_swap] = @arr[to_swap], @arr[pos]
          pos = to_swap
        else
          break
        end
      end
    end

    ret
  end

  def peek
    @arr[1]
  end

  def size
    @arr.size-1
  end

  def empty?
    size == 0
  end
end

if __FILE__ == $0
  pq = PriorityQueue.new

  1000.times do
    pq << (rand * 1000).to_i
  end

  prev = 10000
  while pq.size > 0
    top = pq.pop
    puts "#{prev} #{top}" if top > prev
    prev = top
  end
end

