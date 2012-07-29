#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Tag {
    int kind;
    int top, left, bottom, right;

    Tag() {}
    Tag(int k, int t, int l, int b, int r) : kind(k), top(t), left(l), bottom(b), right(r) {}

    int count(int t, int l, int b, int r) const {
        int ans = 0;

        //not intersect
        if(t > bottom || l > right || b < top || r < left) return 0;

        //clip
        if(t < top) t = top;
        if(l < left) l = left;
        if(b > bottom) b = bottom;
        if(r > right) r = right;

        if(top == bottom) {
            return max(0, r-l+1);
        }
        else if(left == right) {
            return max(0, b-t+1);
        }

        if(t <= top && top <= b) ans += r-l+1;
        if(l <= left && left <= r) ans += b-t+1;
        if(t <= bottom && bottom <= b) ans += r-l+1;
        if(l <= right && right <= r) ans += b-t+1;

        //corner
        if(t == top && l == left) --ans;
        if(t == top && r == right) --ans;
        if(b == bottom && l == left) --ans;
        if(b == bottom && r == right) --ans;

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);

    int N, M;
    while(cin >> N >> M) {
        int cnt = (min(N, M)+1)/2;

        vector<Tag> tags;
        Tag t(0, 0, 0, N-1, M-1);
        for(int i = 0; i < cnt; ++i) {
            cin >> t.kind;
            tags.push_back(t);
            t.top++; t.left++;
            t.bottom--; t.right--;
        }

        int Q;
        int kinds[251];
        cin >> Q;
        while(Q--) {
            int T, L, B, R;
            cin >> T >> L >> B >> R;

            fill(kinds, kinds+251, 0);
            for(int i = 0; i < tags.size(); ++i) {
                kinds[tags[i].kind] += tags[i].count(T, L, B, R);
            }

            int TOTAL = 0, INDEX = 0, COUNT = 0;
            for(int i = 0; i < 251; ++i) {
                if(kinds[i]) ++TOTAL;
                if(kinds[i] > COUNT) {
                    COUNT = kinds[i];
                    INDEX = i;
                }
            }

            cout << TOTAL << ' ' << INDEX << ' ' << COUNT << endl;
        }
    }

    return 0;
}
