#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <set>

using namespace std;

#define TIMES(i,n) for(int i = 0; (i) < (n); ++(i))
#define FOREACH(it,v) for(__typeof((v).begin()) it = (v).begin(); (it) != (v).end(); ++(it))

struct Tag {
    int a, b, step;
    Tag(int a, int b, int s) : a(a), b(b), step(s) {}

    bool operator <(const Tag &other) const {
        if(a != other.a) return a < other.a;
        if(b != other.b) return b < other.b;
        return step < other.step;
    }

    bool operator ==(const Tag &other) const {
        return a == other.a && b == other.b && step == other.step;
    }
};

long long val(int x, const vector<int> &roots) {
    long long res = 1;
    FOREACH(it, roots) {
        res *= x - *it;
    }
    return res;
}

int valsgn(int x, const vector<int> &roots) {
    long long res = val(x, roots);
    return (res == 0) ? 0 : (res < 0) ? -1 : 1;
}

inline bool in_range(int a, int x, int b) {
    return a <= x && x <= b;
}

set<Tag> memo;
int calc(int a, int b, int step, const vector<int> &roots) {
    const Tag tag(a, b, 1);
    if(memo.count(tag)) return 0;
    memo.insert(tag);
    if(step == 7) return 1;

    int res = 1;
    const int sgna = valsgn(a, roots);
    { // case [2a-b, b)
        const int prev_a = 2*a - b;
        if(in_range(0, prev_a, 10000) && prev_a < b && prev_a < a) {
            if(valsgn(prev_a, roots)*sgna > 0) res += calc(prev_a, b, step+1, roots);
        }
    }
    { // case [a, 2b-a)
        const int prev_b = 2*b - a;
        if(in_range(0, prev_b, 10000) && prev_b > a && prev_b > b) {
            if(valsgn(prev_b, roots)*sgna < 0) res += calc(a, prev_b, step+1, roots);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    while(N--) {
        string line;
        cin >> line;
        FOREACH(it, line) {
            if(!isdigit(*it)) *it = ' ';
        }
        istringstream is(line);
        vector<int> roots;
        while(!is.eof()) {
            int r;
            is >> r;
            roots.push_back(r);
        }
        roots.pop_back();
        int R;
        cin >> R;

        memo.clear();
        int ans = 0;
        TIMES(a, 10000+1) {
            const int b = 2*R - a;
            if(a < b && b <= 10000) {
                int sgn = valsgn(a, roots)*valsgn(b, roots);
                if(sgn < 0) {
                    ans += calc(a, b, 1, roots);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
