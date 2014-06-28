//Name: FixedDiceGameDiv1
//Level: 3
//Category: 確率,期待値
//Note: SRM626 Div1 Easy

/**
 * Alice, Bobそれぞれについて、特定の目が出る確率をDPで計算しておく。
 * 求める期待値は E[a | a > b] = ∑ a ✕ P(a,b | A > B) であるから、条件付き確率の定義より
 *   ∑ a ✕ P(a,b | A > B) = ∑ a ✕ P(a,b) / P(A > B)
 * を計算すればよい。
 *
 * オーダーは O((AB)^2)。
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

class FixedDiceGameDiv1 {
public:
    vector<long double> calc(int a, int b) {
        vector<long double> res(a*b+1, 0);
        res[0] = 1;
        for(int i = 0; i < a; ++i) {
            vector<long double> tmp(a*b+1, 0);
            for(int j = 0; j < a*b+1; ++j) {
                for(int k = 1; k <= b; ++k) {
                    if(j-k >= 0) tmp[j] += res[j-k] / b;
                }
            }
            for(long double l : tmp) {
                cout << l << endl;
            }
            cout << "---" << endl;
            res.swap(tmp);
        }
        return res;
    }

    double getExpectation( int a, int b, int c, int d ) {
        vector<long double> alice_prob = calc(a, b);
        vector<long double> bob_prob = calc(c, d);

        long double res = 0;
        long double alice_win = 0;
        for(int i = 1; i <= a*b; ++i) {
            if(alice_prob[i] == 0) continue;
            for(int j = 0; j < i && j <= c*d; ++j) {
                long double prob = alice_prob[i] * bob_prob[j];
                res += i * prob;
                alice_win += prob;
            }
        }
        if(alice_win == 0.0) return -1;
        return res / alice_win;
    }
};

// BEGIN CUT HERE
#include <algorithm>
#include <cmath>
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
			//i += x;
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9;
	static bool topcoder_fequ(double expected, double result) {
		if (std::isnan(expected)) {
			return std::isnan(result);
		} else if (std::isinf(expected)) {
			if (expected > 0) {
				return result > 0 && std::isinf(result);
			} else {
				return result < 0 && std::isinf(result);
			}
		} else if (std::isnan(result) || std::isinf(result)) {
			return false;
		} else if (std::fabs(result - expected) < MAX_DOUBLE_ERROR) {
			return true;
		} else {
			double mmin = std::min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			double mmax = std::max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			return result > mmin && result < mmax;
		}
	}
	double moj_relative_error(double expected, double result) {
		if (std::isnan(expected) || std::isinf(expected) || std::isnan(result) || std::isinf(result) || expected == 0) {
			return 0;
		}
		return std::fabs(result-expected) / std::fabs(expected);
	}
	
	int verify_case(int casenum, const double &expected, const double &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				std::sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int a                     = 1;
			int b                     = 2;
			int c                     = 1;
			int d                     = 5;
			double expected__         = 2.0;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a                     = 3;
			int b                     = 1;
			int c                     = 1;
			int d                     = 3;
			double expected__         = 3.0;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a                     = 1;
			int b                     = 5;
			int c                     = 1;
			int d                     = 1;
			double expected__         = 3.4999999999999996;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a                     = 2;
			int b                     = 6;
			int c                     = 50;
			int d                     = 30;
			double expected__         = -1.0;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a                     = 50;
			int b                     = 11;
			int c                     = 50;
			int d                     = 50;
			double expected__         = 369.8865999182022;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
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
