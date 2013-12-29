//Name: TypoCoderDiv1
//Level: 2
//Category: 動的計画法,DP,探索
//Note: SRM602 Div1 Easy

/**
 * レーティングは各回について2201*2通りしかあり得ない。
 * （2200を超えると次に強制的に下げられるため、2200超えのレーティングは前回の0-2200のどこかから遷移するしかない）
 * したがって、普通にmapに突っ込んで探索すれば間に合う。
 *
 * オーダーはO(N)。
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class TypoCoderDiv1 {
public:
    int getmax( vector <int> D, int X ) {
        unordered_map<int,int> memo;
        memo[X] = 0;
        for(auto d : D) {
            unordered_map<int,int> nmemo;
            for(auto cur : memo) {
                //cout << d << ' ' << cur.first << ' ' << cur.second << endl;
                if(cur.first < 2200) { // can win
                    const int next = cur.first + d;
                    int nc = cur.second;
                    if(next >= 2200) {
                        ++nc;
                    }
                    nmemo[next] = max(nmemo[next], nc);
                }
                { // to lose
                    const int next = max(0, cur.first - d);
                    int nc = cur.second;
                    if(cur.first >= 2200 && next < 2200) {
                        ++nc;
                    }
                    if(next < 2200) {
                        nmemo[next] = max(nmemo[next], nc);
                    }
                }
            }
            nmemo.swap(memo);
        }
        int ans = 0;
        for(auto cur : memo) {
            ans = max(ans, cur.second);
        }
        return ans;
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
			int D[]                   = {100,200,100,1,1};
			int X                     = 2000;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int D[]                   = {0,0,0,0,0};
			int X                     = 2199;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int D[]                   = {90000,80000,70000,60000,50000,40000,30000,20000,10000};
			int X                     = 0;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int D[]                   = {1000000000,1000000000,10000,100000,2202,1};
			int X                     = 1000;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int D[]                   = {2048,1024,5012,256,128,64,32,16,8,4,2,1,0};
			int X                     = 2199;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int D[]                   = ;
			int X                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int D[]                   = ;
			int X                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int D[]                   = ;
			int X                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
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
