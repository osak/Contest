//Name: PalindromicSubstringsDiv1
//Level: 3
//Category: 数学,期待値,文字列,回文
//Note: SRM607 Div1Easy

/**
 * 期待値の線形性より、それぞれの長さの回文について独立に考えてよい。
 * ある文字を中心にした奇数文字の回文を考えるとき、幅2w-1([i-w, i+w])で回文だったとすると、
 * ・[i-w-1]か[i+w+1]が'?'のとき、幅2w+1の文字列が回文になる確率は1/26
 * ・'?'でないとき、同じ文字なら確率1で回文、そうでないなら確率0
 * となる。
 * 偶数文字についても同様に考えることができる。
 * あとは中心の文字を全て試し、幅wを1ずつ増やしていけばよい。
 *
 * オーダーはO(N^2)。
 * ただしNは文字列の長さ。
 */
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class PalindromicSubstringsDiv1 {
public:
    double expectedPalindromes( vector <string> S1, vector <string> S2 ) {
        string str;
        for(auto s : S1) str += s;
        for(auto s : S2) str += s;
        const int N = str.size();
        double res = 0;
        // For Odd
        for(int i = 0; i < N; ++i) {
            int left = i, right = i;
            double prob = 1;
            while(left >= 0 && right < N) {
                if(str[left] == '?' && str[right] == '?') {
                    if(left != right) prob /= 26;
                } else if(str[left] == '?' || str[right] == '?') {
                    prob /= 26;
                } else if(str[left] != str[right]) {
                    break;
                }
                res += prob;
                --left;
                ++right;
            }
        }
        //cout << res << endl;
        // For Even
        for(int i = 0; i < N-1; ++i) {
            int left = i, right = i+1;
            double prob = 1;
            while(left >= 0 && right < N) {
                if(str[left] == '?' && str[right] == '?') {
                    prob /= 26;
                } else if(str[left] == '?' || str[right] == '?') {
                    prob /= 26;
                } else if(str[left] != str[right]) {
                    break;
                }
                res += prob;
                --left;
                ++right;
            }
        }
        return res;
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
			string S1[]               = {"a","a",""};
			string S2[]               = {"a"};
			double expected__         = 6.0;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S1[]               = {"z??"};
			string S2[]               = {};
			double expected__         = 3.115384615384615;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S1[]               = {"ab","c"};
			string S2[]               = {"??","a?"};
			double expected__         = 7.315088757396449;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S1[]               = {};
			string S2[]               = {"?"};
			double expected__         = 1.0;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S1[]               = {"ab?def","?"};
			string S2[]               = {"f??a"};
			double expected__         = 12.545971779699588;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string S1[]               = ;
			string S2[]               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string S1[]               = ;
			string S2[]               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S1[]               = ;
			string S2[]               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
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
