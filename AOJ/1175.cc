//Name: And Then. How Many Are There?
//Level: 2
//Category: 探索,幅優先探索,BFS
//Note:

/*
 * 円盤の数は高々24枚なので，状態数は2^24．
 * それぞれの円盤について上に乗っているものを管理し，上に乗っているものが全て取り除かれている同じ色のペアを取り除いていく．
 * これをメモ化しながら幅優先探索すればよい．
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

inline int sq(int n) {
    return n*n;
}

struct Circle {
    int x, y, r, c;

    bool collide(const Circle &other) const {
        return sq(x-other.x) + sq(y-other.y) < sq(r+other.r);
    }
};

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Circle> circles(N);
        vector<int> blocking(N, 0);
        for(int i = 0; i < N; ++i) {
            Circle &circle = circles[i];
            cin >> circle.x >> circle.y >> circle.r >> circle.c;
            for(int j = 0; j < i; ++j) {
                if(circle.collide(circles[j])) {
                    blocking[i] |= 1<<j;
                }
            }
        }

        int ans = 0;
        vector<unsigned char> memo(1<<N, 0);
        queue<int> q;
        q.push((1<<N)-1);
        memo[q.front()] = 1;
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            ans = max(ans, N - __builtin_popcount(cur));

            for(int i = 0; i < N; ++i) {
                if((blocking[i] & cur) != 0) continue;
                if((cur & (1<<i)) == 0) continue;
                for(int j = 0; j < i; ++j) {
                    if(circles[i].c != circles[j].c) continue;
                    if((blocking[j] & cur) != 0) continue;
                    if((cur & (1<<j)) == 0) continue;

                    int mask = (1<<i) | (1<<j);
                    int next = cur & ~mask;
                    if(memo[next]) continue;
                    memo[next]  = 1;
                    q.push(next);
                }
            }
        }
        
        cout << ans << endl;
    }

    return 0;
}
