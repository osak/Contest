#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct RBTree {
    enum Color {
        RED,
        BLACK
    };
    struct Node {
        T value;
        Node *left, *right;
        Node *parent;
        Color color;

        Node(const T &value, Node *parent) : value(value), left(nullptr), right(nullptr), parent(parent), color(RED) {}
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

private:
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
        r->parent = parent;
        r->left = n;
        n->right = nrl;
        n->parent = r;
        if(nrl) nrl->parent = n;
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
        l->parent = parent;
        l->right = n;
        n->left = nlr;
        n->parent = l;
        if(nlr) nlr->parent = n;
    }
};

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    RBTree<string> s;
    for(int i = 0; i < N; ++i) {
        string cmd, str;
        cin >> cmd >> str;
        if(cmd == "insert") {
            s.insert(str);
        } else {
            cout << (s.find(str) ? "yes" : "no") << endl;
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
