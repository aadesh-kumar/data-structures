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

void solve() {
    int n;
    cin >> n;
    SegmentTree tree(n, 0, [](int i, int j) { return i + j; });
    long long res = 0;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        --a;
        res += tree.get(a, n - 1);
        tree.update(a, 1);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input.txt", "r", stdin);

    int tests;
    cin >> tests;

    while (tests--) {
        solve();
    }

    return 0;
}