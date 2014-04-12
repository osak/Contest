//Name: EllysScrabble
//Level: 3
//Category: 貪欲,Greedy
//Note:

/**
 * 先頭から順に、前後D文字を見て一番小さいものを採用していく。
 * ただし、全部を貪欲に決めると取り残される文字が発生するので、そのような文字は
 * なるべく右側に寄せるようにして処理する。
 *
 * オーダーは O(ND)。
 */
#include <string>
#include <vector>
using namespace std;

class EllysScrabble {
public:
    string getMin( string letters, int maxDistance ) {
        const int N = letters.size();
        const char INF = '\x7f';
        string res = "";
        for(int i = 0; i < N; ++i) {
            char min_char = INF;
            int min_pos = 0;
            if(i >= maxDistance && letters[i - maxDistance] != INF) {
                min_pos = i - maxDistance;
                min_char = letters[min_pos];
            } else {
                for(int d = -maxDistance; d <= maxDistance; ++d) {
                    const int p = i + d;
                    if(p < 0) continue;
                    if(p >= N) break;
                    if(min_char > letters[p]) {
                        min_char = letters[p];
                        min_pos = p;
                    }
                }
            }
            res += min_char;
            letters[min_pos] = INF;
        }
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
			string letters            = "TOPCODER";
			int maxDistance           = 3;
			string expected__         = "CODTEPOR";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string letters            = "ESPRIT";
			int maxDistance           = 3;
			string expected__         = "EIPRST";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string letters            = "BAZINGA";
			int maxDistance           = 8;
			string expected__         = "AABGINZ";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string letters            = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			int maxDistance           = 9;
			string expected__         = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string letters            = "GOODLUCKANDHAVEFUN";
			int maxDistance           = 7;
			string expected__         = "CADDGAHEOOFLUKNNUV";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string letters            = "AAAWDIUAOIWDESBEAIWODJAWDBPOAWDUISAWDOOPAWD";
			int maxDistance           = 6;
			string expected__         = "AAAADDEIBWAEUIODWADSBIAJWODIAWDOPOAWDUOSPWW";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string letters            = "ABRACADABRA";
			int maxDistance           = 2;
			string expected__         = "AABARACBDAR";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 7: {
			string letters            = "EDCDE";
			int maxDistance           = 2;
			string expected__         = "";

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 8: {
			string letters            = ;
			int maxDistance           = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string letters            = ;
			int maxDistance           = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = EllysScrabble().getMin(letters, maxDistance);
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
