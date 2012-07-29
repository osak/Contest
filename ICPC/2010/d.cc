#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <algorithm>

using namespace std;

typedef complex<double> Point;
typedef complex<int> Point_i;

struct Piece {
  double g;
  int weight;
  int minx, maxx;
  vector<Piece*> children;
};

double fill(vector<string> &v, int x, int y, char c, vector<Point_i> &has, vector<int> &under) {
  //cout << x << ' ' << y << ' ' << c << endl;
  const int dx[] = {1, -1, 0, 0};
  const int dy[] = {0, 0, 1, -1};

  if(x < 0 || v[0].size() <= x || y < 0 || v.size() <= y) return 0;
  if(v[y][x] != c) return 0;

  v[y][x] = '%';
  double g = x+0.5;

  for(int i = 0; i < 4; ++i) {
    g += fill(v, x+dx[i], y+dy[i], c, has, under);
  }

  if(y > 0 && v[y-1][x] != '.' && v[y-1][x] != '#' && v[y-1][x] != c) {
    has.push_back(Point_i(x, y-1));
  }
  if(y < v.size()-1 && v[y+1][x] == '#') {
    under.push_back(x);
  }
  v[y][x] = '%';
  return g;
}

Piece* getPiece(vector<string> &v, int x, int y) {
  //cout << x << ' ' << y << endl;
  char c = v[y][x];
  vector<Point_i> has;
  vector<int> under;
  double g = fill(v, x, y, c, has, under);
  Piece *p = new Piece;
  p->g = g/4;
  //cout << p->g << endl;
  p->weight = 4;
  for(int i = 0; i < v.size(); ++i) {
    for(int j = 0; j < v[0].size(); ++j) {
      if(v[i][j] == '%') v[i][j] = '#';
    }
  }
  for(int i = 0; i < has.size(); ++i) {
    char c = v[has[i].imag()][has[i].real()];
    if(c != '#' && c != '.') {
      Piece *c = getPiece(v, has[i].real(), has[i].imag());
      p->children.push_back(c);
    }
  }

  int minx = under[0];
  int maxx = under[0];
  for(int i = 0; i < under.size(); ++i) {
    minx = min(minx, under[i]);
    maxx = max(maxx, under[i]);
  }
  p->minx = minx;
  p->maxx = maxx+1;
  //cout << p->minx << ' ' << p->maxx << endl;
  return p;
}

bool stable(Piece *p) {
  for(int i = 0; i < p->children.size(); ++i) {
    if(!stable(p->children[i])) return false;
  }
  double w = 0, g = 0;
  int minx = p->minx, maxx = p->maxx;
  for(int i = 0; i < p->children.size(); ++i) {
    w += p->children[i]->weight;
    g += p->children[i]->g * p->children[i]->weight;
    //minx = min(p->children[i]->minx, minx);
    //maxx = max(p->children[i]->maxx, maxx);
  }
  w += p->weight;
  g += p->g * p->weight;

  g /= w;
  //cout << g << endl;

  p->g = g;
  p->weight = w;
  return (minx < p->g && p->g < maxx);
}


int main() {
  while(true) {
    int W, H;
    cin >> W >> H;
    if(!W && !H) break;

    vector<string> v;
    for(int i = 0; i < H; ++i) {
      string l;
      cin >> l;
      v.push_back(l);
    }
    string s;
    for(int i = 0; i < W; ++i) {
      s += '#';
    }
    v.push_back(s);
    Piece *root;
    for(int x = 0; x < W; ++x) {
      if(v[H-1][x] != '.') {
        root = getPiece(v, x, H-1);
        break;
      }
    }
    //root->minx = -1;
    //root->maxx = W+10;

    cout << (stable(root) ? "STABLE" : "UNSTABLE") << endl;
  }
  return 0;
}
