#include <cstdio>
#include <set>
#include <vector>
#include <string>

using namespace std;

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    vector<set<int> > cards(K);
    for(int j = 0; j < K; ++j) {
        for(int i = 0; i < N/2; ++i) {
            int n;
            scanf("%d", &n);
            cards[j].insert(n);
        }
    }

    vector<int> cnt(K, 0);
    string str;
    for(int i = 1; i <= N; ++i) {
        bool ok = true;
        for(int j = 0; j < K; ++j) {
            if(cnt[j] >= N*3/8 && cards[j].count(i)) {
                ok = false;
                break;
            }
        }
        if(ok) {
            for(int j = 0; j < K; ++j) {
                if(cards[j].count(i)) cnt[j]++;
            }
        }
        str += ok ? '1' : '0';
    }

    printf("%s\n", str.c_str());
}
