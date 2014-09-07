//Name: Sliding Window
//Level: 3
//Category: スライド最小値,スライド最大値,Sliding window minimum,Sliding window maximum
//Note:

/**
 * Typical sliding window minimum/maximum problem.
 * For minimum value, maintain a deque that holds the candidates in decreasing order.
 * When window slides left for one unit and the minimum value is the rightmost number of the window,
 * it will be popped out and the next candidate become the new minimum.
 * Same for maximum value.
 *
 * Complexity is O(N), assuming pop/push on deque is O(1).
 */
#include <cstdio>
#include <deque>

using namespace std;

int maxbuf[1000000];
int minbuf[1000000];
bool solve() {
    int N, K;
    if(scanf("%d %d", &N, &K) == EOF) return false;
    if(!N && !K) return false;

    deque<int> mxq, mnq, history;
    for(int i = 0; i < N; ++i) {
        int v;
        scanf("%d", &v);
        if(i >= K) {
            const int last = history.front();
            history.pop_front();
            if(mxq.front() == last) mxq.pop_front();
            if(mnq.front() == last) mnq.pop_front();
        }
        while(!mxq.empty() && mxq.back() < v) mxq.pop_back();
        mxq.push_back(v);
        while(!mnq.empty() && mnq.back() > v) mnq.pop_back();
        mnq.push_back(v);
        if(i >= K-1) {
            maxbuf[i-K+1] = mxq.front();
            minbuf[i-K+1] = mnq.front();
        }
        history.push_back(v);
    }
    for(int i = 0; i < N-K+1; ++i) {
        if(i > 0) printf(" ");
        printf("%d", minbuf[i]);
    }
    puts("");
    for(int i = 0; i < N-K+1; ++i) {
        if(i > 0) printf(" ");
        printf("%d", maxbuf[i]);
    }
    puts("");
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
