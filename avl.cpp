#include <iostream>
using namespace std;

class avl {
private:
    avl* l, *r, *p;
    bool is_root;
    int8_t _depth;
    int _size, freq, data;
    int get_depth(avl * node) {
        return (node ? node->_depth : -1);
    }
    void set_aux() {
        _size = size(r, 1) + size(l, 1) + freq;
        _depth = (!is_root) + max(get_depth(l), get_depth(r));
    }
    void join(avl * anc, avl * des, bool dir = false) {
        if (anc) {
            if (des == NULL) {
                (dir ? anc->r : anc->l) = des;
                return;
            }
            if (des->data > anc->data) anc->r = des;
            else anc->l = des;
        }
        if (des) des->p = anc;
    }
    void rotate(avl * anc, avl * des) {
        join(anc->p, des);
        avl * tmp = (anc->data > des->data ? des->r : des->l);
        join(des, anc);
        join(anc, tmp, (anc->data < des->data));
        anc->set_aux();
        des->set_aux();
    }
    avl* rebuildSubtree() {
        if (get_depth(r) - get_depth(l) == 2) {
            if (get_depth(r->r) - get_depth(r->l) == -1)
                rotate(r,r->l);
            rotate(this,r);
            return p;
        } else if (get_depth(r) - get_depth(l) == -2) {
            if (get_depth(l->r) - get_depth(l->l) == 1)
                rotate(l,l->r);
            rotate(this,l);
            return p;
        }
        return this;
    }
    avl* insert1(int d) {
        if (d < data) l = (l ? l->insert1(d) : new avl(d, this));
        else if (d > data) r = (r ? r->insert1(d) : new avl(d, this));
        else freq++;
        set_aux();
        return rebuildSubtree();
    }
    avl(int d, avl * par) {
        data = d;
        l = r = NULL;
        p = par;
        is_root = _depth = false;
        _size = freq = 1;
    }
public:
    avl() {
        data = 0;
        l = r = p = NULL;
        is_root = 1;
        _size = _depth = freq = 0;
    }
    int size(avl * node = NULL, bool flag = false) {
        if (flag) return (node ? node->_size : 0);
        return _size;
    }
    int depth() {
        return _depth;
    }
    void insert(int d) {
        if (l == NULL) l = new avl(d, NULL);
        else l = l->insert1(d);
        set_aux();
    }
    avl * erase(int d, avl * node = NULL) {
        if ((is_root or d < data) and l) l = l->erase(d, node);
        if (d == data) {
            freq--;
            if (freq) return this;
            if (r) {
                r = r->erase(d, this);
                return rebuildSubtree();
            }
            if (l) {
                data = l->data;
                delete l;
                l = NULL;
                return this;
            }
            delete this;
            return NULL;
        }
        if (d > data and r) r = r->erase(d, node);
        if (node != NULL) {
            node->data = data;
            avl * ret = r;
            l = r = p = NULL;
            delete this;
            return ret;
        }
        return rebuildSubtree();
    }
    int lower_bound(int e) {
        if (is_root and l) return l->lower_bound(e);
        int ans = size();
        if (data >= e) ans = min(ans, size(l, 1));
        if (e > data and r) ans = min(ans, size(l, 1) + freq + r->lower_bound(e));
        if (e < data and l) ans = min(ans, l->lower_bound(e));
        return ans;
    }
    void clearTree() {
        if (l) delete l;
        if (r) delete r;
        l = r = p = NULL;
    }
    void dfs(int spaces = 0) {
        if (is_root) {
            l->dfs();
            return;
        }
        if (r) r->dfs(spaces+5);
        for(int i=0; i<spaces; ++i)
            cout << " ";
        cout << data << "\n";
        if (l) l->dfs(spaces+5);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    avl s;
    for(int i=0; i<1e6; ++i)
        s.insert(i);
    cout << s.depth() << "\n";
    return 0;
}
