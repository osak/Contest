//Name: WhiteSpaceEditing
//Level: 3
//Category: 動的計画法,DP
//Note: SRM499 Div1 Medium

/**
 * 行をくっつけるような操作はできないので、基本的には上から順番に作っていくことになる。
 *
 * まず、linesにない文字列長で改行するのは無駄であることがわかる。
 * したがって、あり得る文字列長はlinesの中身と0の高々N+1通りである。
 *
 * 行の構成は、単純に上から確定させていくだけだと2 2 1のようなケースでうまくいかない。
 * （0→1→1 1→2 1→2 2 1が最適解）
 * これは、[start, end)を構成するとき、途中のkで分割して[start, k)と[k, end)で別々に構成するように扱うことができる。
 * このとき、問題になるのはkの場所と、kでの長さである。
 *
 * 以上をまとめると、状態(start, end, len)からkの場所と長さを決めて次の状態に遷移するようなDPが構成できる。
 * オーダーはO(N^5)。
 */
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

class WhiteSpaceEditing {
public:
    int memo[55][55][55];
    int INF;

    int calc(int start, int end, int il, const vector<int> &lines) {
        if(start >= end) return 0;
        int &res = memo[start][end][il];
        if(res >= 0) return res;

        const int init = lines[il];
        res = INF;
        if(start+1 == end) {
            res = abs(init - lines[start]) + 1;
        } else {
            for(int k = start+1; k < end; ++k) {
                res = min(res, 1 + calc(start, k, il, lines) - 1 + calc(k, end, il, lines));
                for(int j = start; j < end; ++j) {
                    const int kl = lines[j];
                    int tmp = abs(init - kl);
                    tmp++;
                    tmp += calc(start, k, j, lines);
                    tmp--; // Unneccesary NL
                    tmp += calc(k, end, j, lines);
                    res = min(res, tmp);
                }
            }
        }
        //cout << start << ' ' << end << ' ' << init << ' ' << res << endl;
        return res;
    }

    int getMinimum( vector <int> lines ) {
        for(int i = 0; i < 55; ++i) {
            for(int j = 0; j < 55; ++j) {
                for(int k = 0; k < 55; ++k) {
                    memo[i][j][k] = -1;
                }
            }
        }
        lines.insert(lines.begin(), 0);
        INF = accumulate(lines.begin(), lines.end(), 0) + lines.size();
        return calc(0, lines.size(), 0, lines)-2;
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
			int lines[]               = { 3, 2, 3 };
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = WhiteSpaceEditing().getMinimum(vector <int>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int lines[]               = { 0 };
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = WhiteSpaceEditing().getMinimum(vector <int>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int lines[]               = { 1, 2, 4 } ;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = WhiteSpaceEditing().getMinimum(vector <int>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int lines[]               = { 250, 105, 155, 205, 350 } ;
			int expected__            = 499;

			std::clock_t start__      = std::clock();
			int received__            = WhiteSpaceEditing().getMinimum(vector <int>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			int lines[]               = {1,1,0};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = WhiteSpaceEditing().getMinimum(vector <int>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			int lines[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WhiteSpaceEditing().getMinimum(vector <int>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int lines[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WhiteSpaceEditing().getMinimum(vector <int>(lines, lines + (sizeof lines / sizeof lines[0])));
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
