gets stdin path
set lst [lreplace [split $path "/"] 0 0]
set ans {}
set ok true

foreach dir $lst {
	if {[string compare $dir ".."] == 0} {
		if {[llength $ans] > 0} {
			set ans [lrange $ans 0 [expr [llength $ans]-2]]
		} else {
			set ok false
			break
		}
	} elseif {[string compare $dir "."] != 0} {
		lappend ans $dir
	}
}

if {$ok} {
	puts [format {/%s} [join $ans "/"]]
} else {
	puts -1
}
