f := File standardInput
line := f readLine

ans := line clone
rep := 1
for(len, 1, line size,
	for(start, 0, line size - len,
		pat := line slice(start, start+len)
		cnt := 0
		pos := line findSeq(pat)
		while(pos isNil not,
			cnt := cnt+1
			pos := line findSeq(pat, pos+1))
		if(cnt > rep or (cnt == rep and (pat size > ans size or (pat size == ans size and pat > ans))),
			ans := pat
			rep := cnt)))

ans println
