//Name: XorCards
//Level: 4
//Category: XOR,連立方程式
//Note: SRM590 Div1 Medium

/*
 * 数値群からいくつか選んでXORをとることは、n_iの2進数表記を列ベクトルと見て
 *   (n_0 n_1 n_2 ... n_N) (x_0 x_1 x_2 ... x_N)
 * を2元体上で計算することと等しい。
 * （ここで、最初の行列は最大のビット数LとしてL✕Nの行列になる）
 *
 * 一方、数値がlimitを超えないという条件は、たとえばlimit = 10110(2進表記)とすると
 * 結果が
 *   ・10110
 *   ・1010*
 *   ・100**
 *   ・0****
 * のどれかのパターンになることを表す。
 * これは、limitで1が立っているbitを0にすると、それ以下は任意に決定できることによる。
 *
 * ここで、最初の方程式表記との対応を考えると、たとえば100**に対応するパターン数は
 * 先頭を100とするような方程式の解の個数と等しくなる。
 * すなわち、n_0, n_1, …… の3ビット目以上のみを用いた行列を使って
 *   (n_0 n_1 n_2 ... n_N) x = (1 0 0)^t
 * を解き、この方程式がもつ解の個数を数えればよい。
 * （左辺の行列は(L-2)✕Nである）
 *
 * オーダーはO(L^3N)。
 * ただし、L = max(log(n_i), log(limit)) である。
 */
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

class XorCards {
public:
    int bitlen(long long n) {
        int res = 0;
        while((1LL<<res) < n) ++res;
        return res+1;
    }

    vector<vector<int> > build(const vector<long long> &number, long long limit) {
        const int N = number.size();
        int len = bitlen(limit);
        for(long long ll : number) {
            len = max(len, bitlen(ll));
        }
        if(len == 0) len = 1;
        vector<vector<int> > matrix(len, vector<int>(N+1, 0));
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < len; ++j) {
                if((1LL<<j) & number[i]) {
                    matrix[j][i] = 1;
                }
            }
        }
        for(int i = 0; i < len; ++i) {
            if((1LL<<i) & limit) matrix[i][N] = 1;
        }
        return matrix;
    }

    long long solve(vector<vector<int> > &matrix) {
        const int R = matrix.size();
        const int C = matrix[0].size();
        vector<unsigned char> has(R, 0);
        int free_cnt = C-1;
        for(int r = 0; r < R; ++r) {
            int c = 0;
            for(c = 0; c < C-1; ++c) {
                if(matrix[r][c] == 1) break;
            }
            if(c >= C-1) continue;
            has[r] = 1;
            --free_cnt;
            for(int rr = r+1; rr < R; ++rr) {
                if(matrix[rr][c] == 1) {
                    for(int cc = c; cc < C; ++cc) {
                        matrix[rr][cc] ^= matrix[r][cc];
                    }
                }
            }
        }
        for(int r = 0; r < R; ++r) {
            if(!has[r] && matrix[r][C-1] == 1) return 0;
        }
        return 1LL << free_cnt;
    }

    long long numberOfWays( vector<long long> number, long long limit ) {
        long long ans = 0;
        while(true) {
            vector<vector<int> > matrix = build(number, limit);
            /*
            for(int i = 0; i < matrix.size(); ++i) {
                for(int j = 0; j < matrix[0].size(); ++j) {
                    cout << matrix[i][j] << ' ';
                }
                cout << endl;
            }
            */
            ans += solve(matrix);
            if(limit == 0) break;
            int shift = 0;
            while((limit & 1) == 0) {
                limit >>= 1;
                ++shift;
            }
            limit ^= 1;
            for(long long &ll : number) {
                ll >>= shift;
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) { 
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
			long long number[]        = {1, 2};
			long long limit           = 2;
			long long expected__      = 3;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long number[]        = {5, 5};
			long long limit           = 3;
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long number[]        = {1, 2, 3, 4, 5, 6, 7};
			long long limit           = 5;
			long long expected__      = 96;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long number[]        = {123, 456, 789, 147, 258, 369, 159, 357};
			long long limit           = 500;
			long long expected__      = 125;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long number[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long limit           = 1000000000000000LL;
			long long expected__      = 4294967296LL;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long number[]        = {1000000000000000LL, 999999999999999LL};
			long long limit           = 65535;
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			long long number[]        = {1LL,2LL,4LL,8LL,16LL,32LL,64LL,128LL,256LL,512LL,1024LL,2048LL,4096LL,8192LL,16384LL,32768LL,65536LL,131072LL,262144LL,524288LL,1048576LL,2097152LL,4194304LL,8388608LL,16777216LL,33554432LL,67108864LL,134217728LL,268435456LL,536870912LL,1073741824LL,2147483648LL,4294967296LL,8589934592LL,17179869184LL,34359738368LL,68719476736LL,137438953472LL,274877906944LL,549755813888LL,1099511627776LL,2199023255552LL,4398046511104LL,8796093022208LL,17592186044416LL,35184372088832LL,70368744177664LL,140737488355328LL,281474976710656LL,562949953421312LL};
			long long limit           = 1LL<<51LL;
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
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
