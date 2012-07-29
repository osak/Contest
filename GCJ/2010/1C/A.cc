#include <iostream>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;

int main() {
    int cases;
    cin >> cases;

    for(int C = 1; C <= cases; ++C) {
        int N;
        cin >> N;

        vector<pair<int, int> > wires;
        for(int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            wires.push_back(make_pair(a, b));
        }
        int cnt = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < i; ++j) {
                if((wires[i].first-wires[j].first)*(wires[i].second-wires[j].second) < 0) ++cnt;
            }
        }

        printf("Case #%d: %d\n", C, cnt);
    }
    return 0;
}
