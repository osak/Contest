#include <iostream>

using namespace std;

void print(const char *str, int ok, int cnt) {
    if(cnt)
        cout << str << ' ' << (int)(ok*100.0/cnt) << endl;
    else
        cout << str << ' ' << "no guest" << endl;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int cnt[3] = {0}, ok[3] = {0};
        for(int i = 0; i < N; ++i) {
            int h, m, ms;
            char colon;
            cin >> h >> colon >> m >> ms;

            int t = ms - m;
            if(t < 0) t += 60;

            int ldm = -1;
            if(11 <= h && h < 15) ldm = 0;
            else if(18 <= h && h < 21) ldm = 1;
            else if(21 <= h || h < 2) ldm = 2;

            if(ldm != -1) {
                if(t <= 8) ok[ldm]++;
                cnt[ldm]++;
            }
        }

        print("lunch", ok[0], cnt[0]);
        print("dinner", ok[1], cnt[1]);
        print("midnight", ok[2], cnt[2]);
    }
    return 0;
}
