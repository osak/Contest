#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

void print_matrix(const vector<vector<int> > &v) {
    for(int r = 0; r < v.size(); ++r) {
        for(int c = 0; c < v[r].size(); ++c) {
            cout << v[r][c] << ' ';
        }
        cout << endl;
    }
}

vector<vector<int> > mult_matrix(const vector<vector<int> > &a, const vector<vector<int> > &b) {
    int R = a.size();
    int C = b[0].size();
    int K = a[0].size();
    vector<vector<int> > res(R, vector<int>(C, 0));
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            for(int k = 0; k < K; ++k) res[i][j] ^= a[i][k]&b[k][j];
        }
    }

    return res;
}

int main() {
    while(true) {
        int M, N, D;
        cin >> M >> N >> D;
        if(!M && !N && !D) break;

        vector<vector<int> > v(N, vector<int>(M));
        for(int r = 0; r < N; ++r) 
            for(int c = 0; c < M; ++c)
                cin >> v[r][c];

        vector<vector<int> > mat(M*N, vector<int>(M*N, 0));
        for(int r = 0; r < N; ++r) {
            for(int c = 0; c < M; ++c) {
                const int a = r*M + c;
                mat[a][a] = 1;
                for(int dr = -D; dr <= D; ++dr) {
                    if(r+dr < 0 || N <= r+dr) continue;
                    int dc = D - abs(dr);
                    if(c+dc < M) {
                        const int b = (r+dr)*M + (c+dc);
                        mat[b][a] = 1;
                    }
                    if(dc > 0 && c-dc >= 0) {
                        const int b = (r+dr)*M + (c-dc);
                        mat[b][a] = 1;
                    }
                }
            }
        }
        vector<vector<int> > mat_org = mat;
        vector<vector<int> > inv(M*N, vector<int>(M*N, 0));
        for(int i = 0; i < inv.size(); ++i) inv[i][i] = 1;
        for(int r = 0; r < M*N; ++r) {
            if(mat[r][r] == 0) {
                //Find pivot
                for(int nr = r+1; nr < M*N; ++nr) {
                    if(mat[nr][r] == 1) {
                        swap(mat[nr], mat[r]);
                        swap(inv[nr], inv[r]);
                        break;
                    }
                }
            }
            for(int nr = 0; nr < M*N; ++nr) {
                if(nr == r) continue;
                if(mat[nr][r] == 1) {
                    for(int c = 0; c < M*N; ++c) {
                        mat[nr][c] ^= mat[r][c];
                        inv[nr][c] ^= inv[r][c];
                    }
                }
            }
        }

        //print_matrix(mat);
        bool ok = true;
        for(int r = 0; r < M*N; ++r) {
            bool all0 = true;
            for(int c = 0; c < M*N; ++c) {
                if(mat[r][c] == 1) {
                    all0 = false;
                    break;
                }
            }
            if(all0) {
                int cnt = 0;
                for(int c = 0; c < M*N; ++c) {
                    if(inv[r][c]) {
                        cnt ^= v[c/M][c%M];
                    }
                }
                if(cnt != 0) {
                    ok = false;
                    break;
                }
            }
        }

        cout << (ok?1:0) << endl;
    }

    return 0;
}
