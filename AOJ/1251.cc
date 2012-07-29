#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

bool valid_path(const vector<string> &dirlist, const set<string> &dirs) {
    string curpath = "";
    for(int i = 0; i < dirlist.size(); ++i) {
        curpath += "/";
        curpath += dirlist[i];
    }
    return curpath == "" || dirs.count(curpath) != 0;
}

bool absolute_path(const string &str, const set<string> &dirs, string &res) {
    vector<string> dirlist;
    int prev = 1;
    for(int i = 1; i < str.size(); ++i) {
        if(str[i] == '/') {
            string dir = str.substr(prev, i-prev);

            if(dir == "..") {
                if(dirlist.size() == 0) return false;
                dirlist.pop_back();
            }
            else if(dir != ".") {
                dirlist.push_back(dir);
                if(!valid_path(dirlist, dirs)) return false;
            }
            prev = i+1;
        }
    }

    if(str[str.size()-1] == '/') { 
        dirlist.push_back("index.html");
    }
    if(prev != str.size()) { //Trailing '/' omitted
        string last = str.substr(prev);
        if(last == "..") {
            if(dirlist.size() == 0) return false;
            dirlist.pop_back();
        }
        else if(last != ".") {
            dirlist.push_back(last);
        }

        if(valid_path(dirlist, dirs)) { //This is Directory
            dirlist.push_back("index.html");
        }
    }

    res = "";
    for(int i = 0; i < dirlist.size(); ++i) {
        res += "/";
        res += dirlist[i];
    }

    //cout << "Relative: " << str << ", Absolute: " << res << endl;
    return true;
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        set<string> files;
        set<string> dirs;
        for(int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            files.insert(s);

            for(int j = 1; j < s.size(); ++j) {
                if(s[j] == '/') {
                    string dirname = s.substr(0, j);
                    dirs.insert(dirname);
                }
            }
        }

        for(int i = 0; i < M; ++i) {
            string s1, s2;
            cin >> s1 >> s2;

            string res = "not found";
            string p1, p2;
            if(absolute_path(s1, dirs, p1) && absolute_path(s2, dirs, p2)) {
                if(files.count(p1) && files.count(p2)) {
                    if(p1 == p2) res = "yes";
                    else res = "no";
                }
            }

            cout << res << endl;
        }
    }

    return 0;
}
