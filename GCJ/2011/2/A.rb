#!/usr/bin/ruby

1.upto(gets.to_i) do |cases|
    x,s,r,t,n = gets.chomp.split.map(&:to_i)
    ws = [] #[sx, ex, w]
    last = 0
    n.times do
        sx, ex, w = gets.chomp.split.map(&:to_i)
        ws << [last, sx, s] if last != sx
        ws << [sx, ex, w+s]
        last = ex
    end
    ws << [last, x, s] if last != x

    ans = 0
    ws.sort_by!{|a| a[2]}
    ws.each do |w|
        use = (w[1]-w[0]) / (w[2]+r-s).to_f
        if use > t
            run = (w[2]+r-s).to_f * t
            rem = w[1]-w[0]-run
            ans += t + rem/w[2].to_f
            t = 0
        else
            ans += use
            t -= use
        end
    end

    printf "Case #%d: %.8f\n", cases, ans
end
