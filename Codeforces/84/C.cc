#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Tag {
    bool valid;
    int four, seven;

    Tag() : valid(false) {}
    Tag(int f, int s) : four(f), seven(s), valid(true) {}

    bool operator < (const Tag &other) const {
        if(valid != other.valid) return valid;

        int sum = four+seven;
        int osum = other.four+other.seven;
        if(sum != osum) return sum < osum;
        return four > other.four;
    }
};

int main() {
    int N;
    cin >> N;

    vector<Tag> dp(N+1);
    dp[0] = Tag(0, 0);
    for(int i = 1; i <= N; ++i) {
        if(i >= 4 && dp[i-4].valid) {
            Tag next(dp[i-4].four+1, dp[i-4].seven);
            dp[i] = min(dp[i], next);
        }
        if(i >= 7 && dp[i-7].valid) {
            Tag next(dp[i-7].four, dp[i-7].seven+1);
            dp[i] = min(dp[i], next);
        }
    }

    if(dp[N].valid) {
        for(int i = 0; i < dp[N].four; ++i) cout << '4';
        for(int i = 0; i < dp[N].seven; ++i) cout << '7';
        cout << endl;
    }
    else {
        cout << -1 << endl;
    }

    return 0;
}
