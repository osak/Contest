//Name: Intersection of Rectangles
//Level: 1
//Category: 当たり判定,やるだけ
//Note:

#include <iostream>
#include <utility>

using namespace std;

typedef pair<double, double> Point;

int main() {
    while(true) {
        Point ps[4];
        for(int i = 0; i < 4; ++i)
            cin >> ps[i].first >> ps[i].second;
        if(cin.eof()) break;

        if(ps[0].first <= ps[3].first && ps[1].first >= ps[2].first && ps[0].second <= ps[3].second && ps[1].second >= ps[2].second) 
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
