//Name: Resistance
//Level: 3
//Category: 連立方程式
//Note:

/*
 * 各点の電圧を変数にして，キルヒホッフの電流則を使って連立方程式を立てる．
 * このときv_1 = 1.0V, v_N = 0.0Vとすると，v_1から流れ出す電流量から
 * 等価抵抗の値が求められる．
 *
 * オーダーはガウスの消去法を用いてO(N^3)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

double resistor[100][100];
double voltage[100];

// ax = b を解く。解 x は b に入る。
// N < M のときは 0 = 0 みたいな式を追加して N == M にする。
// O(M^2 N)
template <class T>
bool gaussian_elimination(vector<vector<T> >& a, vector<T>& b)/*{{{*/
{
  const int N = a.size();
  const int M = a[0].size();
  // assert(N >= M)

  for (int i = 0, p = 0; i < M; i++, p++) {
    int q;
    for (q = p; q < N && a[q][i] == 0; q++);
    if (q == N) {
      --p;
      continue;
    }
    swap(a[i], a[q]);
    swap(b[i], b[q]);

    // const T r = 1.0/a[i][i];
    // const T r = a[i][i].inverse();
    const T r = 1.0 / a[i][i];
    for (int k = i; k < M; k++) {
      a[i][k] = a[i][k] * r;
    }
    b[i] = b[i] * r;

    for (int j = 0; j < N; j++) {
      if (j == i) {
        continue;
      }
      const T t = a[j][i];
      for (int k = i; k < M; k++) {
        a[j][k] = a[j][k] - t * a[i][k];
      }
      b[j] = b[j] - t * b[i];
    }
  }

  for (int i = 0; i < M; i++) {
    if (a[i][i] == 0 && b[i] != 0) {
      // no solution
      return false;
    }
  }
  return true;
}/*}}}*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    while(cin >> N >> M) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                resistor[i][j] = 0;
            }
        }
        for(int i = 0; i < M; ++i) {
            int X, Y, R;
            cin >> X >> Y >> R;
            resistor[X-1][Y-1] += 1.0/R;
            resistor[Y-1][X-1] += 1.0/R;
        }
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                resistor[i][j] = 1.0 / resistor[i][j];
            }
        }

        vector<vector<double> > matrix(N, vector<double>(N, 0));
        vector<double> voltage(N, 0);
        voltage[0] = 1.0;
        voltage[N-1] = 0.0;
        matrix[0][0] = 1;
        matrix[N-1][N-1] = 0;
        for(int node = 1; node < N-1; ++node) {
            for(int other = 0; other < N; ++other) {
                if(resistor[node][other] > 0) {
                    double inv = 1.0 / resistor[node][other];
                    matrix[node][node] -= inv;
                    matrix[node][other] += inv;
                }
            }
        }
        gaussian_elimination(matrix, voltage);
        double current = 0;
        for(int node = 0; node < N; ++node) {
            if(resistor[0][node] > 0) {
                current += (voltage[0] - voltage[node]) / resistor[0][node];
            }
        }
        printf("%.2f\n", 1.0 / current);
    }
    return 0;
}
