//Name: Square
//Level: 2
//Category: 深さ優先探索,数え上げ,全探索,辞書式順序,DFS
//Note:

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int N, int pos, int lim, vector<int> &v) {
    if(N == 0) {
        cout << v[0];
        for(int i = 1; i < pos; ++i) {
            cout << ' ' << v[i];
        }
        cout << endl;
        return;
    }

    for(int i = min(lim,N); i >= 1; --i) {
        v[pos] = i;
        dfs(N-i, pos+1, i, v);
    }
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<int> arr(N, 0);
        dfs(N, 0, N, arr);
    }
    return 0;
}
