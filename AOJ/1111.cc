#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

typedef unsigned long long ULL;

struct Pattern {
    bool permit;
    ULL src, dst, smask, dmask;
    Pattern() : src(0), dst(0), smask(~0LL), dmask(~0LL) {}
};

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<Pattern> rules;

        for(int i = 0; i < N; ++i) {
            string cmd, src, dst;
            cin >> cmd >> src >> dst;
            Pattern pat;

            for(int j = 0; j < 8; ++j) {
                if(src[j] != '?') pat.src |= (ULL)(src[j]-'0') << (7-j)*8;
                else pat.smask ^= (ULL)0xff << (7-j)*8;
                if(dst[j] != '?') pat.dst |= (ULL)(dst[j]-'0') << (7-j)*8;
                else pat.dmask ^= (ULL)0xff << (7-j)*8;
            }
            pat.permit = (cmd == "permit");
            rules.push_back(pat);
        }

        vector<string> allowed;
        for(int i = 0; i < M; ++i) {
            string src, dst, msg;
            cin >> src >> dst >> msg;
            ULL srcpat = 0, dstpat = 0;

            for(int j = 0; j < 8; ++j) {
                srcpat |= (ULL)(src[j]-'0') << 8*(7-j);
                dstpat |= (ULL)(dst[j]-'0') << 8*(7-j);
            }
//            printf("%llx %llx\n", srcpat, dstpat);

            bool denied = true;
            for(int j = rules.size()-1; j >= 0; --j) {
                if((srcpat & rules[j].smask) == rules[j].src &&
                   (dstpat & rules[j].dmask) == rules[j].dst) {
                    denied = !rules[j].permit;
                    break;
                }
            }
            if(denied) continue;
            allowed.push_back(src + " " + dst + " " + msg);
        }

        cout << allowed.size() << endl;
        for(int i = 0; i < allowed.size(); ++i) {
            cout << allowed[i] << endl;
        }
    }
    return 0;
}
