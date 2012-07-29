//Name: Quality Checking
//Level: 2
//Category: シミュレーション
//Note:

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Test {
    int a, b, c, r;
    Test() {}
    Test(int aa, int bb, int cc, int rr) : a(aa), b(bb), c(cc), r(rr) {}
};

bool operator < (const Test &t1, const Test &t2) {
    return t1.r > t2.r;
}

int main() {
    while(true) {
        int a, b, c, n;
        cin >> a >> b >> c >> n;
        if(!a && !b && !c) break;

        vector<int> parts(a+b+c+1, 2);
        vector<Test> tests;

        while(n--) {
            int i, j, k, r;
            cin >> i >> j >> k >> r;
            tests.push_back(Test(i, j, k, r));
        }

        sort(tests.begin(), tests.end());

        for(int i = 0; i < tests.size(); ++i) {
            int pa, pb, pc;
            pa = tests[i].a;
            pb = tests[i].b;
            pc = tests[i].c;
            if(tests[i].r == 1) {
                parts[tests[i].a] = parts[tests[i].b] = parts[tests[i].c] = 1;
            }
            else {
                int cnt = 0;
                if(parts[pa] == 1) ++cnt;
                if(parts[pb] == 1) ++cnt;
                if(parts[pc] == 1) ++cnt;
                if(cnt == 2) {
                    if(parts[pa] == 2) parts[pa] = 0;
                    if(parts[pb] == 2) parts[pb] = 0;
                    if(parts[pc] == 2) parts[pc] = 0;
                }
            }
        }

        for(int i = 1; i < parts.size(); ++i) {
            cout << parts[i] << endl;
        }
    }

    return 0;
}

