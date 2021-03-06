//Name: EllysSortingTrimmer
//Level: 2
//Category: 貪欲,Greedy
//Note:

/**
 * 小さい文字を先頭へ持って行きたいので、末尾から順にソートを繰り返していくことで
 * 後ろの方にある小さい文字を確実に前へ持ってこれる。
 * オーダーは O((N-L) L log L)。
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class EllysSortingTrimmer {
public:
    string getMin( string S, int L ) {
        const int N = S.size();
        for(int start = N - L; start >= 0; --start) {
            sort(S.begin()+start, S.begin()+start+L);
            S = S.substr(0, start+L);
        }
        return S;
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
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string S                  = "ABRACADABRA";
			int L                     = 5;
			string expected__         = "AAAAA";

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S                  = "ESPRIT";
			int L                     = 3;
			string expected__         = "EIP";

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S                  = "BAZINGA";
			int L                     = 7;
			string expected__         = "AABGINZ";

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S                  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			int L                     = 13;
			string expected__         = "ABCDEFGHIJKLM";

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S                  = "GOODLUCKANDHAVEFUN";
			int L                     = 10;
			string expected__         = "AACDDEFGHK";

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S                  = "AAAWDIUAOIWDESBEAIWODJAWDBPOAWDUISAWDOOPAWD";
			int L                     = 21;
			string expected__         = "AAAAAAAAABBDDDDDDDEEI";

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string S                  = "TOPCODER";
			int L                     = 3;
			string expected__         = "CDT";

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string S                  = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string S                  = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string S                  = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = EllysSortingTrimmer().getMin(S, L);
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
