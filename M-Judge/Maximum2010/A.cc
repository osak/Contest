#include <iostream>
#include <map>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        map<string, int> tbl;
        for(int i = 0; i < N; ++i) {
            string name, t;
            cin >> name >> t;
            int h,m,s;
            sscanf(t.c_str(), "%d:%d:%d", &h, &m, &s);
            tbl[name] = h*3600+m*60+s;
        }
        
        int M;
        int t = 0;
        cin >> M;
        for(int i = 0; i < M; ++i) {
            string name;
            int num;

            cin >> name >> num;
            t += tbl[name]*num;
        }
        if(t % 3600 == 0) t += ((t-1)/3600)*60*10;
        else t += (t/3600)*60*10;
        if(t >= 24*3600) cout << "IMPOSSIBLE" << endl;
        else printf("%02d:%02d:%02d\n", t/3600, t%3600/60, t%60);
    }
    return 0;
}
