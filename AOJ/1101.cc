#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore();

    while(N--) {
        string str;
        getline(cin, str);
        int cursor = 0;
        int M;
        cin >> M;
        cin.ignore();

        while(M--) {
            string cmdline;
            getline(cin, cmdline);

            int delim = cmdline.find(' ');
            string cmd = cmdline.substr(0, delim);
            string target = cmdline.substr(delim+1);
            if(cmd == "forward") {
                if(target == "word") {
                    while(cursor < str.size() && str[cursor] == ' ') ++cursor;
                    while(cursor < str.size() && str[cursor] != ' ') ++cursor;
                }
                else if(target == "char") {
                    if(cursor < str.size()) ++cursor;
                }
                else {
                    cerr << "Unknown target in forward: " << target << endl;
                }
            }
            else if(cmd == "backward") {
                if(target == "word") {
                    if(cursor > 0) --cursor;
                    while(cursor > 0 && str[cursor] == ' ') --cursor;
                    while(cursor > 0 && str[cursor] != ' ') --cursor;
                    if(str[cursor] == ' ' && str[cursor+1] != ' ') ++cursor;
                }
                else if(target == "char") {
                    if(cursor > 0) --cursor;
                }
                else {
                    cerr << "Unknown target in backward: " << target << endl;
                }
            }
            else if(cmd == "delete") {
                if(target == "word") {
                    int idx = cursor;
                    bool ok = false;
                    while(idx < str.size() && str[idx] == ' ') ++idx;
                    while(idx < str.size() && str[idx] != ' ') {++idx; ok = true; }
                    if(ok) {
                        str.erase(cursor, idx-cursor);
                    }
                }
                else if(target == "char") {
                    if(cursor >= str.size()) continue;
                    str.erase(cursor, 1);
                }
                else {
                    cerr << "Unknown target in delete: " << target << endl;
                }
            }
            else if(cmd == "insert") {
                str = str.substr(0, cursor) + target.substr(1, target.size()-2) + str.substr(cursor);
                cursor += target.size()-2;
            }
            else {
                //cerr << "Unknown command: " << cmd << endl;
            }
            //cout << cmdline << endl;
            //cout << "\t" << str.substr(0, cursor) << '^' << str.substr(cursor) << endl;
        }
        cout << str.substr(0, cursor) << '^' << str.substr(cursor) << endl;
    }
    return 0;
}
