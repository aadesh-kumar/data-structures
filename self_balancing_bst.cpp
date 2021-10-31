#include <iostream>
using namespace std;


/**
 * Index-based AVL Tree
**/
template<typename T>
class bst {
private:
    bst* l, *r, *p;
    bool is_root;
    int8_t _depth;
    int _size, freq;
    T data;
    int get_depth(bst * node) {
        return (node ? node->_depth : -1);
    }
    void set_aux() {
        _size = (r ? r->size() : 0) + (l ? l->size() : 0) + freq;
        _depth = (!is_root) + max(get_depth(l), get_depth(r));
    }
    void join(bst * anc, bst * des, bool dir = false) {
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
    void rotate(bst * anc, bst * des) {
        join(anc->p, des);
        bst * tmp = (anc->data > des->data ? des->r : des->l);
        join(des, anc);
        join(anc, tmp, (anc->data < des->data));
        anc->set_aux();
        des->set_aux();
    }
    bst* rebuildSubtree() {
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
    bst* insert_elem(T d) {
        if (d < data) l = (l ? l->insert_elem(d) : new bst(d, this));
        else if (d > data) r = (r ? r->insert_elem(d) : new bst(d, this));
        else freq++;
        set_aux();
        return rebuildSubtree();
    }
    bst(T d, bst * par) {
        data = d;
        l = r = NULL;
        p = par;
        is_root = _depth = 0;
        _size = freq = 1;
    }
    bst * erase_elem(T d, bst * node) {
        if (d != data and (r || l)) {
            if (d > data and r) r = r->erase_elem(d, node);
            else if (d < data and l) l = l->erase_elem(d, node);
            set_aux();
            return rebuildSubtree();
        }
        if (d == data) {
            freq--;
            if (freq > 0) return this;
            if (r) {
                r = r->erase_elem(d, this);
                set_aux();
                return rebuildSubtree();
            }
            if (l) {
                data = l->data;
                freq = l->freq;
                delete l;
                return this;
            }
            delete this;
            return NULL;
        }
        node->data = data;
        node->freq = freq;
        bst * ret = r;
        l = r = p = NULL;
        delete this;
        return ret;
    }
public:
    bst() {
        l = r = p = NULL;
        is_root = 1;
        _size = _depth = freq = 0;
    }
    int size() {
        return _size;
    }
    int depth() {
        return _depth;
    }
    void insert(T d) {
        if (l == NULL) l = new bst(d, NULL);
        else l = l->insert_elem(d);
        set_aux();
    }
    void erase(T d) {
        l = l->erase_elem(d, NULL);
        set_aux();
    }
    int lower_bound(T e) {
        if (is_root and l) return l->lower_bound(e);
        int result = size();
        if (data >= e) result = min(result, (l ? l->size() : 0));
        if (e > data and r) result = min((l ? l->size() : 0) + freq + r->lower_bound(e), result);
        if (e < data and l) result = min(result, l->lower_bound(e));
        return result;
    }
    T at(int idx) {
        if (l and (idx < l->_size || is_root))
            return l->at(idx);
        if (r and idx >= l->_size + freq)
            return r->at(idx - l->_size - freq);
        return data;
    }
    void clearTree() {
        if (l) delete l;
        if (r) delete r;
        l = r = p = NULL;
    }
    void dfs(int spaces = 0) {
        if (is_root) {
            if (l) l->dfs();
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
    return 0;
}
