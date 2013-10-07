// Paste me into the FileEdit configuration dialog

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

inline bool contain(int a, int x, int b) {
    return a < x && x <= b;
}

struct Range {
    int start, end;
    Range(int s, int e) : start(s), end(e) {}
    bool cross(const Range &other) const {
        return 
            contain(start, other.start, end) ||
            contain(start, other.end, end) ||
            contain(other.start, start, other.end) ||
            contain(other.start, end, other.end);
    }
};

int to_idx(char c) {
    if(c == 'L') return 0;
    else return 1;
}

const string IMPOSSIBLE = "Impossible";

class FoxAndChess {
public:
   string ableToMove( string begin, string target ) {
       vector<Range> moves[2];
       auto bit = begin.begin();
       auto tit = target.begin();
       while(true) {
           while(bit != begin.end() && *bit == '.') ++bit;
           while(tit != target.end() && *tit == '.') ++tit;
           if(bit == begin.end() || tit == target.end()) break;
           if(*bit != *tit) return IMPOSSIBLE;
           int idx = to_idx(*bit);
           const int pos_b = distance(begin.begin(), bit);
           const int pos_t = distance(target.begin(), tit);
           if(idx == 0 && (pos_b < pos_t)) return IMPOSSIBLE;
           if(idx == 1 && (pos_b > pos_t)) return IMPOSSIBLE;
           moves[idx].push_back(Range(pos_b, pos_t));
           ++bit;
           ++tit;
       }
       if(bit != begin.end() || tit != target.end()) {
           return IMPOSSIBLE;
       }
       for(const Range &r : moves[0]) {
           for(const Range &r2 : moves[1]) {
               if(r.cross(r2)) return IMPOSSIBLE;
           }
       }
       return "Possible";
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
			string begin              = "R...";
			string target             = "..R.";
			string expected__         = "Possible";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string begin              = "..R.";
			string target             = "R...";
			string expected__         = "Impossible";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string begin              = ".L.R.R.";
			string target             = "L...R.R";
			string expected__         = "Possible";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string begin              = ".L.R.";
			string target             = ".R.L.";
			string expected__         = "Impossible";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string begin              = "LRLLRLRLLRLLRLRLRL";
			string target             = "LRLLRLRLLRLLRLRLRL";
			string expected__         = "Possible";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string begin              = "L";
			string target             = ".";
			string expected__         = "Impossible";

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string begin              = ;
			string target             = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string begin              = ;
			string target             = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string begin              = ;
			string target             = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FoxAndChess().ableToMove(begin, target);
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
