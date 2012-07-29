#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

struct Tag {
    int pat;
    int sat;

    Tag() : pat(0) {}
};

long long memo[1<<16];
Tag tags[100];
int N;

long long rec(int cur) {
    if(memo[cur] != 0) return memo[cur];

    long long mx = 0;
    for(int i = 0; i < N; ++i) {
        if((cur & tags[i].pat) == 0) {
            int next = cur|tags[i].pat;
            long long tmp = rec(next) + tags[i].sat;
            mx = max(mx, tmp);
        }
    }

    memo[cur] = mx;
    return mx;
}

int main() {
    ios::sync_with_stdio(0);
    while(true) {
        cin >> N;
        if(!N) break;
        memset(memo, 0, sizeof(memo));
        for(int i = 0; i < N; ++i) {
            int M, L;
            cin >> M >> L;
            Tag t;
            for(int j = 0; j < M; ++j) {
                int a, b;
                cin >> a >> b;
                a -= 6;
                b -= 6;
                for(int k = a; k < b; ++k) {
                    t.pat |= (1<<k);
                }
            }
            t.sat = L;
            tags[i] = t;
        }

        cout << rec(0) << endl;
    }
    return 0;
}
