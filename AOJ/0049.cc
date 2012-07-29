//Name: Blood Groups
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    map<string, int> m;
    int n;
    char comma;
    string type;
    while(cin >> n >> comma >> type) 
        m[type]++;
    cout << m["A"] << endl;
    cout << m["B"] << endl;
    cout << m["AB"] << endl;
    cout << m["O"] << endl;
    return 0;
}
