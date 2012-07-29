#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> height(1001, 0);
    int N;
    cin >> N;
    while(N--) {
        int h;
        cin >> h;
        height[h]++;
    }
    int highest = 0;
    int cnt =  0;
    for(int i = 1; i <= 1000; ++i) {
        if(height[i] > highest) highest = height[i];
        if(height[i]) cnt++;
    }

    cout << highest << " " << cnt << endl;
    return 0;
}
