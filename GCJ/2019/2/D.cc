//Name:
//Level:
//Category:
//Note:

/**
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007LL;

vector<vector<long long>> matmul(vector<vector<long long>> &m1, vector<vector<long long>> &m2) {
    const int N = m1.size();
    const int M = m2[0].size();
    const int K = m2.size();

    vector<vector<long long>> res(N, vector<long long>(M));

    for(int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < K; ++k) {
                res[i][j] += m1[i][k] * m2[k][j] % MOD;
            }
        }
    }
    return res;
}

void modpow(vector<vector<long long>> &matrix, int x) {
    const int N = matrix.size();
    vector<vector<long long>> buf(N, vector<long long>(N, 0));

    for (int i = 0; i < N; ++i) {
        buf[i][i] = 1;
    }

    while (x > 0) {
        if (x & 1) {
            buf = matmul(buf, matrix);
        }
        matrix = matmul(matrix, matrix);
        x /= 2;
    }

    matrix.swap(buf);
}

long long calcLead(const vector<vector<long long>> &mat, const vector<long long> &g, bool real = false) {
    long long res = 0;
    for (int i = 0; i < mat.size(); ++i) {
        if (g[i] > 0) {
            if (real) {
                res += mat[0][i] * g[i] % MOD;
            } else {
                res += mat[0][i];
            }
        }
    }
    return res;
}

void printMat(const vector<vector<long long>> &mat) {
    for (int i = 0; i < mat.size(); ++i) {
        for(int j = 0; j < mat[i].size(); ++j) {
            cout << mat[i][j] << ' ';
        }
        cout << endl;
    }
}

string solve() {
   int M;
   cin >> M;

   vector<vector<long long>> matrix(M, vector<long long>(M));
   for (int i = 0; i < M; ++i) {
       int r1, r2;
       cin >> r1 >> r2;
       matrix[r1-1][i] += 1;
       matrix[r2-1][i] += 1;
   }
   vector<long long> g(M);
   for (int i = 0; i < M; ++i) {
       cin >> g[i];
   }

   vector<vector<long long>> nolead = matrix;
   for (int i = 0; i < M; ++i) {
       nolead[i][0] = 0;
   }
   nolead[0][0] = 1;

   long long maxLead = 0;
   vector<vector<long long>> buf = nolead;
   for (int t = 0; t < M*2; ++t) {
       buf = matmul(buf, nolead);
       maxLead = max(maxLead, calcLead(buf, g));
   }
   for (int t = 0; t < M*2; ++t) {
       buf = matmul(buf, nolead);
       if (calcLead(buf, g) > maxLead) return "UNBOUNDED";
   }

   long long lead = calcLead(buf, g, true);
   if (lead == 0) return to_string(0);
   buf = matrix;

   for (int t = 0; t < M*2; ++t) {
       buf = matmul(buf, matrix);
       if(buf[0][0] > 1) return "UNBOUNDED";
   }
   return to_string(lead % MOD);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": " << solve() << endl;
    }
    return 0;
}
