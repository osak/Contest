#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    vector<double> nums(N);
    for(int i = 0; i < N; ++i) {
        cin >> nums[i];
    }
    vector<int> ord(N-1);
    for(int i = 0; i < N-1; ++i) ord[i] = i;
    vector<int> best;
    double best = -1.0/0.0;
    do {

