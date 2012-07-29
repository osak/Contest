gets stdin nstr
set fact 1
for {set i 1} {$i <= $nstr} {incr i} {
	set fact [expr $fact*$i]
}
puts stdout $fact
