#!/usr/bin/ruby

class Hash
	def calc
		ret = [0, 0]
		self.each_pair { |n, v|
			if n =~ /\./
				ret[1] += 1
			else
				tmp = v.calc
				ret[0] += 1 + tmp[0]
				ret[1] += tmp[1]
			end
		}
		ret
	end

	def subfolders
		cnt = 0
		self.each_pair { |n, v|
			cnt += 1+v.subfolders unless n =~ /\./
		}
		cnt
	end

	def files
		cnt = 0
		self.each_pair { |n, v|
			if n =~ /\./
				cnt += 1
			else
				cnt += v.files
			end
		}
		cnt
	end
end

tree = {}
ARGF.read.each_line { |line|
	line.chomp!
	cur = tree
	line.split("\\").each { |dir|
		cur[dir] ||= {}
		cur = cur[dir]
	}
}

v = tree.values.map { |drv| drv.values }.flatten
puts "#{v.map(&:subfolders).max} #{v.map(&:files).max}"
