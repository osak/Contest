#!/usr/bin/ruby

require 'rational'

class Fixnum
	def depth
		n = self
		ret = 0
		while n > 0
			ret += 1
			n >>= 1
		end
		ret
	end
end

def add(node, value, tree)
	tree[node] ||= 0
	tree[node] += value
	add(node>>1, value, tree) if node > 1
end

def search(node, min, tree, h)
	depth = node.depth
	return tree[node].to_f / 2**(depth-1) if depth == h

	#left
	al = tree[node<<1]
	ar = tree[node]-al

	ret = 0.0
	if ar >= al
		ret += [ar,min].max.to_f / 2**depth
	else
		ret += search(node<<1, [min,ar].max, tree, h) 
	end

	#right
	ar = tree[(node<<1)+1]
	al = tree[node]-ar
	if al >= ar
		ret += [al,min].max.to_f / 2**depth
	else
		ret += search((node<<1)+1, [min,al].max, tree, h) 
	end

	ret
end

tree = {}
tree.default = 0
h,q = gets.split.map(&:to_i)
h += 1
q.times do
	query = gets
	if query[0..2] == 'add'
		v,e = query.split[1..2].map(&:to_i)
		add(v, e, tree)
	else
		printf("%.5f\n", search(1, 0, tree, h))
	end
end

