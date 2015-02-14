//Name: 
//Level: 
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <set>
#include <cassert>
#include <vector>

using namespace std;

// Red Black Tree
// Based on wikipedia's implementation 
// http://en.wikipedia.org/wiki/Red%E2%80%93black_tree
template<typename T>
struct RBTree {
    enum Color {
        RED,
        BLACK
    };
    struct Node {
        T value, sum;
        int size;
        Node *left, *right;
        Node *parent;
        Color color;

        Node(const T &value, Node *parent) : value(value), sum(value), size(1), left(nullptr), right(nullptr), parent(parent), color(RED) {}
        ~Node() {
            delete left;
            delete right;
        }

        Node* sibiling() const {
            return parent->right == this ? parent->left : parent->right;
        }

        Node* uncle() const {
            return parent->sibiling();
        }
    };

    Node *root;

    RBTree() : root(nullptr) {}
    ~RBTree() {
        delete root;
    }

    void insert(const T &t) {
        Node **cur = &root;
        Node *parent = nullptr;
        while(*cur) {
            parent = *cur;
            if((*cur)->value == t) return; // Already exists
            if(t < (*cur)->value) {
                cur = &(*cur)->left;
            } else {
                cur = &(*cur)->right;
            }
        }
        *cur = new Node(t, parent);
        Node *n = parent;
        while(n) {
            n->sum += t;
            n->size++;
            n = n->parent;
        }
        balance(*cur);
    }

    bool find(const T &t) const {
        const Node *cur = root;
        while(cur) {
            if(cur->value == t) return true;
            if(t < cur->value) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return false;
    }

    T minsum(int K) const {
        return minsum_inner(root, K);
    }

private:
    T minsum_inner(Node *n, int &K) const {
        if(n->size <= K) {
            K -= n->size;
            return n->sum;
        } else {
            T sum = 0;
            if(n->left) {
                sum += minsum_inner(n->left, K);
            }
            if(K > 0) {
                sum += n->value;
                --K;
            }
            if(K > 0) {
                assert(n->right);
                sum += minsum_inner(n->right, K);
            }
            return sum;
        }
    }

    void balance(Node *cur) {
        if(cur == root) { // Case 1: This is root
            cur->color = BLACK;
            return;
        }
        if(cur->parent->color == BLACK) { // Case 2: Parent is black
            // The tree is still valid
            return;
        }
        auto uncle = cur->uncle();
        auto grand = cur->parent->parent;
        if(uncle && uncle->color == RED) { // Case 3: Both parent and uncle are red
            // Flip colors of parent, grandparent and uncle
            cur->parent->color = BLACK;
            grand->color = RED;
            uncle->color = BLACK;
            // Now grandparent may violate tree property
            balance(grand);
            return;
        }
        if(uncle == nullptr || uncle->color == BLACK) { // Case 4 & 5: Parent is red whereas uncle is black
             // Case 4: Parent and cur are opposite children
            if(cur == cur->parent->right && cur->parent == grand->left) {
                rotate_left(cur->parent);
                cur = cur->left;
            } else if(cur == cur->parent->left && cur->parent == grand->right) {
                rotate_right(cur->parent);
                cur = cur->right;
            }

            // Now cur and parent are surely in same direction
            // Then perform rotation on grandparent
            grand->color = RED;
            cur->parent->color = BLACK;
            if(cur == cur->parent->left) {
                rotate_right(grand);
            } else {
                rotate_left(grand);
            }
        }
    }

    void rotate_left(Node *n) {
        auto parent = n->parent;
        auto nrl = n->right->left;
        auto r = n->right;
        if(parent) {
            if(parent->left == n) {
                parent->left = r;
            } else if(parent->right == n) {
                parent->right = r;
            }
        } else {
            root = r;
        }
        n->right = nrl;
        n->parent = r;
        n->sum -= r->sum;
        n->size -= r->size;
        if(nrl) {
            nrl->parent = n;
            n->sum += nrl->sum;
            n->size += nrl->size;
            r->sum -= nrl->sum;
            r->size -= nrl->size;
        }
        r->parent = parent;
        r->left = n;
        r->sum += n->sum;
        r->size += n->size;
    }

    void rotate_right(Node *n) {
        auto parent = n->parent;
        auto nlr = n->left->right;
        auto l = n->left;
        if(parent) {
            if(parent->left == n) {
                parent->left = l;
            } else if(parent->right == n) {
                parent->right = l;
            }
        } else {
            root = l;
        }
        n->left = nlr;
        n->parent = l;
        n->sum -= l->sum;
        n->size -= l->size;
        if(nlr) {
            nlr->parent = n;
            n->sum += nlr->sum;
            n->size += nlr->size;
            l->sum -= nlr->sum;
            l->size -= nlr->size;
        }
        l->parent = parent;
        l->right = n;
        l->sum += n->sum;
        l->size += n->size;
    }
};

// Used in
// AOJ(ALDS1_4_C)

bool solve(bool first) {
    int N, K;
    if(!(cin >> N >> K)) return false;
    vector<int> boxes;
    set<int> cur;
    for(int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        boxes.push_back(v);
        cur.insert(v);
    }

    RBTree<long long> tree;
    for(auto it = begin(cur); next(it) != end(cur); ++it) {
        tree.insert(*next(it) - *it);
    }
    cout << tree.minsum(N-K) << endl;
    int Q;
    cin >> Q;
    for(int i = 0; i < Q; ++i) {
        int d;
        cin >> d;
        const int val = boxes[d];
        auto it = cur.find(val);
        assert(it != end(cur));
        if(it != begin(cur)) {
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
