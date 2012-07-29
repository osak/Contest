#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Rect {
    //x1 < x2, y1 < y2
    int x1, y1, x2, y2;
    int num;

    Rect() {}
    Rect(int num, int x1, int y1, int x2, int y2) : num(num), x1(x1), y1(y1), x2(x2), y2(y2) {
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
    }

    bool operator < (const Rect &other) const {
        if(x1 != other.x1) return x1 < other.x1;
        return y1 < other.y1;
    }
};

int readthem(vector<Rect> &rects, vector<int> &order, int idx) {
    if(rects.size() == 0) return idx;
    /*
    cout << "To read: " << endl;
    for(int i = 0; i < rects.size(); ++i) {
        cout << rects[i].num << endl;
    }
    */

    sort(rects.begin(), rects.end());
    order[rects[0].num] = idx++;

    int yb = rects[0].y2;
    int xl = INT_MAX;
    for(int i = 1; i < rects.size(); ++i) {
        if(rects[i].y1 < yb && yb < rects[i].y2) xl = min(xl, rects[i].x1);
    }

    vector<Rect> subset;
    vector<Rect> remain;
    for(int i = 1; i < rects.size(); ++i) {
        if(rects[i].y2 <= yb && rects[i].x2 <= xl) subset.push_back(rects[i]);
        else remain.push_back(rects[i]);
    }
    idx = readthem(subset, order, idx);
    return readthem(remain, order, idx);
}

int main() {
    bool first = true;
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Rect> rects(N);
        for(int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            rects[i] = Rect(i, x1, y1, x2, y2);
        }

        vector<int> order(N);
        readthem(rects, order, 1);

        if(!first) cout << endl;
        first = false;
        for(int i = 0; i < N; ++i) cout << order[i] << endl;
    }
    return 0;
}
