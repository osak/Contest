f := File standardInput
line := f readLine

happy := false
happier := true
n := line asNumber
line foreach(v,
	digit := v asCharacter asNumber
	if(n % digit == 0) then(happy := true) else(happier := false))

if(happier) then("happier" println) else(if(happy) then("happy" println) else("upset" println))

