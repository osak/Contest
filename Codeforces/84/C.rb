#!/usr/bin/ruby

class Array
    def sum
        self.inject(&:+)
    end
end

n = gets.to_i
dp = Array.new(n+1, nil)
dp[0] = [0, 0]
tmp = [1, 1]
1.upto(n) do |i|
    if dp[i-4]
        #a = dp[i-4].dup
        a = tmp
        a[0] += 1
        if dp[i].nil?
            dp[i] = a
        else
            dp[i] = a if dp[i].sum > a.sum || (dp[i].sum == a.sum && dp[i][0] < a[0])
        end
    end

    if dp[i-7]
        #a = dp[i-7].dup
        a = tmp
        a[1] += 1
        if dp[i].nil?
            dp[i] = a
        else
            dp[i] = a if dp[i].sum > a.sum || (dp[i].sum == a.sum && dp[i][0] < a[0])
        end
    end
end

if dp[n]
    buf = ''
    buf << '4'*dp[n][0]
    buf << '7'*dp[n][1]
    puts buf
else
    puts -1
end
