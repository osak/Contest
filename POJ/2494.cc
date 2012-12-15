//Name: Acid Text
//Level: 3
//Category: 実装
//Note:

/*
 * がんばる．
 * 出力部ではstable_sortを使うと便利．
 */
#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

struct Entry {
    int posx, posy;
    int x, y;
    string position;
    string file;
    int layer;

    bool operator <(const Entry &other) const {
        return layer < other.layer;
    }
};

typedef vector<string> Image;

char buf[1001][1001];

void init() {
    for(int i = 0; i < 1000; ++i) {
        for(int j = 0; j < 1000; ++j) {
            buf[i][j] = ' ';
        }
    }
};

string nameline(const string &str) {
    size_t start = 1;
    size_t end = start+1;
    while(!isspace(str[end]) && str[end] != '{') ++end;
    return str.substr(start, end-start);
}

int pos(const string &str) {
    int val = 0;
    bool neg = false;
    size_t digit_pos = str.find_first_of("0123456789");
    if(str[digit_pos-1] == '-') {
        neg = true;
    }
    while(isdigit(str[digit_pos])) {
        val *= 10;
        val += str[digit_pos] - '0';
        ++digit_pos;
    }
    return neg ? -val : val;
}

string position(const string &str) {
    size_t eql = str.find('=');
    if(eql == string::npos) {
        return "absolute";
    } else {
        size_t start = eql+1;
        while(isspace(str[start])) ++start;
        size_t end = start+1;
        while(!isspace(str[end]) && str[end] != ';') ++end;
        return str.substr(start, end-start);
    }
}

string file(const string &str) {
    size_t colon = str.find(':');
    size_t start = colon + 1;
    while(isspace(str[start])) ++start;
    size_t end = start+1;
    while(!isspace(str[end]) && str[end] != ';') ++end;
    return str.substr(start, end-start);
}

int layer(const string &str) {
    size_t digit_pos = str.find_first_of("0123456789");
    int val = 0;
    while(isdigit(str[digit_pos])) {
        val *= 10;
        val += str[digit_pos] - '0';
        ++digit_pos;
    }
    return val;
}

void determine(vector<Entry> &entries, int idx, map<string,int> &dict) {
    Entry &entry = entries[idx];
    if(entry.position == "absolute") return;
    int dep = dict[entry.position];
    determine(entries, dep, dict);
    entry.posx += entries[dep].posx;
    entry.posy += entries[dep].posy;
    entry.position = "absolute";
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int CASES;
    cin >> CASES;
    for(int CASE = 1; CASE <= CASES; ++CASE) {
        init();
        int I;
        cin >> I;
        map<string,Image> images;
        for(int i = 0; i < I; ++i) {
            string filename;
            int H, W;
            cin >> filename >> H >> W;
            cin.ignore();
            Image &img = images[filename];
            while(H--) {
                string line;
                getline(cin, line);
                img.push_back(line);
            }
        }
        int N;
        cin >> N;
        cin.ignore();
        vector<Entry> entries(N);
        map<string,int> dict;
        for(int i = 0; i < N; ++i) {
            Entry &entry = entries[i];
            string line;
            getline(cin, line);
            const string name = nameline(line);
            dict[name] = i;
            getline(cin, line);
            entry.posx = pos(line);
            getline(cin, line);
            entry.posy = pos(line);
            getline(cin, line);
            entry.position = position(line);
            getline(cin, line);
            entry.file = file(line);
            getline(cin, line);
            entry.layer = layer(line);
            getline(cin, line);
        }
        for(int i = 0; i < N; ++i) {
            Entry &entry = entries[i];
            if(entry.position != "absolute") {
                determine(entries, i, dict);
            }
        }
        stable_sort(entries.begin(), entries.end());
        int height = 0, width = 0;
        for(int i = 0; i < N; ++i) {
            Entry &entry = entries[i];
            const Image &img = images[entry.file];
            const int H = img.size();
            const int W = img[0].size();
            height = max(height, entry.posy + H);
            width = max(width, entry.posx + W);
            for(int iy = 0; iy < H; ++iy) {
                const int y = entry.posy + iy;
                for(int ix = 0; ix < W; ++ix) {
                    const int x = entry.posx + ix;
                    if(img[iy][ix] != '.') buf[y][x] = img[iy][ix];
                }
            }
        }
        cout << "Scenario #" << CASE << ":" << endl;
        for(int y = 0; y < height; ++y) {
            buf[y][width] = '\0';
            cout << buf[y] << endl;
        }
        cout << endl;
    }
    return 0;
}
