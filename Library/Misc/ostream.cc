// ostream support for vector.
template<typename T>
ostream& operator <<(ostream &os, const vector<T> &v) {
    for(const T &t : v) {
        os << t << endl;
    }
    return os;
}
