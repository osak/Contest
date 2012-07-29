proc cmp {a b} {
	set ascore [lindex $a 1]
	set bscore [lindex $b 1]
	if {$ascore != $bscore} {
		return [expr $ascore - $bscore]
	} else {
		return [string compare [lindex $b 0] [lindex $a 0]]
	}
}

gets stdin n
set lst {}
for {set i 0} {$i < $n} {incr i} {
	scan [gets stdin] {%s %d} name score
	lappend lst [list $name $score]
}
set lst [lsort -decreasing -command cmp $lst]

set prev [lindex [lindex $lst 0] 1]
set start 0 
for {set i 1} {$i <= [llength $lst]} {incr i} {
	if {$i < [llength $lst]} {
		set dat [lindex $lst $i]
		set score [lindex $dat 1]
	}
	if {$i == [llength $lst] || $score != $prev} {
		if {[expr $i-$start] > 1} {
			for {set j $start} {$j < $i} {incr j} {
				puts [format {%d-%d %s} [expr $start+1] $i [lindex [lindex $lst $j] 0]]
			}
		} else {
			puts [format {%d %s} $i [lindex [lindex $lst $start] 0]]
		}
		set prev $score
		set start $i
	}
}
