template<typename T>
ostream& operator <<(ostream& os, const vector<vector<T>> &v) {
    for(const auto &row : v) {
        for(const auto &val : row) {
            os << val << ' ';
        }
        os << endl;
    }
    return os;
}
