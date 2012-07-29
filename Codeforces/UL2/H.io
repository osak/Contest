f := File standardInput
line := f readLine 
neg := false
if(line at(0) asCharacter == "-", 
	neg := true
	line := line slice(1))

while(line at(0) asCharacter == "0",
	line := line slice(1)
	if(line == "", break))

if(line == "") then(line := "0") else(
		line := line reverse
		while(line at(0) asCharacter == "0",
			line := line slice(1))
		if(neg, line := "-" .. line))
line println
