//Name: Emacs-like Editor
//Level: 2
//Category: シミュレーション
//Note: 類題:AOJ1101

/*
 * シミュレーションやるだけ。実装が重い。
 * substrを使いこなせると楽に書ける。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> buffer;
    while(true) {
        string str;
        getline(cin, str);
        if(str == "END_OF_TEXT") break;
        buffer.push_back(str);
    }

    int row = 0, col = 0;
    string clipboard;
    while(true) {
        char op;
        cin >> op;
        if(op == '-') break;
        if(op == 'a') {
            col = 0;
        }
        else if(op == 'e') {
            col = buffer[row].size();
        }
        else if(op == 'p') {
            col = 0;
            if(row-1 >= 0) row--;
        }
        else if(op == 'n') {
            col = 0;
            if(row+1 < buffer.size()) row++;
        }
        else if(op == 'f') {
            if(col == buffer[row].size()) {
                if(row+1 < buffer.size()) {
                    row++;
                    col = 0;
                }
            }
            else col++;
        }
        else if(op == 'b') {
            if(col == 0) {
                if(row-1 >= 0) {
                    row--;
                    col = buffer[row].size();
                }
            }
            else col--;
        }
        else if(op == 'd') {
            if(col == buffer[row].size()) {
                if(row+1 < buffer.size()) {
                    buffer[row] += buffer[row+1];
                    for(int i = row+1; i < (int)buffer.size()-1; ++i) buffer[i] = buffer[i+1];
                    buffer.resize((int)buffer.size()-1);
                }
            }
            else buffer[row] = buffer[row].substr(0, col) + buffer[row].substr(col+1);
        }
        else if(op == 'k') {
            if(col == buffer[row].size()) {
                if(row+1 < buffer.size()) {
                    buffer[row] += buffer[row+1];
                    for(int i = row+1; i < (int)buffer.size()-1; ++i) buffer[i] = buffer[i+1];
                    buffer.resize((int)buffer.size()-1);
                    clipboard = "\n";
                }
            }
            else {
                clipboard = buffer[row].substr(col);
                buffer[row] = buffer[row].substr(0, col);
                col = buffer[row].size();
            }
        }
        else if(op == 'y') {
            if(clipboard == "\n") {
                buffer.resize(buffer.size()+1);
                for(int i = (int)buffer.size()-1; i > row+1; --i) 
                    buffer[i] = buffer[i-1];
                buffer[row+1] = buffer[row].substr(col);
                buffer[row] = buffer[row].substr(0, col);
                ++row;
                col = 0;
            }
            else if(clipboard != "") {
                buffer[row] = buffer[row].substr(0, col) + clipboard + buffer[row].substr(col);
                col += clipboard.size();
            }
        }
    }
    for(int i = 0; i < buffer.size(); ++i)
        cout << buffer[i] << endl;
    return 0;
}
