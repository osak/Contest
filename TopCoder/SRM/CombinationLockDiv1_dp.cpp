//Name: CombinationLockDiv1
//Level: 4
//Category: 動的計画法,DP
//Note: SRM607 Div1Medium

/**
 * 左から順に揃えていくことを考える。
 * このとき、今見ているダイヤルの左隣について、「どちらに回したか」と「何回回したか」に対して、そのときの最小コストを覚えておく。
 * すると、便乗したときのコストが完全に計算できる。
 * 更新式は以下のようになる。
 * ・左隣と逆側に回す時、左隣の最小コスト + 回す回数
 * ・左隣と同じ方向に回す時
 * 　・左隣より多く回すとき、prev[j] + (i - j) だけ余分に回す必要がある。
 * 　　このようなjは単調増加である。
 * 　・左隣より少なく回すとき、余分に回す必要はない。
 *
 * オーダーはO(NM)。
 * ただしMはひとつのダイヤルを回す回数の上限。
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 2500 * 10 + 10;
class CombinationLockDiv1 {
public:
    int minimumMoves( vector <string> P, vector <string> Q ) {
        string p, q;
        for(auto s : P) p += s;
        for(auto s : Q) q += s;
        const int N = p.size();

        const int M = 2500 * 10 + 10;
        vector<vector<int>> dp(2, vector<int>(M, INF));
        auto prev = dp;

        prev[0][0] = prev[1][0] = 0;
        for(int i = 0; i < N; ++i) {
            {
                // inc
                fill(dp[0].begin(), dp[0].end(), INF);
                const int diff = (q[i] - p[i] + 10) % 10;
                int min_dec = *min_element(prev[1].begin(), prev[1].end());
                for(int j = 0; j < M; ++j) {
                    if(j % 10 == diff) {
                        dp[0][j] = min_dec + j;
                    }
                }
                int best_pos = 0;
                for(int j = 0; j < M; ++j) {
                    if(prev[0][j] < prev[0][best_pos] + (j - best_pos)) {
                        best_pos = j;
                    }
                    if(j % 10 == diff) {
                        dp[0][j] = min(dp[0][j], prev[0][best_pos] + j - best_pos);
                    }
                }
                best_pos = M-1;
                for(int j = M-1; j >= 0; --j) {
                    if(prev[0][j] < prev[0][best_pos]) {
                        best_pos = j;
                    }
                    if(j % 10 == diff) {
                        dp[0][j] = min(dp[0][j], prev[0][best_pos]);
                    }
                }
            }
            {
                // dec
                fill(dp[1].begin(), dp[1].end(), INF);
                const int diff = (p[i] - q[i] + 10) % 10;
                int min_inc = *min_element(prev[0].begin(), prev[0].end());
                for(int j = 0; j < M; ++j) {
                    if(j % 10 == diff) {
                        dp[1][j] = min_inc + j;
                    }
                }
                int best_pos = 0;
                for(int j = 0; j < M; ++j) {
                    if(prev[1][j] < prev[1][best_pos] + (j - best_pos)) {
                        best_pos = j;
                    }
                    if(j % 10 == diff) {
                        dp[1][j] = min(dp[1][j], prev[1][best_pos] + j - best_pos);
                    }
                }
                best_pos = M-1;
                for(int j = M-1; j >= 0; --j) {
                    if(prev[1][j] < prev[1][best_pos]) {
                        best_pos = j;
                    }
                    if(j % 10 == diff) {
                        dp[1][j] = min(dp[1][j], prev[1][best_pos]);
                    }
                }
            }
            dp.swap(prev);
        }
        return min(*min_element(prev[0].begin(), prev[0].end()), *min_element(prev[1].begin(), prev[1].end()));
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
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
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
			string P[]                = {"123"};
			string Q[]                = {"112"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string P[]                = {"1"};
			string Q[]                = {"7"};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string P[]                = {"6","07"};
			string Q[]                = {"","60","7"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string P[]                = {"1234"};
			string Q[]                = {"4567"};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string P[]                = {"020"};
			string Q[]                = {"909"};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string P[]                = {"4423232218340"};
			string Q[]                = {"6290421476245"};
			int expected__            = 18;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			vector<string> P;
            for(int i = 0; i < 50; ++i) {
                P.push_back(string(50, '0'));
            }
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(P, P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
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
