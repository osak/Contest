#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int a, b;
    while(cin >> a >> b) {
        int c = a+b;
        ostringstream os;
        os << c;
        cout << os.str().length() << endl;
    }
    return 0;
}
