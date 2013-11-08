//Name: BitwiseAnd
//Level: 3
//Category: 貪欲,Greedy
//Note: SRM596 Div1 Medium

/**
 * 条件より、以下のことがわかる。
 * ・iビット目が立っている数は、全体で0,1,2個のいずれか
 *
 * まず、与えられたセットが条件を満たしているかを確認する。
 * 次に数を加えていくときは、上記の考察より、subsetの中で1個だけが立っているビットを持っているような箇所を埋める必要がある。
 * なるべく数は小さいほうがいいので、加える数ひとつにつき、subsetとの各数との共通ビットは、それぞれにつき1bitあれば十分である。
 *
 * 最後に、加えた数どうしで条件を満たすような共通部分が生じるようにする。
 * これは、サンプル4(subsetが空)の答えを見ると分かりやすいが、k個の数で条件を満たすようなビット配置を作り出すには、
 * 1つの数がk-1個のビットを立て、残りが1ビットづつこれを消費していけばよい。
 *
 * 上の2つの作業を貪欲に、利用できる下位ビットから順に使っていくようにすればよい。
 * 途中で操作ができなくなったら解は存在しない。
 *
 * オーダーはO(M^3 + NM)。
 * ただし、Mはsubsetの大きさ。
 *
 * また、2つめの操作の考察より、N >= 12では解が存在しないことが言える。
 */
//#define _GLIBCXX_DEBUG
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BitwiseAnd {
public:
    vector<long long> lexSmallest( vector<long long> subset, int N ) {
        vector<int> cnt(60, 0);
        const int M = subset.size();
        const int NEED = N - M;
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < i; ++j) {
                if((subset[i] & subset[j]) == 0) return vector<long long>();
                for(int k = 0; k < j; ++k) {
                    if((subset[i] & subset[j] & subset[k]) != 0) return vector<long long>();
                }
            }
        }

        for(long long v : subset) {
            for(int i = 0; i < 60; ++i) {
                const long long mask = 1LL << i;
                if(mask > v) break;
                if(mask & v) {
                    if(++cnt[i] >= 3) {
                        return vector<long long>();
                    }
                }
            }
        }
        vector<bool> safe(60, true);
        for(int i = 0; i < 60; ++i) {
            safe[i] = (cnt[i] == 0);
        }
        vector<long long> rem = subset;
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < i; ++j) {
                const long long mask = rem[i] & rem[j];
                rem[i] ^= mask;
                rem[j] ^= mask;
            }
        }

        vector<long long> res(NEED, 0);
        for(int i = 0; i < NEED; ++i) {
            for(long long &v : rem) {
                const long long lsb = v&-v;
                if(lsb == 0 || (res[i] & lsb)) return vector<long long>();
                res[i] |= lsb;
                v ^= lsb;
            }
        }
        sort(res.begin(), res.end());
        for(int rank = NEED-1; rank >= 1; --rank) {
            const int base = NEED-rank-1;
            int placed = 0;
            for(int i = 0; i < 60; ++i) {
                if(safe[i]) {
                    res[base] |= 1LL << i;
                    res[base+placed+1] |= 1LL << i;
                    safe[i] = false;
                    if(++placed == rank) break;
                }
            }
            if(placed != rank) return vector<long long>();
        }
        for(long long v : subset) {
            res.push_back(v);
        }
        sort(res.begin(), res.end());
        return res;
    }
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector<long long> &expected, const vector<long long> &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			long long subset[]        = {14, 20};
			int N                     = 3;
			long long expected__[]    = {14, 18, 20};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			long long subset[]        = {11, 17, 20};
			int N                     = 4;
			long long expected__[]    = {};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			long long subset[]        = {99, 157};
			int N                     = 4;
			long long expected__[]    = {99, 157, 262, 296};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			long long subset[]        = {1152921504606846975LL};
			int N                     = 3;
			long long expected__[]    = {};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			long long subset[]        = {};
			int N                     = 5;
			long long expected__[]    = {15, 113, 402, 676, 840};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			long long subset[]        = {1, 3, 5, 7, 9, 11};
			int N                     = 6;
			long long expected__[]    = {};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			long long subset[]        = ;
			int N                     = ;
			long long expected__[]    = ;

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			long long subset[]        = ;
			int N                     = ;
			long long expected__[]    = ;

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			long long subset[]        = ;
			int N                     = ;
			long long expected__[]    = ;

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
