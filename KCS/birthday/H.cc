#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

typedef complex<double> P;
const double EPS = 1e-7;
const double PI = acos(-1);

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

// O(N)
vector<P> convex(vector<P>& ps)/*{{{*/
{
  sort(ps.begin(), ps.end(), [](const P &a, const P &b) {
          if(fabs(a.real() - b.real()) < EPS) {
            return a.imag() < b.imag();
          }
          return a.real() < b.real();
          });
  const int N = ps.size();
  vector<P> ch(2*N);
  int k = 0;
  for (int i = 0; i < N; i++) {
    while (k >= 2 && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  for (int i = N-2, t = k+1; i >= 0; i--) {
    while (k >= t && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  ch.resize(k-1);
  return ch;
}/*}}}*/

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;

    vector<P> points;
    for(int i = 0; i < N; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        const P c(x, y);
        const P rot = polar(1.0, 2*PI / 10000);
        P v(r, 0);
        for(int j = 0; j < 10000; ++j) {
            points.push_back(c + v);
            v *= rot;
        }
    }
    vector<P> cvx = convex(points);
    const int S = cvx.size();
    double ans = 0;
    for(int i = 0; i < S; ++i) {
        ans += abs(cvx[i] - cvx[(i+1)%S]);
    }
    printf("%.8f\n", ans);
    return 0;
}
