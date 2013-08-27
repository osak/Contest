// Name: GooseTattarrattatDiv1
// Level: 3
// Category: 文字列,Union-Find
// Note: SRM589 Div1 Easy

/*
 * 対称な位置にある文字は最終的に同じ文字になる必要がある。
 * この関係で文字を結んでいき、各グループを一番初期個数の多い文字に寄せるようにすると最小コストで回文にできる。
 *
 * オーダーは O(N+C^2)。
 * ただしCはアルファベットの文字数で26。
 */
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

struct GooseTattarrattatDiv1 {
    int get(vector<int> &roots, int a) {
        if(roots[a] == a) return a;
        return roots[a] = get(roots, roots[a]);
    }

    int getmin( string S ) {
        const int N = S.size();
        vector<int> roots(26);
        vector<int> charcnt(26);
        for(int i = 0; i < 26; ++i) {
            roots[i] = i;
        }
        for(char c : S) {
            charcnt[c-'a']++;
        }
        for(int i = 0; i < N/2; ++i) {
            const int r1 = get(roots, S[i]-'a');
            const int r2 = get(roots, S[N-i-1]-'a');
            if(r1 != r2) {
                roots[r2] = r1;
            }
        }
        int ans = 0;
        set<int> seen;
        for(int i = 0; i < 26; ++i) {
            const int ri = get(roots, i);
            if(seen.count(ri)) continue;
            seen.insert(ri);
            int sum = 0;
            int maxval = 0;
            for(int j = i; j < 26; ++j) {
                const int ji = get(roots, j);
                if(ri == ji) {
                    sum += charcnt[j];
                    maxval = max(maxval, charcnt[j]);
                }
            }
            ans += sum - maxval;
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
			string S                  = "geese";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S                  = "tattarrattat";
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S                  = "xyyzzzxxx";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S                  = "xrepayuyubctwtykrauccnquqfuqvccuaakylwlcjuyhyammag";
			int expected__            = 11;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S                  = "abaabb";
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseTattarrattatDiv1().getmin(S);
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
