#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rect {
    int x, y;

    Rect() {}
    Rect(int x, int y) : x(x), y(y) {}
};

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Rect> v;
        v.push_back(Rect(0, 0));
        
        int dt[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        while(--N) {
            int n, d;
            cin >> n >> d;
            Rect r = v[n];
            r.x += dt[d][0];
            r.y += dt[d][1];
            v.push_back(r);
        }
        int l, r, t, b;
        l = t = N;
        r = b = 0;
        for(int i = 0; i < v.size(); ++i) {
            const Rect &rc = v[i];
            l = min(l, rc.x); r = max(r, rc.x);
            t = min(t, rc.y); b = max(b, rc.y);
        }
        cout << (r-l+1) << ' ' << (b-t+1) << endl;
    }
    return 0;
}
