#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    while(true) {
        int N, W;
        cin >> N >> W;
        if(!N && !W) break;

        vector<int> hist(11, 0);
        int rightmost = 0;
        int maxval = 0;

        for(int i = 0; i < N; ++i) {
            int v;
            cin >> v;
            hist[v/W]++;
        }

        for(int i = 0; i < hist.size(); ++i) {
            if(hist[i] != 0) rightmost = i;
            if(hist[i] > maxval) maxval = hist[i];
        }

        double sum = 0;
        if(rightmost == 0) sum += 1;
        else {
            for(int i = 0; i <= rightmost; ++i) {
                sum += ((double)(rightmost-i) / rightmost) * hist[i] / maxval;
            }
        }
        sum += 0.01;

        printf("%.6f\n", sum);
    }
    return 0;
}
