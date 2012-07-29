#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <complex>

using namespace std;

typedef complex<int> Point;

int cross(const Point &p1, const Point &p2, const Point &p3) {
    const Point v1 = p2 - p1;
    const Point v2 = p3 - p1;
    return v1.real()*v2.imag() - v1.imag()*v2.real();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand(time(NULL));
    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int N;
        cin >> N;
        vector<int> orders(N);
        for(int i = 0; i < N-1; ++i) {
            cin >> orders[i];
            --orders[i];
        }

        vector<Point> peaks(N);
        bool found = false;
        int cnt = 0;
        while(!found) {
            for(int i = 0; i < N; ++i) {
                peaks[i] = Point(i, rand()%10000+1);
            }

            found = true;
            for(int i = 0; i < N-1; ++i) {
                for(int j = i+1; j < N; ++j) {
                    int cr = cross(peaks[i], peaks[orders[i]], peaks[j]);
                    //cout << cr << endl;
                    if(j != orders[i] && cr > 0) {
                        found = false;
                        goto next;
                    }
                }
            }
next:
            if(++cnt == 1000000) break;
            ;
        }

endcase:
        cout << "Case #" << CASE << ": ";
        if(!found) {
            cout << "Impossible";
        }
        else {
            for(int i = 0; i < N; ++i) {
                cout << peaks[i].imag() << ' ';
            }
        }
        cout << endl;
    }

    return 0;
}
