//Name: CombinationLockDiv1
//Level: 4
//Category: 貪欲,Greedy
//Note: SRM607 Div1Medium

/**
 * ダイヤルを1方向に回すことだけを考える。
 * このとき、隣り合ったダイヤルどうしの差分を取ると、最終形ではPとQでこの配列を同じ形にすることが目的となる。
 * （そのままだと同じ差分をもつ10通りを区別できないが、端に0を埋めておくと数字が一致する条件まで表現できる）
 * このとき、ダイヤルを増やす方向へ回すと、ある区間のダイヤルを回すということは、右端の差分が+1され、左端の差分が-1されることと等価である。
 * 減らす方向のときは逆になる。
 * これを繰り返すのだから、任意の時点において、一番小さいものを-1し、一番大きいものを+1するのが最適戦略である。
 *
 * オーダーはO(N log N)。
 */
#include <string>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

class CombinationLockDiv1 {
public:
    int minimumMoves( vector <string> P, vector <string> Q ) {
        string p, q;
        for(auto s : P) p += s;
        for(auto s : Q) q += s;
        const int N = p.size();
        p += "0";
        q += "0";

        multiset<int> ms;
        for(int i = 0; i < N; ++i) {
            const int dp = (p[i] - p[i+1] + 10) % 10;
            const int dq = (q[i] - q[i+1] + 10) % 10;
            const int diff = (dp - dq + 10) % 10;
            //cout << diff << endl;
            if(diff != 0) ms.insert(diff);
        }
        int res = 0;
        while(ms.size() > 1) {
            ++res;
            int left = *ms.begin();
            int right = *ms.rbegin();
            ms.erase(ms.begin());
            ms.erase(ms.find(right));
            --left; ++right;
            if(left > 0) ms.insert(left);
            if(right < 10) ms.insert(right);
        }
        if(ms.size() > 0) res += min(*ms.begin(), 10 - *ms.begin());
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
