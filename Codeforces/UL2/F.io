f := File standardInput
arr := f readLine split map(v, v asNumber)
n := arr at(0)
m := arr at(1)
rows := List clone
cols := List clone
for(i, 1, n, rows append(i))
for(i, 1, m, cols append(i))

ts := f readLine split map(v, v asNumber)
ts removeAt(0)
ts foreach(v, rows remove(v))

ss := f readLine split map(v, v asNumber)
ss removeAt(0)
ss foreach(v, cols remove(v))

rc := 1
for(i, 1, rows size - 1,
	if(rows at(i) - rows at(i-1) > 1, rc := rc+1))
cc := 1
for(i, 1, cols size - 1,
	if(cols at(i) - cols at(i-1) > 1, cc := cc+1))

if(rows size == 0 or cols size == 0) then(0 println) else((rc*cc) println)
