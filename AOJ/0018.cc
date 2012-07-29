#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int arr[5];
    for(int i = 0; i < 5; ++i) cin >> arr[i];
    sort(arr, arr+5);
    for(int i = 4; i >= 0; --i) {
        cout << arr[i];
        if(i != 0) cout << ' ';
    }
    cout << endl;
    return 0;
}
