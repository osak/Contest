#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Tag {
    int i, j, k, a;
};

int main() {
    ios::sync_with_stdio(false);

    int X, Y, Z;
    int dx, dy, dz;
    cin >> X >> Y >> Z;
    dx = ceil(sqrt(X)); dy = ceil(sqrt(Y)); dz = ceil(sqrt(Z));
    vector<vector<vector<int> > > v(X, vector<vector<int> >(Y, vector<int>(Z, 0)));
    vector<vector<vector<int> > > kd(ceil((double)X/dx), vector<vector<int> >(ceil((double)Y/dy), vector<int>(ceil((double)Z/dz), 0)));

    for(int z = 0; z < Z; ++z)
        for(int y = 0; y < Y; ++y)
            for(int x = 0; x < X; ++x) {
                cin >> v[x][y][z];
                kd[x/dx][y/dy][z/dz] += v[x][y][z];
            }

    int Q;
    cin >> Q;
    while(Q--) {
        string s;
        cin >> s;
        if(s == "+") {
            int i, j, k, a;
            cin >> i >> j >> k >> a;
            i--; j--; k--;
            v[i][j][k] += a;
            kd[i/dx][j/dy][k/dz] += a;
        }
        else if(s == "-") {
            int i, j, k, a;
            cin >> i >> j >> k >> a;
            i--; j--; k--;
            v[i][j][k] -= a;
            kd[i/dx][j/dy][k/dz] -= a;
        }
        else {
            int i1, j1, k1, i2, j2, k2;
            cin >> i1 >> j1 >> k1 >> i2 >> j2 >> k2;

            i1--; j1--; k1--;
            i2--; j2--; k2--;
            int si1 = ceil((double)i1/dx), sj1 = ceil((double)j1/dy), sk1 = ceil((double)k1/dz);
            int si2 = (i2+1)/dx-1, sj2 = (j2+1)/dy-1, sk2 = (k2+1)/dz-1;
            cout << si1 << ' ' << sj1 << ' ' << sk1 << endl;
            cout << si2 << ' ' << sj2 << ' ' << sk2 << endl;
            int sum = 0;
            for(int si = si1; si <= si2; ++si)
                for(int sj = sj1; sj <= sj2; ++sj)
                    for(int sk = sk1; sk <= sk2; ++sk) {
                        sum += kd[si][sj][sk];
                    }

            for(int i = i1; i <= i2; ++i) {
                if(i/dx == si1) {
                    i = dx*(si2+1)-1;
                    continue;
                }
                for(int j = j1; j <= j2; ++j) {
                    if(j/dy == sj1) {
                        j = dy*(sj2+1)-1;
                        continue;
                    }
                    for(int k = k1; k <= k2; ++k) {
                        if(k/dz == sk1) {
                            k = dz*(sk2+1)-1;
                            continue;
                        }
                        sum += v[i][j][k];
                    }
                }
            }
            cout << sum << endl;
        }
    }

    return 0;
}
