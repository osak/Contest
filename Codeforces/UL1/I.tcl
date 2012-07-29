set fields [split [gets stdin] " "]
set orders [split [gets stdin] ","]
set data {}
while {![eof stdin]} {
	lappend data [split [gets stdin] " "]
}
set data [lrange $data 0 [expr [llength $data]-2]]

foreach order [lreverse $orders] {
	regexp {(\w+) (\w+)} $order all field so
	set idx [lsearch $fields $field]
	if {[string compare $so "ASC"] == 0} {
		set data [lsort -index $idx $data]
	} else {
		set data [lsort -decreasing -index $idx $data]
	}
}
foreach dat $data {
	puts [join $dat " "]
}
