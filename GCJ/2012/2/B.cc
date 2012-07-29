#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdlib>

using namespace std;

typedef complex<double> Point;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand(time(NULL));
    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int N, W, L;
        cin >> N >> W >> L;
        vector<int> radius(N);
        for(int i = 0; i < N; ++i) {
            cin >> radius[i];
        }

        vector<Point> centers(N);
        while(true) {
            for(int i = 0; i < N; ++i) {
                centers[i] = Point(double(rand())/RAND_MAX*W, double(rand())/RAND_MAX*L);
            }
            //cout << "restart" << endl;
            for(int step = 0; step <= 1000; ++step) {
                bool ok = true;
                vector<Point> vecs(N, Point(0, 0));
                for(int i = 0; i < N; ++i) {
                    for(int j = 0; j < i; ++j) {
                        Point vec = centers[i]-centers[j];
                        if(abs(vec) <= radius[i]+radius[j]) {
                            vecs[i] += vec*0.5;
                            vecs[j] -= vec*0.5;
                            ok = false;
                        }
                    }
                }
                if(ok) goto endcase;
                for(int i = 0; i < N; ++i) {
                    centers[i] += vecs[i];
                    if(centers[i].real() < 0) centers[i].real() = 0;
                    if(centers[i].real() > W) centers[i].real() = W;
                    if(centers[i].imag() < 0) centers[i].imag() = 0;
                    if(centers[i].imag() > L) centers[i].imag() = L;
                }
            }
        }

endcase:
        cout << "Case #" << CASE << ": ";
        cout.setf(ios::fixed);
        cout.precision(2);
        for(int i = 0; i < N; ++i) {
            cout << centers[i].real() << ' ' << centers[i].imag() << ' ';
        }
        cout << endl;
    }

    return 0;
}
