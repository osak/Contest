#include <iostream>
#include <vector>
#include <climits>
#include <stack>
#include <cstdio>

using namespace std;

typedef long long LL;

vector<int> v[2];
vector<vector<int> > product;

int n;

int dp[800][800];

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        product.clear();
        v[0].clear();
        v[1].clear();
        cin >> n;
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < n; ++j) {
                int num;
                cin >> num;
                v[i].push_back(num);
            }
        }

        product.resize(n);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                product[i].push_back(v[0][i] * v[1][j]);
            }
        }

        for(int i = 0; i < n; ++i) {

        }
    }
}
