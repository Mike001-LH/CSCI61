#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Order m B-tree (course convention):
- max keys per node = m - 1
- min keys per non-root node = (m - 1) / 2
  which matches common classroom "order 5 -> min 2 keys, max 4 keys".
- children count = keys + 1 for internal nodes
Insertion: loose insertion + fix_excess
Deletion: loose removal + fix_shortage (4 cases)
Search: single-subtree recursion (4 cases)
*/

struct Node {
    vector<int> key;      // sorted, partially filled
    vector<Node*> child;  // empty if leaf; else size = key.size() + 1
    bool leaf;

    Node(bool is_leaf) : leaf(is_leaf) {}
};

class BTree {
public:
    explicit BTree(int order_m)
        : m(order_m), max_keys(order_m - 1), min_keys((order_m - 1) / 2) {
        root = new Node(true);
    }

    /* -------------------- SEARCH -------------------- */
    bool contains(int x) const { return search(root, x); }

    /* -------------------- INSERT -------------------- */
    void insert(int x) {
        loose_insert(root, x);
        if ((int)root->key.size() > max_keys) {
            Node* new_root = new Node(false);
            new_root->child.push_back(root);
            fix_excess(new_root, 0);
            root = new_root;
        }
    }

    /* -------------------- DELETE -------------------- */
    bool remove(int x) {
        bool removed = loose_remove(root, x);

        // Root may shrink in height.
        if (!root->leaf && root->key.empty()) {
            Node* old = root;
            root = root->child[0];
            // For classroom simplicity we skip freeing old.
        }
        return removed;
    }

private:
    int m;         // order
    int max_keys;  // m-1
    int min_keys;  // ceil(m/2)-1 (course-style), approx (m-1)/2
    Node* root;

private:
    /* -------------------- UTIL -------------------- */
    static int first_ge(const vector<int>& a, int x) {
        return (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
    }

    /* ============================================================
       SEARCH: four cases (as in your slides)
       1) leaf + not found -> return false
       2) leaf + found     -> return true
       3) internal + not found -> recurse subset[i]
       4) internal + found     -> return true
       ============================================================ */
    bool search(Node* n, int x) const {
        int i = first_ge(n->key, x);
        bool found = (i < (int)n->key.size() && n->key[i] == x);

        if (n->leaf) {
            // Case 1 and Case 2
            return found;
        } else {
            if (found) {
                // Case 4
                return true;
            }
            // Case 3
            return search(n->child[i], x);
        }
    }

    /* ============================================================
       INSERT (loose): may temporarily allow max_keys+1 keys in a child
       ============================================================ */
    void loose_insert(Node* n, int x) {
        int i = first_ge(n->key, x);

        // Ignore duplicates (optional)
        if (i < (int)n->key.size() && n->key[i] == x) return;

        if (n->leaf) {
            // Insert into partially filled key array
            n->key.insert(n->key.begin() + i, x);
            return; // may overflow; parent fixes
        }

        // Recurse into exactly one child
        loose_insert(n->child[i], x);

        // Fix child overflow if needed
        if ((int)n->child[i]->key.size() > max_keys) {
            fix_excess(n, i);
        }
    }

    void fix_excess(Node* parent, int i) {
        Node* left = parent->child[i];      // overflowing child
        Node* right = new Node(left->leaf);

        int mid = (int)left->key.size() / 2;   // median index
        int promote = left->key[mid];

        // right gets keys after median
        right->key.assign(left->key.begin() + mid + 1, left->key.end());
        // left keeps keys before median
        left->key.erase(left->key.begin() + mid, left->key.end());

        // split children if internal
        if (!left->leaf) {
            right->child.assign(left->child.begin() + mid + 1, left->child.end());
            left->child.erase(left->child.begin() + mid + 1, left->child.end());
        }

        // insert promoted key into parent and right pointer into parent children
        int p = first_ge(parent->key, promote);
        parent->key.insert(parent->key.begin() + p, promote);
        parent->child.insert(parent->child.begin() + (p + 1), right);
        parent->leaf = false;
    }

    /* ============================================================
       DELETE (loose): four cases (as in your slides) + fix_shortage
       1) leaf + not found -> return false
       2) leaf + found     -> erase key, return true
       3) internal + not found -> recurse subset[i], then fix_shortage if needed
       4) internal + found -> replace with predecessor (or successor), recurse delete, fix_shortage
       ============================================================ */

    // Remove and return predecessor (max key) from subtree rooted at n.
    int remove_predecessor(Node* n) {
        if (n->leaf) {
            int k = n->key.back();
            n->key.pop_back();
            return k;
        }
        int last = (int)n->child.size() - 1;
        int k = remove_predecessor(n->child[last]);
        if ((int)n->child[last]->key.size() < min_keys) {
            fix_shortage(n, last);
        }
        return k;
    }

    bool loose_remove(Node* n, int x) {
        int i = first_ge(n->key, x);
        bool found = (i < (int)n->key.size() && n->key[i] == x);

        if (n->leaf) {
            // Case 1 and Case 2
            if (!found) return false;                 // Case 1
            n->key.erase(n->key.begin() + i);         // Case 2
            return true;
        }

        if (!found) {
            // Case 3: recurse into subset[i]
            bool removed = loose_remove(n->child[i], x);

            // fix shortage on the way back up
            if ((int)n->child[i]->key.size() < min_keys) {
                fix_shortage(n, i);
            }
            return removed;
        } else {
            // Case 4: found in internal node
            // Replace n->key[i] with predecessor from left subtree (child i)
            int pred = remove_predecessor(n->child[i]);
            n->key[i] = pred;

            // left child might now be short
            if ((int)n->child[i]->key.size() < min_keys) {
                fix_shortage(n, i);
            }
            return true;
        }
    }

    void fix_shortage(Node* parent, int i) {
        Node* c = parent->child[i]; // short child: keys < min_keys

        // Borrow from left sibling if possible
        if (i > 0) {
            Node* L = parent->child[i - 1];
            if ((int)L->key.size() > min_keys) {
                // Rotate right
                c->key.insert(c->key.begin(), parent->key[i - 1]);
                parent->key[i - 1] = L->key.back();
                L->key.pop_back();

                if (!L->leaf) {
                    c->child.insert(c->child.begin(), L->child.back());
                    L->child.pop_back();
                    c->leaf = false;
                }
                return;
            }
        }

        // Borrow from right sibling if possible
        if (i + 1 < (int)parent->child.size()) {
            Node* R = parent->child[i + 1];
            if ((int)R->key.size() > min_keys) {
                // Rotate left
                c->key.push_back(parent->key[i]);
                parent->key[i] = R->key.front();
                R->key.erase(R->key.begin());

                if (!R->leaf) {
                    c->child.push_back(R->child.front());
                    R->child.erase(R->child.begin());
                    c->leaf = false;
                }
                return;
            }
        }

        // Must merge (no sibling can lend)
        if (i > 0) {
            // Merge c into left sibling using parent key[i-1]
            Node* L = parent->child[i - 1];

            L->key.push_back(parent->key[i - 1]);
            L->key.insert(L->key.end(), c->key.begin(), c->key.end());

            if (!c->leaf) {
                L->child.insert(L->child.end(), c->child.begin(), c->child.end());
                L->leaf = false;
            }

            parent->key.erase(parent->key.begin() + (i - 1));
            parent->child.erase(parent->child.begin() + i);
            // skip delete c for simplicity
        } else {
            // Merge right sibling into c using parent key[i]
            Node* R = parent->child[i + 1];

            c->key.push_back(parent->key[i]);
            c->key.insert(c->key.end(), R->key.begin(), R->key.end());

            if (!R->leaf) {
                c->child.insert(c->child.end(), R->child.begin(), R->child.end());
                c->leaf = false;
            }

            parent->key.erase(parent->key.begin() + i);
            parent->child.erase(parent->child.begin() + (i + 1));
            // skip delete R for simplicity
        }
    }
};

/* ---------------- demo ---------------- */
int main() {
    BTree t(5); // order 5 -> max 4 keys, min 2 keys (non-root)

    // Insert some values
    vector<int> vals = {
        300, 450, 700, 950,
        50, 100, 200,
        325, 350, 400, 425,
        500, 600,
        850, 900,
        1000, 1200
    };
    for (int v : vals) t.insert(v);

    cout << "contains(375) before insert: " << (t.contains(375) ? "true" : "false") << "\n";
    t.insert(375);
    cout << "contains(375) after insert:  " << (t.contains(375) ? "true" : "false") << "\n";

    cout << "remove(375): " << (t.remove(375) ? "true" : "false") << "\n";
    cout << "contains(375) after remove: " << (t.contains(375) ? "true" : "false") << "\n";

    cout << "remove(999): " << (t.remove(999) ? "true" : "false") << "\n";

    return 0;
}
