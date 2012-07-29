f := File standardInput
n := f readLine asNumber

prev := 1
ans := 1
for(a, 2, n,
	tmp := ans
	ans := ans + prev
	prev := tmp)
ans println
