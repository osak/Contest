#!/usr/bin/ruby

regs = {}
File.open(ARGV[0]).read.each_line do |line|
	line.chomp!
	cmd, a, b = line.split
	case cmd
	when 'get'
		regs[a] = STDIN.gets.to_i
	when 'put'
		puts regs[a]
	when 'or'
		regs[a] |= (/\d+/===b) ? b.to_i : regs[b]
	when 'and'
		regs[a] &= (/\d+/===b) ? b.to_i : regs[b]
	when 'shl'
		regs[a] <<= b.to_i
	when 'shr'
		regs[a] >>= b.to_i
	when 'mov'
		regs[a] = (/\d+/===b) ? b.to_i : regs[b]
	when 'not'
		regs[a] = ~regs[a]
	end
end

