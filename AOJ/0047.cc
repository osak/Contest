//Name: Cup Game
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int arr[3] = {1, 0, 0};
    char c1, c2, comma;
    while(cin >> c1 >> comma >> c2) 
        swap(arr[c1-'A'], arr[c2-'A']);
    for(int i = 0; i < 3; ++i)
        if(arr[i]) cout << (char)('A'+i) << endl;
    return 0;
}
