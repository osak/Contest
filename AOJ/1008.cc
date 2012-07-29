#include <iostream>
#include <map>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        map<int, int> cnt;
        for(int i = 0; i < N; ++i) {
            int num;
            cin >> num;
            cnt[num]++;
        }
        int ans = -1;
        for(map<int,int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
            if(it->second > N/2) {
                ans = it->first;
                break;
            }
        }
        if(ans == -1) cout << "NO COLOR" << endl;
        else cout  << ans << endl;
    }
    return 0;
}
