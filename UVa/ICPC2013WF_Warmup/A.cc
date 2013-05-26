#include <iostream>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

#define TIMES(i,n) for(int i = 0; (i) < (n); ++(i))
#define FOREACH(it,v) for(__typeof((v).begin()) it = (v).begin(); (it) != (v).end(); ++(it))

struct Tag {
    int A, B, K;

    Tag(int a, int b, int k) : A(a), B(b), K(k) {}
    bool operator <(const Tag &other) const {
        if(A != other.A) return A < other.A;
        else if(B != other.B) return B < other.B;
        return K != other.K;
    }

    bool operator ==(const Tag &other) const {
        return A == other.A && B == other.B && K == other.K;
    }
};

map<Tag,long long> memo;
long long calc(int A, int B, int K) {
    const Tag t(A, B, K);
    if(memo.count(t)) return memo[t];

    if(K == 0) return 1;
    long long size = 1LL<<K;

    long long ans = 0;
    if(A < size/2 && B >= size/2) {
        ans = calc(A, size/2-1, K-1)*2 + calc(0, B-size/2, K-1);
    } else if(B < size/2) {
        ans = calc(A, B, K-1)*2;
    } else if(A >= size/2) {
        ans = calc(A-size/2, B-size/2, K-1);
    } else {
        assert(false);
    }
    return memo[t] = ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    TIMES(CASE, N) {
        int A, B, K;
        cin >> K >> A >> B;
        cout << "Case " << (CASE+1) << ": " << calc(A-1, B-1, K) << endl;
    }
    return 0;
}
