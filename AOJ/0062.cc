//Name: What is the Bottommost?
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>

using namespace std;

int main() {
    string line;
    while(cin >> line) {
        int arr[10] = {0};
        for(int i = 0; i < 10; ++i) arr[i] = line[i]-'0';
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 10-i-1; ++j) {
                arr[j] = (arr[j]+arr[j+1]) % 10;
            }
        }
        cout << arr[0] << endl;
    }
    return 0;
}
