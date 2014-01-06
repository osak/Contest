//Name: PairsOfStrings
//Level: 4
//Category: 数学,数え上げ,動的計画法,DP
//Note: SRM603 Div1 Medium

/**
 * AとBが条件を満たすのは、Aの巡回シフトがBと一致するようなときである。
 *
 * このとき、シフト幅はNの約数だけを考えればよい。
 * シフト幅dで一致するようなパターンでは、自由に決められるのは先頭のd文字だけである。
 * したがって単純計算ではd^k通りのパターンが存在するが、これはdの約数であるようなシフト幅d'のものを重複して数えている。
 * これは、約数を小さい方から処理していき、ちょうど幅dのものの個数を覚えておくことで除去できる。
 *
 * オーダーは約数の個数Dに対して、O(D^2)。
 */
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL MOD = 1000000007LL;
const int LIM = (int)sqrt(MOD);

class PairsOfStrings {
public:
    LL modpow(LL a, int x) {
        LL res = 1;
        LL ord = a;
        while(x > 0) {
            if(x & 1) {
                res *= ord;
                res %= MOD;
            }
            ord *= ord;
            ord %= MOD;
            x /= 2;
        }
        return res;
    }

   int getNumber( int n, int k ) {
        vector<bool> is_prime(LIM+1, true);
        is_prime[0] = is_prime[1] = false;

        map<LL,int> factor;
        int tmp = n;
        for(int i = 2; i <= min(LIM, tmp); ++i) {
            if(is_prime[i]) {
                while(tmp > 1 && tmp % i == 0) {
                    factor[i]++;
                    tmp /= i;
                }
                if(tmp == 1) break;
                for(LL j = (LL)i * i; j <= min(LIM, tmp); j += i) {
                    is_prime[j] = false;
                }
            }
        }
        if(tmp > 1) factor[tmp]++;

        vector<LL> divisors;
        divisors.push_back(1);
        for(auto p : factor) {
            vector<LL> buf;
            for(const auto d : divisors) {
                LL cur = d;
                for(int i = 0; i <= p.second; ++i) {
                    buf.push_back(cur);
                    cur *= p.first;
                }
            }
            buf.swap(divisors);
        }
        sort(divisors.begin(), divisors.end());

        LL res = 0;
        map<LL,LL> memo;
        for(auto d : divisors) {
            LL pat = modpow(k, d);
            for(auto din : divisors) {
                if(din >= d) break;
                if(d % din == 0) {
                    pat -= memo[din];
                    pat += MOD;
                    pat %= MOD;
                }
            }
            res += d * pat;
            res %= MOD;
            memo[d] = pat;
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
			int n                     = 2;
			int k                     = 2;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 3;
			int k                     = 2;
			int expected__            = 20;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			int k                     = 4;
			int expected__            = 184;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 6;
			int k                     = 2;
			int expected__            = 348;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 100;
			int k                     = 26;
			int expected__            = 46519912;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
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
