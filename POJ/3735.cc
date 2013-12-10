//Name: Training little cats
//Level: 3
//Category: 行列累乗,疎行列,Sparse Matrix
//Note:

/**
 * それぞれの操作は行列で表されるので、行列の累乗計算で答えは求められる。
 * しかし、行列サイズが最大100なので、100×100行列を愚直に累乗計算するとTLEしてしまう。
 * そこで、行列が疎であることに着目し、疎行列に特化した処理で行列乗算を行うことで高速化する。
 *
 * オーダーはO(A^2 log R log M)。
 * ただしAは行列中で非ゼロの要素数、Rは1行中にある非ゼロの要素数。
 * log Rは行列計算の途中経過をmapで管理していることによる。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

struct SparseMatrix {
    typedef pair<int,LL> Cell;
    typedef vector<Cell> Row;
    vector<Row> rows;
    int R, C;

    SparseMatrix(int R, int C) : rows(R), R(R), C(C) {}

    void add(int r, int c, LL val) {
        assert(0 <= r && r < R);
        assert(0 <= c && c < C);
        Row &row = rows[r];
        const int N = row.size();
        TIMES(i, N) {
            if(row[i].first == c) {
                row[i].second += val;
                return;
            }
        }
        row.push_back(Cell(c, val));
    }

    LL get(int r, int c) const {
        TIMES(i, rows[r].size()) {
            if(rows[r][i].first == c) return rows[r][i].second;
        }
        return 0;
    }

    SparseMatrix& operator *=(const SparseMatrix &sm) {
        assert(C == sm.R);

        vector<Row> new_rows(R);
        TIMES(r, R) {
            const Row &row = rows[r];
            map<int,LL> col_acc;
            TIMES(i, row.size()) {
                const Row &smrow = sm.rows[row[i].first];
                TIMES(j, smrow.size()) {
                    const int col = smrow[j].first;
                    col_acc[col] += row[i].second * smrow[j].second;
                }
            }
            for(map<int,LL>::const_iterator it = col_acc.begin(); it != col_acc.end(); ++it) {
                if(it->second != 0) new_rows[r].push_back(Cell(it->first, it->second));
            }
        }
        rows.swap(new_rows);
        C = sm.C;
        return *this;
    }
};

bool solve() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    if(!N && !M && !K) return false;

    SparseMatrix mat(N+1, N+1);
    TIMES(i, N+1) {
        mat.add(i, i, 1);
    }
    TIMES(_, K) {
        char cmd;
        scanf(" %c", &cmd);
        if(cmd == 'g') {
            int i;
            scanf(" %d", &i);
            mat.add(i, 0, 1);
        } else if(cmd == 'e') {
            int i;
            scanf(" %d", &i);
            mat.rows[i].clear();
        } else if(cmd == 's') {
            int i, j;
            scanf(" %d %d", &i, &j);
            swap(mat.rows[i], mat.rows[j]);
        }
    }
    SparseMatrix res(N+1, N+1);
    TIMES(i, N+1) {
        res.add(i, i, 1);
    }
    while(M > 0) {
        if(M & 1) {
            res *= mat;
        }
        mat *= mat;
        M >>= 1;
    }
    TIMES(i, N) {
        if(i != 0) printf(" ");
        printf("%lld", res.get(i+1, 0));
    }
    puts("");
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
