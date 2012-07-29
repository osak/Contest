#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<int> M;
vector<int> costs;
vector<int> mincosts;
int P;

int calc_cost(int n) {
    int depth = 0;
    for(; (n>>depth) > 1; ++depth) ;

    if(depth == P-1) {
        if(M[(n<<1)-(1<<P)]<=0 && M[((n<<1)+1)-(1<<P)]<=0) return 0;
        return costs[n];
    }

    int use = costs[n];
    int first = (n << (P-depth)) - (1<<P);
    int last = (((n+1) << (P-depth))-1) - (1<<P);
    //cerr << n << " " << first << " " << last << endl;

    for(int i = first; i <= last; ++i) {
        --M[i];
    }
    use += calc_cost(n<<1) + calc_cost((n<<1)+1);
    //cerr << n << "    use " << use << endl;

    int nonuse = 0;
    bool mustuse = false;
    bool allzero = true;
    for(int i = first; i <= last; ++i) {
        ++M[i];
        if(M[i] >= P-depth) mustuse = true;
        if(M[i] > 0) allzero = false;
    }
    if(mustuse) return use;
    if(allzero) return 0;

    nonuse = calc_cost(n<<1) + calc_cost((n<<1)+1);
    //cerr << n << " nonuse " << nonuse << endl;

    return min(use, nonuse);
}

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        cin >> P;

        M.clear();
        for(int i = 0; i < (1<<P); ++i) {
            int m;
            cin >> m;
            M.push_back(P-m);
        }
        reverse(M.begin(), M.end());
        costs.resize(1<<P);
        for(int i = (1<<P)-1; i >= 1; --i) {
            int c;
            cin >> c;
            costs[i] = c;
    //        cout << c << endl;
        }

        cout << "Case #" << C << ": " << calc_cost(1) << endl;
    }
}
