#!/usr/bin/env ruby

def doit(arr)
	arr.each do |obj|
		yield obj
	end
end

n = gets.to_i
weapons = []
armors = []
orbs = []

whole_size = 0
n.times do
	arr = gets.chomp.split
	case arr[1]
	when 'weapon'
		weapons << { :name => arr[0], :val => arr[2].to_i, :size => arr[5].to_i }
	when 'armor'
		armors << { :name => arr[0], :val => arr[3].to_i, :size => arr[5].to_i }
	when 'orb'
		orbs << { :name => arr[0], :val => arr[4].to_i, :size => arr[5].to_i }
	end
	whole_size += arr[5].to_i
end
doit([weapons, armors, orbs]) { |obj| obj.sort_by!{ |a| a[:val] } }

m = gets.to_i
gladiators = []
sentries = []
physicians = []
m.times do
	arr = gets.chomp.split
	case arr[1]
	when 'gladiator'
		gladiators << { :name => arr[0], :val => arr[2].to_i, :home => arr[3] }
	when 'sentry'
		sentries << { :name => arr[0], :val => arr[2].to_i, :home => arr[3] }
	when 'physician'
		physicians << { :name => arr[0], :val => arr[2].to_i, :home => arr[3] }
	end
end
doit([gladiators, sentries, physicians]) { |obj| obj.sort_by!{ |a| a[:val] }.reverse! }

if m < whole_size
	doit([[weapons, gladiators], [armors, sentries], [orbs, physicians]]) do |arr|
		item = arr[0]
		res = arr[1]
		item.each do |obj|
			size = obj[:size]
			obj[:val] += res[0,size].inject(0) { |a, r| a + r[:val] }
			obj[:residents] = res[0,size].map { |a| a[:name] }
		end
	end
else
	doit([[weapons, gladiators], [armors, sentries], [orbs, physicians]]) do |arr|
		item = arr[0]
		res = arr[1]
		res.each do |r|
			item.each do |i|
                i[:residents] ||= []
				if i[:name] == r[:home]
					i[:val] += r[:val]
					i[:residents] << r[:name]
					break
				end
			end
		end
	end
end
doit([weapons, armors, orbs]) { |obj| obj.sort_by!{ |a| a[:val] } }

items = weapons + armors + orbs
residents = gladiators + sentries + physicians
residents_list = residents.map { |r| r[:name] }
used_list = weapons[-1][:residents] + armors[-1][:residents] + orbs[-1][:residents]
not_used_list = residents_list - used_list
not_used_list.each do |name|
	if weapons[-1][:residents].size < weapons[-1][:size]
		weapons[-1][:residents] << name
	elsif armors[-1][:residents].size < armors[-1][:size]
		armors[-1][:residents] << name
	elsif orbs[-1][:residents].size < orbs[-1][:size]
		orbs[-1][:residents] << name
	else
		break
	end
end

puts "#{weapons[-1][:name]} #{weapons[-1][:residents].size} #{weapons[-1][:residents].join(' ')}"
puts "#{armors[-1][:name]} #{armors[-1][:residents].size} #{armors[-1][:residents].join(' ')}"
puts "#{orbs[-1][:name]} #{orbs[-1][:residents].size} #{orbs[-1][:residents].join(' ')}"
