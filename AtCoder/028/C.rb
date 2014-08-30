# Name: 高橋王国の分割統治
# Level: 3
# Category: 木,Tree,DFS,深さ優先探索
# Note:

# ある頂点を首都にしたとき、バランス値は
#   max(子サブツリーの大きさ, n - Σ子サブツリー - 1)
# になる。
# 再帰しながらこれらの情報を保存しつつたどればよい。
#
# Rubyでは普通にDFSすると最大ケースでスタックが足りなくなってREするので、
# 先にDFS順序を求めておいて葉から順に処理していくといった工夫が必要。
#
# オーダーは O(N)。
$memo = {}
$tree = {}
$buf = []
def dfs(pos, parent)
  return $memo[pos] if $memo[pos]
  n = $tree.size
  csum = 0
  $buf[pos] = 0
  $tree[pos].each do |c|
    next if c == parent
    s = dfs(c, pos)
    $buf[pos] = s if s > $buf[pos]
    csum += s
  end
  rem = n - csum - 1
  $buf[pos] = rem if rem > $buf[pos]
  $memo[pos] = csum + 1
end

n = gets.to_i
$tree = {}
(n-1).times do |i|
  v = gets.to_i
  $tree[i+1] ||= []
  $tree[i+1] << v
  $tree[v] ||= []
  $tree[v] << i+1
end

dfs_ord = []
stack = [[0, -1]]
used = {}
until stack.empty?
  cur = stack.pop
  dfs_ord << cur
  $tree[cur[0]].each do |c|
    stack << [c, cur[0]] if used[c].nil?
    used[c] = true
  end
end
dfs_ord.reverse!

$buf = Array.new(n, 0)
dfs_ord.each do |i, parent|
  dfs(i, parent)
end
puts $buf
