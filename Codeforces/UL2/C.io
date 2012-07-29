f := File standardInput
n := f readLine asNumber
list := List clone
n repeat(a, list append (a+1))
list := list select(i, v, n % v == 0)
odds := list select(i, v, v isOdd) size
evens := list select(i, v, v isEven) size
if(odds == evens) then("yes" println) else("no" println)
