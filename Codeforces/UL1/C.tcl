scan [gets stdin] {%d %d %d} n m k
puts [expr $m*(($k+$n-1)%$n) + (($k-1)/$n) + 1]
