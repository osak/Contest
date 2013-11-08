//Name: IncrementAndDoubling
//Level: 2
//Category: やるだけ,貪欲,Greedy
//Note: SRM596 Div1 Easy

/**
 * 大きい数はシフトで作ったほうがよいのは明らかで、小さい数でも1はInc1手、2はInc2手かInc1+Double1の2手。
 * したがって、貪欲に1ビットずつ立てながらシフトしていけばよい。
 * オーダーはO(N)。
 */
#include <string>
#include <vector>
using namespace std;

class IncrementAndDoubling {
public:
    int getMin( vector <int> desiredArray ) {
        int double_cnt = 0;
        int inc_cnt = 0;
        for(int bit = 10; bit >= 0; --bit) {
            const int mask = 1 << bit;
            for(int v : desiredArray) {
                if(mask & v) {
                    double_cnt = max(double_cnt, bit);
                    ++inc_cnt;
                }
            }
        }
        return double_cnt+inc_cnt;
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
			int desiredArray[]        = {2, 1};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int desiredArray[]        = {16, 16, 16};
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int desiredArray[]        = {100};
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int desiredArray[]        = {0, 0, 1, 0, 1};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int desiredArray[]        = {123, 234, 345, 456, 567, 789};
			int expected__            = 40;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int desiredArray[]        = {7,5,8,1,8,6,6,5,3,5,5,2,8,9,9,4,6,9,4,4,1,9,9,2,8,4,7,4,8,8,6,3,9,4,3,4,5,1,9,8,3,8,3,7,9,3,8,4,4,7};
			int expected__            = 84;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int desiredArray[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int desiredArray[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int desiredArray[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
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
