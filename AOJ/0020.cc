#include <iostream>
#include <string>

using namespace std;

int main() {
    while(true) {
        string str;
        getline(cin, str);
        if(str == "") break;

        for(int i = 0; i < str.size(); ++i)
            if(islower(str[i])) str[i] = toupper(str[i]);
        cout << str << endl;
    }
    return 0;
}
