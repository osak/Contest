//Name: MaxMinTreeGame
//Level: 2
//Category: 貪欲,Greedy
//Note: SRM603 Div1 Easy

/**
 * あるノードiを選び、それ以上のコストが得られるかを考える。
 * 先手がどこかの辺を切り、残った木の中でc[i]未満の葉があれば、後手はそれだけを残すように動く。
 * したがって、先手が辺を切る時点で、全ての葉はc[i]以上でなければならない。
 * そのような切り方が可能なのは、iの子である部分木のうち最小の葉がc[i]未満であるようなものが、高々1つしかないときである。
 * 初手でiを葉にするような切り方ができなくても、上の条件を満たしていれば、c[i]以上のスコアを取ることは可能である。
 *
 * （実は、これは最大の葉のスコアを選ぶことと等しい）
 *
 * オーダーはO(N^2)。
 */
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class MaxMinTreeGame {
public:
    int child_max(const vector<vector<int>> &graph, int v, int parent, const vector<int> &costs) {
        int ans = graph[v].size() == 1 ? costs[v] : 0;
        for(int n : graph[v]) {
            if(n == parent) continue;
            ans = max(ans, child_max(graph, n, v, costs));
        }
        return ans;
    }

    bool check(const vector<vector<int>> &graph, int v, const vector<int> &costs) {
        if(graph[v].size() == 1) return true;
        const int threshold = costs[v];
        int cnt = 0;
        for(int n : graph[v]) {
            //cout << v << ' ' << n << endl;
            if(child_max(graph, n, v, costs) < threshold) {
                ++cnt;
            }
        }
        return cnt <= 1;
    }

    int findend( vector <int> edges, vector <int> costs ) {
        const int N = edges.size();
        vector<vector<int>> graph(N+1);
        for(int i = 0; i < N; ++i) {
            graph[i+1].push_back(edges[i]);
            graph[edges[i]].push_back(i+1);
        }

        int ans = -1;
        for(int i = 0; i < N+1; ++i) {
            if(check(graph, i, costs)) ans = max(ans, costs[i]);
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
			int edges[]               = {0};
			int costs[]               = {4,6};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int edges[]               = {0,1};
			int costs[]               = {4,6,5};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int edges[]               = {0,1,2,3};
			int costs[]               = {0,1,0,1,0};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int edges[]               = {0,0,0};
			int costs[]               = {5,1,2,3};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int edges[]               = {0,0};
			int costs[]               = {3,2,5};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int edges[]               = ;
			int costs[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int edges[]               = ;
			int costs[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int edges[]               = ;
			int costs[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
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
