// Name: GearsDiv1
// Level: 4
// Category: グラフ,Graph,探索,最小頂点被覆
// Note: SRM589 Div1 Medium

/*
 * それぞれの色について回転方向を決めると、同じ回転方向どうしが辺で結ばれることがないように
 * 頂点を削除していく問題になる。
 * すなわち、最小頂点被覆問題である。
 * 各点を順番に見ていき、その頂点を残すか消すか決めながら枝刈り探索をすると解ける。
 * 枝刈り条件は
 *   - 現在の最良解を超えた場合は無条件で打ち切り
 *   - 次数が1の頂点は消しても無意味なので必ず残す
 */
#include <string>
#include <vector>
#include <bitset>
#include <iostream>
using namespace std;

typedef bitset<50> Vec;

struct GearsDiv1 {
    int best;
    void dfs(int pos, vector<Vec> &eg, Vec alive, int acc) {
        const int N = eg.size();
        if(acc >= best) return;
        if(pos == N) {
            best = min(best, acc);
            return;
        }
        if(!alive[pos]) {
            dfs(pos+1, eg, alive, acc);
            return;
        }
        Vec neigh = eg[pos] & alive;
        if(neigh.count() > 1) {
            // erase this
            Vec next(alive);
            next[pos] = 0;
            dfs(pos+1, eg, next, acc+1);
        }
        {
            // keep this
            Vec next(alive);
            next ^= neigh;
            dfs(pos+1, eg, next, acc+neigh.count());
        }
    }

    void gen_graph(int r, int g, int b, const string &color, const vector<string> &graph, vector<Vec> &eg) {
        const int N = graph.size();
        for(int i = 0; i < N; ++i) {
            const int ic = (color[i] == 'R') ? r : (color[i] == 'G') ? g : b;
            for(int j = 0; j < N; ++j) {
                if(i == j) continue;
                const int jc = (color[j] == 'R') ? r : (color[j] == 'G') ? g : b;
                if(ic == jc && graph[i][j] == 'Y') {
                    eg[i][j] = eg[j][i] = 1;
                }
            }
        }
    }

    int getmin( string color, vector <string> graph ) {
        const int N = graph.size();

        best = N*2;
        for(int r = 0; r <= 1; ++r) {
            for(int g = 0; g <= 1; ++g) {
                for(int b = 0; b <= 1; ++b) {
                    //cout << r << ' ' << g << ' ' << b << endl;
                    vector<Vec> eg(N);
                    Vec alive;
                    gen_graph(r, g, b, color, graph, eg);
                    for(int i = 0; i < N; ++i) {
                        alive[i] = 1;
                    }
                    dfs(0, eg, alive, 0);
                }
            }
        }
        return best;
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
			string color              = "RGB";
			string graph[]            = {"NYY","YNY","YYN"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string color              = "RGBR";
			string graph[]            = {"NNNN","NNNN","NNNN","NNNN"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string color              = "RGBR";
			string graph[]            = {"NYNN","YNYN","NYNY","NNYN"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string color              = "RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG";
			string graph[]            = {"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",
 "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",
 "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",
 "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",
 "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",
 "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",
 "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",
 "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",
 "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",
 "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",
 "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",
 "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",
 "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",
 "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",
 "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",
 "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",
 "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",
 "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",
 "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",
 "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",
 "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",
 "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			string color              = "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR";
			string graph[]            = {
"NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNY",
"YNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNYN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNY",
"YNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",};
			int expected__            = 25;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
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
