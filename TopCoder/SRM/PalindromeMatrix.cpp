//Name: PalindromeMatrix
//Level: 5
//Category: 動的計画法,DP
//Note: SRM600 Div1Med

/**
 * 回文にするときは、文字を変える必要があるかどうかだけを考え、実際にどのような配列になるかは無視してよい。
 *
 * まず、回文にする列を決める。
 * その上で行を1行ずつ回文にするかどうかを決めていく。
 * このとき、次の2つの要因で文字の変更が必要になる。
 * ・行rを回文化するため、(r,c)と(r,M-c-1)を揃える
 * ・列cを回文化するため、(r,c)と(N-r-1,c)を揃える
 * これらの関係は推移的になるため、最大で4箇所を同じ文字に揃える必要がある。
 * このとき揃え方は、0か1のうち数が多い方に揃えればよい。
 *
 * また、列の回文化が必要なため、行を回文化する処理はrとN-r-1を同時に考える必要がある。
 * （そうしないと後半の行を回文化するとき、前半の行をどう処理したかで変わってきてしまう）
 *
 * オーダーはO(C(M, rowCount)*N^2 M)。
 */
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <bitset>
using namespace std;

class PalindromeMatrix {
public:
    int N, M;
    vector<string> A;
    array<array<int,15>,15> dp;

    int get(int r, int k) {
        if(r < 0 || k < 0) return 0;
        return dp[r][k];
    }

    void update(int r, int k, int v) {
        dp[r][k] = min(dp[r][k], v);
    }

    void init() {
        for(int i = 0; i <= 14; ++i) {
            for(int j = 0; j <= 14; ++j) {
                dp[i][j] = N*M;
            }
        }
    }

    int calc(int rowCount, bitset<14> pat) {
        init();
        update(0, 0, 0);
        for(int r = 0; r < N/2; ++r) {
            const int rev_r = N-r-1;
            for(int k = 0; k <= N; ++k) {
                // Case 1. Skip this row.
                int v = get(r, k);
                for(int c = 0; c < M; ++c) {
                    if(pat[c] && A[r][c] != A[rev_r][c]) {
                        v++;
                    }
                }
                update(r+1, k, v);

                // Case 2. Make this row palindrome.
                v = get(r, k);
                for(int c = 0; c < M/2; ++c) {
                    int rev_c = M-c-1;
                    int cost = 0;
                    if(pat[c] && pat[rev_c]) {
                        int ones = (A[r][c]-'0') + (A[r][rev_c]-'0') + (A[rev_r][c]-'0') + (A[rev_r][rev_c]-'0');
                        cost = min(ones, 4-ones);
                    } else if(pat[c]) {
                        int ones = (A[r][c]-'0') + (A[r][rev_c]-'0') + (A[rev_r][c]-'0');
                        cost = min(ones, 3-ones);
                    } else if(pat[rev_c]) {
                        int ones = (A[r][c]-'0') + (A[r][rev_c]-'0') + (A[rev_r][rev_c]-'0');
                        cost = min(ones, 3-ones);
                    } else {
                        int ones = (A[r][c]-'0') + (A[r][rev_c]-'0');
                        cost = min(ones, 2-ones);
                    }
                    v += cost;
                }
                update(r+1, k+1, v);

                // Case 3. Make opposite row palindrome.
                v = get(r, k);
                for(int c = 0; c < M/2; ++c) {
                    int rev_c = M-c-1;
                    int cost = 0;
                    if(pat[c] && pat[rev_c]) {
                        int ones = (A[r][c]-'0') + (A[r][rev_c]-'0') + (A[rev_r][c]-'0') + (A[rev_r][rev_c]-'0');
                        cost = min(ones, 4-ones);
                    } else if(pat[c]) {
                        int ones = (A[rev_r][c]-'0') + (A[rev_r][rev_c]-'0') + (A[r][c]-'0');
                        cost = min(ones, 3-ones);
                    } else if(pat[rev_c]) {
                        int ones = (A[rev_r][c]-'0') + (A[rev_r][rev_c]-'0') + (A[r][rev_c]-'0');
                        cost = min(ones, 3-ones);
                    } else {
                        int ones = (A[rev_r][c]-'0') + (A[rev_r][rev_c]-'0');
                        cost = min(ones, 2-ones);
                    }
                    v += cost;
                }
                update(r+1, k+1, v);

                // Case 4. Make this and opposite row palindrome.
                v = get(r, k);
                for(int c = 0; c < M/2; ++c) {
                    int rev_c = M-c-1;
                    if(pat[c] || pat[rev_c]) {
                        int ones = (A[r][c]-'0') + (A[r][rev_c]-'0') + (A[rev_r][c]-'0') + (A[rev_r][rev_c]-'0');
                        v += min(ones, 4-ones);
                    } else {
                        int ones_r = (A[r][c]-'0') + (A[r][rev_c]-'0');
                        int ones_revr = (A[rev_r][c]-'0') + (A[rev_r][rev_c]-'0');
                        int cost = min(ones_r, 2-ones_r) + min(ones_revr, 2-ones_revr);
                        v += cost;
                    }
                }
                update(r+1, k+2, v);
            }
        }
        return get(N/2, rowCount);
    }

    int minChange( vector <string> A_, int rowCount, int columnCount ) {
        A = A_;
        N = A.size();
        M = A[0].size();

        int ans = N*M;
        for(int pat = 0; pat < (1<<M); ++pat) {
            if(__builtin_popcount(pat) == columnCount) {
                ans = min(ans, calc(rowCount, bitset<14>(pat)));
                //cout << pat << ' ' << ans << endl;
            }
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
		for (int i=0; ; ++i) {
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
			string A[]                = {"0000"
,"1000"
,"1100"
,"1110"};
			int rowCount              = 2;
			int columnCount           = 2;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string A[]                = {"0000"
,"1000"
,"1100"
,"1110"};
			int rowCount              = 3;
			int columnCount           = 2;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string A[]                = {"01"
,"10"};
			int rowCount              = 1;
			int columnCount           = 1;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string A[]                = {"1110"
,"0001"};
			int rowCount              = 0;
			int columnCount           = 0;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string A[]                = {"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"};
			int rowCount              = 2;
			int columnCount           = 3;
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string A[]                = {"000000000000"
,"011101110111"
,"010001010101"
,"010001010101"
,"011101010101"
,"010101010101"
,"010101010101"
,"011101110111"
,"000000000000"
,"000000000000"};
			int rowCount              = 5;
			int columnCount           = 9;
			int expected__            = 14;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string A[]                = {"11111101001110"
,"11000111111111"
,"00010101111001"
,"10110000111111"
,"10000011010010"
,"10001101101101"
,"00101010000001"
,"10111010100100"
,"11010011110111"
,"11100010110110"
,"00100101010100"
,"01001011001000"
,"01010001111010"
,"10100000010011"};
			int rowCount              = 6;
			int columnCount           = 8;
			int expected__            = 31;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string A[]                = ;
			int rowCount              = ;
			int columnCount           = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string A[]                = ;
			int rowCount              = ;
			int columnCount           = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string A[]                = ;
			int rowCount              = ;
			int columnCount           = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
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
