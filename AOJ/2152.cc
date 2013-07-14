//Name: Restrictive Filesystem
//Level: 3
//Category: シミュレーション,連結リスト
//Note:

/*
 * 連続して挿入される個所を一つのノードにして、連結リストで管理する。
 * ノード数は1回の挿入操作で高々1しか増えないため、各操作は線形探索で問題ない。
 *
 * オーダーは O(N^2)。
 * ただし上述の通り、定数項がかなり小さい。
 */
#include <iostream>
#include <list>
#include <string>
 
using namespace std;
 
struct Segment {
    int start;
    int end;
    int id;
     
    Segment() {}
    Segment(int s, int e, int id) : start(s), end(e), id(id) {}
};
 
list<Segment> storage;
void do_write(const int id, const int sectors) {
    list<Segment>::iterator it = storage.begin();
    int prev_last = -1;
    int remain = sectors;
    while(it != storage.end()) {
        if(it->start > prev_last+1) {
            // insert file
            int size = min(remain, it->start - prev_last - 1);
            it = storage.insert(it, Segment(prev_last+1, prev_last+1+size-1, id));
            remain -= size;
            if(remain == 0) break;
        }
        prev_last = it->end;
        ++it;
    }
    if(remain > 0) {
        storage.insert(it, Segment(prev_last+1, prev_last+1+remain-1, id));
    }
}
 
void do_delete(const int id) {
    list<Segment>::iterator it = storage.begin();
    while(it != storage.end()) {
        if(it->id == id) {
            it = storage.erase(it);
        } else {
            ++it;
        }
    }
}
 
int read_sector(const int sector) {
    for(list<Segment>::const_iterator it = storage.begin(); it != storage.end(); ++it) {
        if(it->start <= sector && sector <= it->end) {
            return it->id;
        }
    }
    return -1;
}
 
bool solve() {
    int N;
    cin >> N;
    if(!N) return false;
    storage.clear();
    while(N--) {
        string cmd;
        cin >> cmd;
        if(cmd == "W") {
            int id, sectors;
            cin >> id >> sectors;
            do_write(id, sectors);
        } else if(cmd == "D") {
            int id;
            cin >> id;
            do_delete(id);
        } else if(cmd == "R") {
            int sector;
            cin >> sector;
            cout << read_sector(sector) << endl;
        }
    }
    cout << endl;
    return true;
}
 
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
     
    for(; solve(); ) ;
    return 0;
}
