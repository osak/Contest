Entry := Object clone
#Entry compare := method(other, 
#	if(self section != other section) then((self section compare(other section))) else((self name compare(other name))))

f := File standardInput
n := f readLine asNumber

section := ""
list := List clone
n repeat(
	line := f readLine strip
	if(line at(0) asCharacter == ";", continue)
	if(line at(0) asCharacter == "[") then(
		section := line slice(1, line size-1) strip
		entry := Entry clone
		entry name := ""
		entry section := section
		list append(entry)
	) else(
		eql := line findSeq("=")
		name := line slice(0, eql) strip
		value := line slice(eql+1) strip
		entry := nil
		list foreach(e, 
			if(e name == name and e section == section, 
				entry := e
				break))
		if(entry isNil,
			entry := Entry clone
			list append(entry))
		entry name := name
		entry value := value
		entry section := section
	)
)

list := list sortBy(block(a, b, 
	if(a section != b section) then(return a section < b section) else(return a name < b name)))

prevsec := ""
list foreach(e,
	if(e section != prevsec,
		writeln("[",e section,"]")
		prevsec := e section)
	if(e name != "", writeln(e name,"=",e value)))
