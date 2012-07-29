#include <iostream>
#include <vector>
#include <string>

using namespace std;

inline void update(int &a, int v) {
    if(a < v) a = v;
}

int main() {
    ios::sync_with_stdio(0);

    int N, M;
    while(cin >> N >> M) {
        cin.ignore();

        int cost = 0;
        while(N--) {
            vector<string> books(M);
            for(int i = 0; i < M; ++i) {
                getline(cin, books[i]);
            }

            int maxval = 1;
            vector<int> dp(M, 1);
            for(int i = 0; i < M; ++i) {
                for(int j = 0; j < i; ++j) {
                    if(books[i] >= books[j]) update(dp[i], dp[j]+1);
                    update(maxval, dp[i]);
                }
            }

            cost += M - maxval;
        }

        cout << cost << endl;
    }

    return 0;
}
