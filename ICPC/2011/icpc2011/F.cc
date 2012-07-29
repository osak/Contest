#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double PI = atan2(+0.0, -0.0);

struct ko
{
  double theta;
  P center;
  double r;
  ko(double t, const P& c, double s)
    : theta(t), center(c), r(s)
  {}
};

struct cmp_right
{
  bool operator()(const pair<P,int>& p, const pair<P,int>& q) const
  {
    if (p.first.real() == q.first.real()) {
      return p.first.imag() < q.first.imag();
    } else {
      return p.first.real() > q.first.real();
    }
};

struct cmp_left
{
  bool operator()(const pair<P,int>& p, const pair<P,int>& q) const
  {
    if (p.real() == q.real()) {
      return p.imag() < q.imag();
    } else {
      return p.real() > q.real();
    }
};

vector<ko> solve(int R, vector<P> ps, int W, int H, bool f)
{
  vector<pair<double,int> > ws(4);
  for (int i = 0; i < 4; i++) {
    ws[i] = make_pair(acos(ps[i].real()*ps[i].real()/(abs(ps[i]))), i);
  }
  if (f) {
    swap(ws[0].second, ws[2].second);
    swap(ws[1].second, ws[3].second);
  }
  sort(ws.begin(), ws.end());
  if (f) {
    reverse(ws.begin(), ws.end());
  }
  vector<P> qs(4);
  for (int i = 0; i < 4; i++) {
    qs[i] = ps[ws[i].second];
  }

  bool b = true;
  for (int i = 0; i < 4; i++) {
    if (abs(ps[i]) < R) {
      b = false;
    }
  }
  if (b) {
    return vector<ko>(1, ko(2*PI, P(0,0), R));
  }

  if (abs(qs[0]) > R) {
    return vector<ko>(1, ko(asin(qs[0].imag() / R), P(0,0), R));
  }

  vector<ko> ans;
  const double r = abs(qs[0]);
  printf("qs[0]=(%f,%f)\n", qs[0].real(), qs[0].imag());
  double a = acos(abs(qs[0].imag()) / r);
  ans.push_back(ko(PI/2 - a, P(0, 0), R));

  ans.push_back(ko(a, qs[0], R - r));
  const bool flag = ws[0].second == 1 || ws[0].second == 3;
  if (flag) {
    if (r + H > R) {
      return ans;
    }
  } else {
    if (r + W > R) {
      return ans;
    }
  }

  if (flag) {
    ans.push_back(ko(R-r-H, qs[1], PI/2.0));
  } else {
    ans.push_back(ko(R-r-W, qs[1], PI/2.0));
  }
  if (r+H+W < R) {
    return ans;
  }

  ans.push_back(ko(R-r-H-W, qs[2], PI/2.0));
  if (flag) {
    if (r+H+W+H > R) {
      return ans;
    }
  } else {
    if (r+H+W+W > R) {
      return ans;
    }
  }

  if (flag) {
    ans.push_back(ko(R-r-H-W-H, qs[3], PI/2.0));
  } else {
    ans.push_back(ko(R-r-H-W-W, qs[3], PI/2.0));
  }
  return ans;
}

int main()
{
  int len, x1, y1, x2, y2;
  while (cin >> len >> x1 >> y1 >> x2 >> y2 && len != 0) {
    vector<P> ps(4);
    ps[0] = P(x2, y1);
    ps[1] = P(x2, y2);
    ps[2] = P(x1, y2);
    ps[3] = P(x1, y1);
    vector<ko> right = solve(len, ps, x2-x1, y2-y1, false);
    vector<ko> left = solve(len, ps, x2-x1, y2-y1, true);
    for (int i = 0; i < right.size(); i++) {
      printf("right (%f,%f) r=%f theta=%f\n", right[i].center.real(), right[i].center.imag(), right[i].r, right[i].theta);
    }
    for (int i = 0; i < left.size(); i++) {
      printf("left (%f,%f) r=%f theta=%f\n", left[i].center.real(), left[i].center.imag(), left[i].r, left[i].theta);
    }
    puts("");
  }
  return 0;
}
