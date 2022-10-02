#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class SegmentTree {
    private:
    long long Value;
    function<int(int, int)> combiner;
    int Default;
    SegmentTree *left, *right;
    int L, R;

    public:
    SegmentTree(int R, int Default, function<int(int,int)> combiner, int L=0) : combiner(combiner), L(L), R(R), Default(Default) {
        if (this->L < this->R) {
            int mid = (this->L + this->R) >> 1;
            left = new SegmentTree(mid, Default, combiner, this->L);
            right = new SegmentTree(this->R, Default, combiner, mid + 1);
        }
        this->Value = Default;
    }

    long long update(int idx, int value) {
        if (L == R) return Value += value;
        int mid = (L + R) >> 1;
        if (idx > mid) return Value = combiner(left->Value, right->update(idx, value));
        else return Value = combiner(left->update(idx, value), right->Value);
    }

    long long get(int l, int r) {
        if (l > r) return Default;
        if (l == L && r == R) return Value;
        int mid = (L + R) >> 1;
        return combiner(left->get(l, min(r, mid)), right->get(max(l, mid + 1), r));
    }
};

int main() {
    
    // num of elements
    int n = 3;

    // create segment tree
    SegmentTree tree(n, 0, [](int i, int j) { return i + j; });

    tree.update(0, 2);
    tree.update(1, 3);
    tree.update(2, 7);
    // [2, 3, 7]

    cout << tree.get(0, 2) << endl;

    return 0;
}