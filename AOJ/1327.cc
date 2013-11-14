//Name: One-Dimensional Cellular Automaton
//Level: 2
//Category: 行列累乗
//Note:

/**
 * 遷移は行列で表すことができる。
 * これをダブリングを使ってT乗すればよい。
 *
 * オーダーはO(N^3 log N)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

typedef vector<int> MatRow;
typedef vector<vector<int>> Matrix;

void matmul(Matrix &a, const Matrix &b, int N, int M) {
    Matrix tmp(N, MatRow(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                tmp[i][j] += a[i][k] * b[k][j];
                tmp[i][j] %= M;
            }
        }
    }
    a = tmp;
}

bool solve() {
    int N, M, A, B, C, T;
    cin >> N >> M >> A >> B >> C >> T;
    if(!N && !M && !A && !B && !C && !T) return false;
    vector<int> init(N, 0);
    for(int i = 0; i < N; ++i) {
        cin >> init[i];
    }
    Matrix mat(N, MatRow(N, 0)), unit(N, MatRow(N, 0));
    for(int i = 0; i < N; ++i) {
        if(i > 0) mat[i][i-1] = A;
        mat[i][i] = B;
        if(i+1 < N) mat[i][i+1] = C;
    }
    for(int i = 0; i < N; ++i) {
        unit[i][i] = 1;
    }
    Matrix res(unit), ord(mat);
    while(T > 0) {
        if(T & 1) {
            matmul(res, ord, N, M);
        }
        matmul(ord, ord, N, M);
        T /= 2;
    }

    for(int i = 0; i < N; ++i) {
        int s = 0;
        for(int j = 0; j < N; ++j) {
            s += res[i][j] * init[j];
            s %= M;
        }
        if(i > 0) cout << " ";
        cout << s;
    }
    cout << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
