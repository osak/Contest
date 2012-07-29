set isprime [list]
for {set i 0} {$i <= 10007} {incr i} {
	if {[expr $i%2] == 0} {
		lappend isprime 0
	} else {
		lappend isprime 1
	}
}
lset isprime 2 1
for {set i 3} {$i <= 10007} {set i [expr $i+2]} {
	if {[lindex $isprime $i] == 1} {
		for {set j [expr $i*$i]} {$j <= 10007} {set j [expr $j+$i]} {
			lset isprime $j 0
		}
	}
}

scan [gets stdin] {%d} n
for {set left $n} {[lindex $isprime $left] != 1} {set left [expr $left-1]} {}
for {set right $n} {[lindex $isprime $right] != 1} {incr right} {}
puts [format {%d %d} $left $right]
