gets stdin str
set lst [split $str "."]
set ok true
foreach part $lst {
	if {$part == {} || [regexp {^[a-z0-9]+$} $part] == 0} {
		set ok false
		break
	}
}
set len [string length $part]
if {$len < 2 || 3 < $len} {
	set ok false
}
if {$ok} {
	puts "YES"
} else {
	puts "NO"
}
