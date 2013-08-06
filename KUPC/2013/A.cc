#include <iostream>
#include <string>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, Q;
    cin >> N >> Q;
    string name = "kogakubu10gokan";
    while(N--) {
        int year;
        string new_name;
        cin >> year >> new_name;
        if(Q >= year) name = new_name;
    }
    cout << name << endl;
    return 0;
}

