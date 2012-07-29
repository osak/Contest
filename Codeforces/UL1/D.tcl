scan [gets stdin] {%d %d %d} a1 a2 a3
set lst [list [list $a1 0] [list $a2 1] [list $a3 2]]
set ans {0 0 0}
set l [lsort -decreasing -integer -index 0 $lst]
for {set i 0} {$i < 3} {incr i} {
	lset ans [lindex [lindex $l $i] 1] [expr $i+1]
}
puts [join $ans " "]
