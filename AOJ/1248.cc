#include <iostream>
#include <vector>

using namespace std;

#define UPDATE do {\
 int w = A*cntA + B*cntB;\
    if(cntA+cntB < ansA+ansB || (cntA+cntB == ansA+ansB && w < ansW)) {\
        ansA = cntA; ansB = cntB; ansW = w;\
    }\
} while(0)

int main() {
    while(true) {
        int A, B, D;
        cin >> A >> B >> D;
        if(!A && !B && !D) break;

        int lim = 2000000000/A;
        int cur = 0;
        int ansA = 100000, ansB = 100000;
        int ansW = A*ansA + B*ansB;

        for(int cntA = 0; cntA <= lim; ++cntA) {
            if(cur <= D && (D-cur) % B == 0) {
                int cntB = (D-cur) / B;
                UPDATE;
            }
            if((A*cntA+D) % B == 0) {
                int cntB = (A*cntA+D) / B;
                UPDATE;
            }
            if(A*cntA-D > 0 && (A*cntA-D) % B == 0) {
                int cntB = (A*cntA-D) / B;
                UPDATE;
            }
            if(D-A*cntA > 0 && (D-A*cntA) % B == 0) {
                int cntB = (D-A*cntA) / B;
                UPDATE;
            }
            cur += A;
            lim = ansA + ansB;
        }

        cout << ansA << ' ' << ansB << endl;
    }

    return 0;
}
