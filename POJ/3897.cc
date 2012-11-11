//Name: Maze Stretching
//Level: 3
//Category: 二分探索,ダイクストラ,Dijkstra
//Note:

/*
 * Pの値を二分探索しながら最短経路長をダイクストラで求める．
 * オーダーはマップの横幅をMとして O(NM log NM)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

struct DistTag {
    static double P;
    int ver, hor;
    DistTag() {}
    DistTag(int ver, int hor) : ver(ver), hor(hor) {}

    double cost() const {
        return ver*P + hor;
    }

    bool operator <(const DistTag &other) const {
        return cost() < other.cost();
    }

    bool operator >(const DistTag &other) const {
        return cost() > other.cost();
    }
};
double DistTag::P;

struct Tag {
    int r, c;
    DistTag dt;
    Tag() {}
    Tag(int r, int c, const DistTag &dt) : r(r), c(c), dt(dt) {}

    bool operator <(const Tag &other) const {
        return dt.cost() > other.dt.cost(); //Reverse order
    }
};

DistTag memo[100][100];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        double L;
        int N;
        cin >> L >> N;
        cin.ignore();
        vector<string> field(N);
        pair<int,int> start;
        for(int i = 0; i < N; ++i) {
            getline(cin, field[i]);
            for(int j = 0; j < (int)field[i].size(); ++j) {
                if(field[i][j] == 'S') {
                    start = make_pair(i, j);
                }
            }
        }
        const int M = field[0].size();

        double left = 0, right = 1000;
        for(int step = 0; step < 32; ++step) {
            const double P = (left+right)/2;
            DistTag::P = P;
            for(int i = 0; i < 100; ++i) {
                for(int j = 0; j < 100; ++j) {
                    memo[i][j] = DistTag(10000, 10000);
                }
            }

            priority_queue<Tag> q;
            q.push(Tag(start.first, start.second, DistTag(0, 0)));
            memo[start.first][start.second] = DistTag(0, 0);
            double ans = 1e20;
            while(!q.empty()) {
                const Tag t = q.top();
                q.pop();
                if(memo[t.r][t.c] < t.dt) continue;
                if(field[t.r][t.c] == 'E') {
                    ans = t.dt.cost();
                    break;
                }

                const static int dr[] = {0, -1, 0, 1};
                const static int dc[] = {1, 0, -1, 0};
                for(int i = 0; i < 4; ++i) {
                    const int nr = t.r + dr[i];
                    const int nc = t.c + dc[i];
                    if(nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if(field[nr][nc] == '#') continue;
                    DistTag ndt = t.dt;
                    if(dr[i] != 0) ++ndt.ver;
                    else if(dc[i] != 0) ++ndt.hor;
                    if(ndt < memo[nr][nc]) {
                        memo[nr][nc] = ndt;
                        q.push(Tag(nr, nc, ndt));
                    }
                }
            }
            if(ans > L) right = P;
            else left = P;
        }
        printf("Case #%d: %.3f%%\n", CASE, (left+right)/2*100);
    }
    return 0;
}
