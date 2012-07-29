#include <iostream>
#include <vector>

using namespace std;

//Verified PKU 2524
int getroot(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    else return (roots[i] = getroot(roots[i], roots));
}

//Verified PKU 2524
bool unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = getroot(i, roots);
    j = getroot(j, roots);
    if(i == j) return false;

    if(levels[i] < levels[j]) {
        roots[i] = j;
    }
    else {
        roots[j] = i;
        if(levels[i] == levels[j]) ++levels[i];
    }
    return true;
}


int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<vector<int> > v(N, vector<int>(31, 0));
        vector<int> roots(N);
        vector<int> levels(N, 0);
        for(int i = 0; i < N; ++i) {
            int M;
            cin >> M;
            for(int j = 0; j < M; ++j) {
                int n;
                cin >> n;
                v[i][n] = 1;
            }
            roots[i] = i;
        }

        int ans = -1;
        for(int i = 1; i <= 30; ++i) {
            int node = -1;
            for(int n = 0; n < N; ++n) {
                if(v[n][i]) {
                    if(node == -1) node = n;
                    else unite(node, n, roots, levels);
                }
            }

            int root = getroot(0, roots);
            bool ok = true;
            for(int n = 1; n < N; ++n) {
                if(root != getroot(n, roots)) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                ans = i;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
