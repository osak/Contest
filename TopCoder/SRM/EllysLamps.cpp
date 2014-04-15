//Name: EllysLamps
//Level: 4
//Category: 動的計画法,DP
//Note:

/**
 * あるランプはその前後1つにしか影響せず、特に、ひとつ左より前のランプには全く影響を及ぼさないことから、
 * DPによる解法が考えられる。
 *
 * まず、同じスイッチを2回押すと無効化されることより、全てのスイッチがどのような性質をもっているかは
 * あらかじめ知っておくことができる。
 * したがって、与えられた配置の中で、最小コストを実現することは可能である。
 * このときの最小コストの最大値を求めるので、配置については全てのパターンを試して最悪のものを選ぶ。
 * その中で、スイッチを押すか押さないかは最小コストになるように決める。
 *
 * あるスイッチを見たとき、これを押した段階で確定できるのは左ランプの状態のみである。
 * したがって、スイッチiを押した時に加算されるコストは、ランプi-1に由来するものになる。
 * 
 * 普通に考えると(位置, 直前のランプの状態, 現在のランプの状態)の3つ組が状態になり、
 * 現在のランプが左右にどう影響するかで4通りを試すようなDPになる。
 * しかし、この方法では、スイッチiからの影響が未知のままでスイッチi-1を押すか押さないかを決めることになり、うまく行かない。
 *
 * そこで、スイッチiを押すかどうかを決める時点で、全ての影響が考慮されるような遷移を考える。
 * つまり、この段階で、スイッチi+1が左側にどう影響するかを決め打つ。
 * このとき、影響が決まればスイッチi+1が押された時、押されなかったときのそれぞれで、ランプiがコストにどう影響するかを
 * あらかじめ計算できるようになる。
 * よって、それぞれの分岐をあらかじめ計算しておき、次の状態として伝搬させ、スイッチi+1を押すかどうか決めた時点で
 * 対応する分岐のコストを加算するようにすればよい。
 *
 * 最後のランプだけは右側に影響しないため、特別に扱う。
 * オーダーはO(N * 2^5)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// dp[idx][cur][prev_press][prev_not_press]
int dp[55][2][2][2];
const int INF = 55;
class EllysLamps {
public:
    string lamps;
    int N;
    int calc(int pos, int lit, int prev_press, int prev_not_press) {
        int &ans = dp[pos][lit][prev_press][prev_not_press];
        if(ans != INF) return ans;

        ans = 0;
        if(pos == N-1) {
            ans =  min(
                    // Press
                    prev_press + (lit ^ 1),
                    // Not press
                    prev_not_press + lit);
        } else {
            const int next = lamps[pos+1] == 'Y' ? 1 : 0;
            for(int tr = 0; tr < 2; ++tr) { // affect to right
                for(int ar = 0; ar < 2; ++ar) { // affect from right
                    int cost = min(
                            // Press
                            calc(pos+1, next ^ tr, lit ^ 1 ^ ar, lit ^ 1) + prev_press,
                            // Not press
                            calc(pos+1, next, lit ^ ar, lit) + prev_not_press);
                    ans = max(ans, cost);
                }
            }
        }
        return ans;
    }

    int getMin( string lamps_ ) {
        for(int i = 0; i < 55; ++i) {
            for(int j = 0; j < 2; ++j) {
                for(int k = 0; k < 2; ++k) {
                    for(int l = 0; l < 2; ++l) {
                        dp[i][j][k][l] = INF;
                    }
                }
            }
        }

        lamps = lamps_;
        N = lamps.size();
        return calc(0, lamps[0] == 'Y' ? 1 : 0, 0, 0);
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
			string lamps              = "YNNYN";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string lamps              = "NNN";
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string lamps              = "YY";
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string lamps              = "YNYYYNNNY";
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string lamps              = "YNYYYYNYNNYYNNNNNNYNYNYNYNNYNYYYNY";
			int expected__            = 13;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string lamps              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string lamps              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string lamps              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = EllysLamps().getMin(lamps);
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
