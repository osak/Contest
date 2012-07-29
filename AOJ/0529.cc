#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<int> points;
        vector<int> points_of_two;
        for(int i = 0; i < N; ++i) {
            int p;
            cin >> p;
            points.push_back(p);
        }
        for(int i = 0; i < N; ++i) {
            if(points[i] <= M) points_of_two.push_back(points[i]);
            for(int j = 0; j < i; ++j) {
                int sum = points[i] + points[j];
                if(sum <= M) points_of_two.push_back(sum);
            }
        }
        points_of_two.push_back(0);
        sort(points_of_two.begin(), points_of_two.end());
        points_of_two.erase(unique(points_of_two.begin(), points_of_two.end()), points_of_two.end());

        int ans = 0;
        for(int i = 0; i < points_of_two.size(); ++i) {
            int rem = M - points_of_two[i];
            int left = 0, right = points_of_two.size();
            while(left < right) {
                int center = (left+right)/2;
                if(points_of_two[center] <= rem) {
                    left = center+1;
                }
                else {
                    right = center;
                }
            }
            if(left != 0) --left;
            int score = points_of_two[i] + points_of_two[left];
            if(score > ans) ans = score;
        }
        cout << ans << endl;
    }
    return 0;
}
