//Name: Study Session
//Level: 4
//Category: Fenwick Tree, シミュレーション
//Note:

/**
 * 各時点でリーダーは100人までしかいないので、CHECKのたびに全リーダーをなめてよい。
 * リーダー以外の人が各点数に何人いるかをFenwick Treeで管理しておき、rに関して二分探索することで各CHECKに答えられる。
 * ただし、点数の数値が大きいので、あらかじめ圧縮しておく必要がある。
 *
 * オーダーは O(QN (log N)^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

typedef long long LL;

template <class T>
struct BinaryIndexedTree/*{{{*/
{
  vector<T> tree;
  const int size;
  BinaryIndexedTree(int s) : tree(s+1), size(s) {}
  // i 番目までの要素の累積和
  T read(int i) const
  {
    T sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= i & -i;
    }
    return sum;
  }

  // i 番目の要素
  T read_single(int i) const
  {
    T sum = tree[i];
    if (i > 0) {
      const int z = i - (i & -i);
      --i;
      while (i != z) {
        sum -= tree[i];
        i -= (i & -i);
      }
    }
    return sum;
  }

  void add(int i, T v)
  {
    while (i <= size) {
      tree[i] += v;
      i += (i & -i);
    }
  }

  // read(i) == vとなる最小のi。存在しなければ-1。
  int search(T v) {
        int left = 0, right = size;
        while(left+1 < right) {
            const int center = (left+right) / 2;
            if(read(center) < v) {
                left = center;
            } else {
                right = center;
            }
        }
        if(right == size || read(right) != v) return -1;
        return right;
    }
};/*}}}*/

bool solve() {
	int N, Q;
	if(!(cin >> N >> Q)) return false;
	if(!N && !Q) return false;

	vector<LL> scores(N);
	for(int i = 0; i < N; ++i) {
		cin >> scores[i];
	}
	vector<LL> score_index = scores;
	scores.push_back(-1); // sentinel
	scores.push_back(*max_element(begin(scores), end(scores)) + 1); // sentinel
	sort(begin(scores), end(scores));
	scores.erase(unique(begin(scores), end(scores)), end(scores));

	BinaryIndexedTree<int> bit(score_index.size() + 1);
	for(int i = 0; i < N; ++i) {
		score_index[i] = distance(begin(scores), lower_bound(begin(scores), end(scores), score_index[i]));
		bit.add(score_index[i], 1);
	}

	multiset<int> leader_scores;
	while(Q--) {
		string cmd;
		int x;
		cin >> cmd >> x;

		if(cmd == "ADD") {
			bit.add(score_index[x-1], -1);
			leader_scores.insert(score_index[x-1]);
		} else if(cmd == "REMOVE") {
			bit.add(score_index[x-1], 1);
			leader_scores.erase(leader_scores.find(score_index[x-1]));
		} else if(cmd == "CHECK") {
			// Binary search for r
			LL left = -1, right = scores.back();
			bool found = false;
			while(left+1 < right) {
				const LL r = (left + right) / 2;
				int not_in_group = 0;
				LL prev_leader_score = 0;
				for(int leader_score : leader_scores) {
					const LL actual = scores[leader_score];
					const LL lim = actual - r;
					if(scores[prev_leader_score] < lim-1) {
						int lim_idx = distance(begin(scores), lower_bound(begin(scores), end(scores), lim-1));
						if(scores[lim_idx] > lim-1) --lim_idx;
						not_in_group += bit.read(lim_idx) - bit.read(prev_leader_score);
					}
					prev_leader_score = leader_score;
				}
				not_in_group += bit.read(bit.size) - bit.read(prev_leader_score);
				if(not_in_group <= x) {
					right = r;
					found = true;
				} else {
					left = r;
				}
			}
			if(found) {
				cout << right << endl;
			} else {
				cout << "NA" << endl;
			}
		}
	}

	return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
