#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct Node {
    int threshold;
    int axis;
    bool leaf;
    bool used;
    bool empty;

    Node *left, *right, *parent;
    int pos[2];

    Node(int thresh, int axis, Node *parent) : threshold(thresh), axis(axis), leaf(false), parent(parent), empty(false) {
        left = right = NULL;
    }

    Node(int *arr, int axis, Node *parent) : axis(axis), leaf(true), parent(parent), empty(false) {
        pos[0] = arr[0];
        pos[1] = arr[1];
    }

    virtual ~Node() {
        threshold = -3214;
        if(!leaf) {
            if(left) delete left;
            if(right) delete right;
        }
    }

    Node* insert_or_create(Node **n, int *arr) {
        if(*n) return (*n)->insert(arr);
        else return *n = new Node(arr, 1-axis, this);
    }

    Node* insert(int *arr) {
        if(leaf) {
            Node *mine = new Node(pos, 1-axis, this);
            mine->used = used;
            Node *ins = new Node(arr, 1-axis, this);

            leaf = false;
            empty = false;

            threshold = (arr[axis]+mine->pos[axis])/2;
            if(mine->pos[axis] < threshold) {
                left = mine;
                right = ins;
            }
            else {
                left = ins;
                right = mine;
            }

            return ins;
        }
        else {
            empty = false;
            if(arr[axis] < threshold) return insert_or_create(&left, arr);
            else return insert_or_create(&right, arr);
        }

        return NULL;
    }

    bool update_empty() {
        if(leaf) return false;

        bool empty_ = true;
        if(left) {
            if(left->leaf || !left->empty) empty_ = false;
        }
        if(right) {
            if(right->leaf || !right->empty) empty_ = false;
        }
        return empty = empty_;
    }

    void remove_it(Node *n) {
        if(leaf) return;

        if(n == left) {
            left->used = true;
            /*
            delete left;
            left = NULL;
            */
        }
        else {
            //assert(n == right);
            if(n != right) cerr << "Something went wrong!!" << endl;
            right->used = true;
            /*
            delete right;
            right = NULL;
            */
        }
        update_empty();
    }

    void inspect(int depth = 0) {
        for(int i = 0; i < depth; ++i) cout << "  ";
        if(leaf) cout << "(" << pos[0] << "," << pos[1] << "," << axis << "," << (used?"used":"") << ")" << endl;
        else {
            cout << "[" << threshold << "," << axis << (empty?",empty":"") << "]" << endl;
            if(left) left->inspect(depth+1);
            if(right) right->inspect(depth+1);
        }
    }
};

bool inCircle(int cx, int cy, int r, int x, int y) {
    unsigned long long x2 = (cx-x)*(cx-x);
    unsigned long long y2 = (cy-y)*(cy-y);
    unsigned long long r2 = r*r;

    return x2+y2 <= r2;
}

inline bool inRange(int a, int x, int b) {
    return a <= x && x <= b;
}

void remove(Node *n) {
    Node *parent;
    do {
        //cout << "remove " << n << endl;
        parent = n->parent;
        parent->remove_it(n);
        n = parent;
    } while(n->parent && n->empty);
    //cout << "removed." << endl;
}

void get_node_in_range(Node *n, int L, int T, int R, int B, vector<Node*> &res) {
    if(n == NULL) return;
    if(n->empty) return;

    if(n->leaf) {
        //if(n->pos[0] == 0 && n->pos[1] == 4) cout << "come" << endl;
        if(!n->used && inRange(L, n->pos[0], R) && inRange(T, n->pos[1], B)) {
            res.push_back(n);
            n->used = true;
            remove(n);
        }
        return;
    }
    else {
        if(n->axis == 0) {
            if(L <= n->threshold) get_node_in_range(n->left, L, T, R, B, res);
            if(R >= n->threshold) get_node_in_range(n->right, L, T, R, B, res);
        }
        else {
            //if(n->threshold == 2) cout << "come" << L << ' ' << T << ' ' << R << ' ' << B << endl;
            if(T <= n->threshold) get_node_in_range(n->left, L, T, R, B, res);
            if(B >= n->threshold) get_node_in_range(n->right, L, T, R, B, res);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);

    int N, R, L;
    while(cin >> N >> R >> L) {
        vector<pair<int, int> > v(N);
        long long sumx = 0;
        for(int i = 0; i < N; ++i) {
            cin >> v[i].first >> v[i].second;
            sumx += v[i].first;
        }
        int CX, CY;
        cin >> CX >> CY;

        queue<pair<int, int> > frozen;
        sumx /= N;
        random_shuffle(v.begin(), v.end());
        Node *root = new Node(sumx, 0, NULL);
        for(int i = 0; i < N; ++i) {
            int arr[2];
            arr[0] = v[i].first;
            arr[1] = v[i].second;

            if(inCircle(CX, CY, R, arr[0], arr[1])) {
                frozen.push(make_pair(arr[0], arr[1]));
            }
            else  {
                Node *n = root->insert(arr);
            }
        }

        //root->inspect();

        int ans = frozen.size();
        vector<Node*> tmp;
        set<Node*> hist;
        while(!frozen.empty()) {
            const int x = frozen.front().first;
            const int y = frozen.front().second;
            frozen.pop();

            tmp.clear();
            get_node_in_range(root, x-L/2, y-L/2, x+L/2, y+L/2, tmp);
            //root->inspect();

            for(int i = 0; i < tmp.size(); ++i) {
                ++ans;
                frozen.push(make_pair(tmp[i]->pos[0], tmp[i]->pos[1]));
                //cout << tmp[i]->pos[0] << ' ' << tmp[i]->pos[1] << endl;
                //remove(tmp[i]);
            }
        }

        cout << ans << endl;
        delete root;
    }

    return 0;
}
