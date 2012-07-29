#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> Range; // represents [first, second]

int countOf(const Range &r) {
    return r.second - r.first + 1;
}

int check(int R, const Range &r) {
    if(R < r.first) return 0;
    if(r.second <= R) return countOf(r);
    return countOf(r)-countOf(Range(R+1, r.second));
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        int M, P, Q, R;
        cin >> M >> P >> Q >> R;

        vector<Range> cards;
        cards.push_back(Range(1, N));
        while(M--) {
            int x, y;
            cin >> x >> y;

            vector<Range> next;
            int cnts[] = {N-y, y-x, x};
            int cntidx = 0;
            int end = cards.size();
            for(int i = cards.size()-1; i >= 0; --i) {
                int cnt = countOf(cards[i]);
                if(cnts[cntidx]-cnt <= 0) {
                    int rem = cnts[cntidx];
                    next.push_back(Range(cards[i].second-rem+1, cards[i].second));
                    for(int j = i+1; j < end; ++j) {
                        if(countOf(cards[j]) > 0) next.push_back(cards[j]);
                    }
                    cards[i].second -= rem;
                    end = i+1;
                    if(++cntidx == 4) {
                        break;
                    }
                    else {
                        ++i;
                        continue;
                    }
                }
                cnts[cntidx] -= cnt;
            }
            cards = next;
        }
        /*
        for(int i = 0; i < cards.size(); ++i) {
            cout << '(' << cards[i].first << ", " << cards[i].second << ')' << endl;
        }
        */
        int ans = 0;
        int currCount = 0;
        for(int i = 0; i < cards.size(); ++i) {
            int cnt = countOf(cards[i]);
            Range r = cards[i];

            bool ok = false;
            if(currCount < P && currCount+cnt >= P) {
                r.first += P-currCount-1;
                ok = true;
                //cout << i << ' ' << ans << endl;
            }
            if(currCount < Q && currCount+cnt >= Q) {
                r.second -= currCount+cnt-Q;
                ok = true;
                //cout << i << ' ' << ans << endl;
            }
            if(P <= currCount+cnt && currCount+cnt <= Q) ok = true;

            if(ok) ans += check(R, r);
            currCount += cnt;
        }
        cout << ans << endl;
    }
}
