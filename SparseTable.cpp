#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/**
 * @brief SparseTable minimal implementation, Good for Static Arrays
 * 
 */
class SparseTable {
    private:
    vector<vector<int>> tree;
    function<int(int,int)> combiner;
    int Default;

    public:
    SparseTable(const vector<int> &L, int Default, function<int(int,int)> combiner) {
        this->combiner = combiner;
        this->Default = Default;
        tree = vector<vector<int>> (30, vector<int> (L.size(), Default));
        for(int i = 0; i < L.size(); ++i)
            tree[0][i] = L[i];
        for(int pw = 1; pw < 30; ++pw) {
            for(int i = 0; i < L.size(); ++i) {
                if (i + 1 < (1 << pw)) continue;
                tree[pw][i] = combiner(tree[pw - 1][i], tree[pw - 1][i - (1 << (pw - 1))]);
            }
        }
    }

    int get(int L, int R, int pw = 29) {
        if (pw == -1) return Default;
        if (R - L + 1 < (1 << pw)) return get(L, R, pw - 1);
        return combiner(tree[pw][R], get(L, R - (1 << pw), pw));
    }


};

int main() {
    vector<int> a = {1, 1,1,3,1,1,1,1};

    // f[j,i] = find sum of array in range [i - 2^j + 1, i]

    SparseTable table(a, 1, [](int i, int j) {return i + j;});

    a[2] = 4;

    for(int l = 0; l < a.size(); ++l) {
        for(int r = l; r < a.size(); ++r) {
            cout << table.get(l,r) << ", ";
        }
        cout << "\n";
    }
}