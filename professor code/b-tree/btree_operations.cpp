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
/*
翻译：
课程约定的m阶B树：
- 每个节点的最大键数 = m - 1
- 每个非根节点的最小键数 = (m - 1) / 2
  这与常见的课堂“5阶 -> 最小2键，最大4键”相匹配。
插入：松散插入 + 修复过多
删除：松散删除 + 修复不足（4种情况）
搜索：单子树递归（4种情况）
*/

struct Node {
    vector<int> key;      // sorted, partially filled                       //这个vector存储了节点中的键，按照升序排列，并且可能没有填满整个容量（即可能有空位）。
    vector<Node*> child;  // empty if leaf; else size = key.size() + 1      //这个vector存储了节点的子节点指针，如果当前节点是叶子节点，则该vector为空；如果不是叶子节点，则该vector的大小等于key.size() + 1，因为每个键将子节点分成两部分。
    bool leaf;//如果leaf为true，表示该节点是叶子节点；如果为false，表示该节点是内部节点。

    Node(bool is_leaf) : leaf(is_leaf) {}//构造函数，接受一个布尔值参数is_leaf，用于初始化节点的leaf成员变量。根据传入的参数，节点将被标记为叶子节点或内部节点。
};
/*
- `key`：存储键值，始终保持升序
- `child`：子节点指针，叶节点为空，内部节点有 `key.size() + 1` 个子节点
- `leaf`：标识是否为叶子节点
**内部节点的结构示意：**
keys:     [ 300 | 500 | 700 ]
children: [C0] [C1] [C2] [C3]
           ↑    ↑    ↑    ↑
         <300 301~ 501~ >700
              499  699
*/

class BTree {
public:
    // 构造函数，接受一个整数参数order_m，表示B树的阶数（当前节点子节点数量）。根据阶数计算最大键数和最小键数，并初始化根节点为一个叶子节点。
    explicit BTree(int order_m)
        : m(order_m), max_keys(order_m - 1), min_keys((order_m - 1) / 2) {//传入的分别是阶数m，计算最大键数max_keys和最小键数min_keys。
        root = new Node(true);
    }

    /* -------------------- SEARCH -------------------- */
    bool contains(int x) const { return search(root, x); }

    /* -------------------- INSERT -------------------- */
    void insert(int x) {
        loose_insert(root, x);//调用loose_insert函数在根节点root中插入键x。loose_insert函数可能会暂时允许某个节点的键数超过max_keys
        if ((int)root->key.size() > max_keys) {//如果插入后根节点的键数超过了max_keys，也就是超过了B树的阶数限制，我们需要修复这个问题。
            Node* new_root = new Node(false);//因此，我们创建一个新的根节点new_root，并将其标记为内部节点（leaf = false）。
            new_root->child.push_back(root);//将原来的根节点root作为新根节点的第一个子节点。推入new_root的child vector中。
            fix_excess(new_root, 0);//调用fix_excess函数来修复新根节点的第0个子节点（也就是原来的根节点）。fix_excess函数会将原来的根节点分裂成两个节点，并将中间的键提升到新根节点中，从而保持B树的性质。
            root = new_root;//最后，我们将root指向新的根节点new_root，这样B树的高度就增加了1，同时保持了B树的平衡和有序性。
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
    int m;         // order                                         //m是B树的阶数，表示每个节点最多可以有多少个子节点。
    int max_keys;  // m-1                                           //max_keys是每个节点允许的最大键数，等于阶数m减1。也就是每个节点最多可以存m-1个元素。  
    int min_keys;  // ceil(m/2)-1 (course-style), approx (m-1)/2    //min_keys是每个非根节点必须至少拥有的最小键数，通常是阶数m的一半向上取整减1。对于课程约定的B树来说，min_keys等于(m-1)/2，这意味着每个非根节点至少需要有(m-1)/2个键。
    Node* root;                                                     //root是指向B树根节点的指针。B树的所有操作（搜索、插入、删除）都是从根节点开始进行的，因此这个指针是非常重要的。通过root，我们可以访问整个B树的数据结构。

private:
    /* -------------------- UTIL -------------------- */
    static int first_ge(const vector<int>& a, int x) {//作用：在有序数组中找到第一个 ≥ x 的元素的下标。//例如 a = [100, 300, 500]，查找 300，返回 1。查找 400，返回 2。
        return (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
        //begin()返回指向vector第一个元素的迭代器，end()返回指向vector最后一个元素之后位置的迭代器。
        //lower_bound函数在有序范围内查找第一个不小于x的元素，并返回一个指向该元素的迭代器。
        //通过将这个迭代器减去a.begin()，我们得到该元素在vector中的索引位置。也就是第一个大于或等于x的元素的index。
        //之所以要减去a.begin()，是因为lower_bound返回的是一个迭代器，而我们需要的是一个整数索引。通过减去a.begin()，我们将迭代器转换为相对于vector起始位置的索引。
    }

    /* ============================================================
       SEARCH: four cases (as in your slides)
       1) leaf + not found -> return false
       2) leaf + found     -> return true
       3) internal + not found -> recurse subset[i]
       4) internal + found     -> return true
       ============================================================ */
    bool search(Node* n, int x) const {
        int i = first_ge(n->key, x);//在节点n的键数组中找到第一个大于或等于x的键的位置i。
        bool found = (i < (int)n->key.size() && n->key[i] == x);//检查位置i是否在键数组的范围内，并且n->key[i]是否等于x，如果是，则说明找到了键x，found为true；否则，found为false。

        if (n->leaf) {
            // Case 1 and Case 2: 叶子节点，如果没有找到，返回false；如果找到了，返回true。
            return found;
        } else {//如果是内部节点：
            if (found) {
                // Case 4: 内部节点，如果找到了，返回true。
                return true;
            }
            // Case 3: 内部节点，如果没有找到，递归地在子节点n->child[i]中继续搜索。因为第i个子节点包含了所有键值在n->key[i-1]和n->key[i]之间的键值（如果i=0，则表示小于n->key[0]的键值；如果i=n->key.size()，则表示大于n->key.back()的键值）。
            //举个例子，如果n->key = [300, 500, 700]，我们要搜索400，那么i = first_ge(n->key, 400)会返回1，因为400是第一个大于或等于500的元素，所以我们应该在n->child[2]中继续搜索。
            //                    /   ｜   ｜    \
            //                 C0    C1   C2    C3
            return search(n->child[i], x);
        }
    }

    /* ============================================================
       INSERT (loose): may temporarily allow max_keys+1 keys in a child
       ============================================================ */
    void loose_insert(Node* n, int x) {//loose insert的意思是如果在插入过程中某个节点的键数超过了max_keys，我们暂时允许它存在max_keys + 1个键，之后再通过fix_excess函数来修复这个问题，也就是把中间的键提升到父节点，并将当前节点分裂成两个节点。这样做的好处是简化了插入逻辑，使得我们不需要在每次插入时都检查和处理节点是否已经满了，而是等到最后再统一处理。
        int i = first_ge(n->key, x);//在节点n的键数组中找到第一个大于或等于x的键的位置i。

        // Ignore duplicates (optional)
        if (i < (int)n->key.size() && n->key[i] == x) return;//检查位置i是否在键数组的范围内，并且n->key[i]是否等于x，如果是，则说明找到了键x，这是一个重复的键，我们选择忽略它，不进行插入，直接返回。

        if (n->leaf) {//如果当前节点是叶子节点，我们直接在位置i插入x到n->key中，并返回。这里我们使用vector的insert方法，在n->key的begin() + i的位置插入x，这样可以保持n->key的有序性。
            // Insert into partially filled key array
            n->key.insert(n->key.begin() + i, x);
            return; // may overflow; parent fixes
        }

        // Recurse into exactly one child
        loose_insert(n->child[i], x);//如果当前节点不是叶子节点，我们递归地在第i个子节点n->child[i]中继续插入x。例如：如果n->key = [300, 500, 700]，我们要插入400，那么i = first_ge(n->key, 400)会返回1，因为400是第一个大于或等于500的元素，所以我们应该在n->child[1]中继续插入400。

        // Fix child overflow if needed
        if ((int)n->child[i]->key.size() > max_keys) {//如果在插入之后，子节点n->child[i]的键数超过了max_keys，也就是超过了B树的阶数限制，我们需要修复这个问题。
            fix_excess(n, i);// 子节点溢出，修复
        }
    }

    void fix_excess(Node* parent, int i) {//fix_excess函数的作用是修复父节点parent的第i个子节点（也就是parent->child[i]）的键数超过max_keys的问题。这个函数会将子节点分裂成两个节点，并将中间的键提升到父节点中，从而保持B树的性质。
        Node* left = parent->child[i];      // overflowing child //溢出的子节点，left是指向parent->child[i]的指针，也就是需要修复的子节点。这个子节点的键数已经超过了max_keys，我们需要对它进行分裂。   
        Node* right = new Node(left->leaf); // new sibling //创建一个新的节点right，它的leaf属性与left相同。这个节点将成为left的兄弟节点，用于存储分裂后的一部分键值。

        int mid = (int)left->key.size() / 2;   // median index //中间键的下标
        int promote = left->key[mid];          // median key to promote // 要提升到父节点的键

        // right gets keys after median
        right->key.assign(left->key.begin() + mid + 1, left->key.end());//将中间键之后的键值分配给right节点。我们使用vector的assign方法，将left->key中从mid + 1开始到end的键值复制到right->key中。这样，right节点就获得了原来left节点中位于中间键之后的所有键值。
        // left keeps keys before median
        left->key.erase(left->key.begin() + mid, left->key.end());//将中间键之前的键值保留在left节点中。我们使用vector的erase方法，将left->key中从mid开始到end的键值删除，这样left节点就只保留了原来left节点中位于中间键之前的所有键值（不包括中间键本身，因为它要提升到父节点）。

        // split children if internal
        if (!left->leaf) {// 分裂内部节点时，子节点指针也要分裂
            right->child.assign(left->child.begin() + mid + 1, left->child.end());//如果left节点为内部节点，我们还需要将left节点的子节点指针分裂给right节点。我们使用vector的assign方法，将left->child中从mid + 1开始到end的子节点指针复制到right->child中。这样，right节点就获得了原来left节点中位于中间键之后的所有子节点指针。
            left->child.erase(left->child.begin() + mid + 1, left->child.end());//我们使用vector的erase方法，将left->child中从mid + 1开始到end的子节点指针删除，这样left节点就只保留了原来left节点中位于中间键之前的所有子节点指针（不包括中间键对应的子节点，因为它要提升到父节点）。同时，我们将right节点的leaf属性设置为false，因为它现在是一个内部节点。
        }

        // insert promoted key into parent and right pointer into parent children//将提升的键插入到父节点中，并将right节点的指针插入到父节点的子节点指针中。我们首先找到提升的键在父节点中的位置p，这个位置是第一个大于或等于promote的键的位置。然后，我们在父节点的key数组中插入promote，在child数组中插入right指针。最后，我们将父节点的leaf属性设置为false，因为它现在是一个内部节点。
        int p = first_ge(parent->key, promote);//在父节点的键数组中找到第一个大于或等于中位键promote的键的位置p。
        parent->key.insert(parent->key.begin() + p, promote);//在父节点的key数组中插入promote，在位置p插入，这样可以保持父节点的键数组的有序性。
        parent->child.insert(parent->child.begin() + (p + 1), right);//在父节点的child数组中插入right指针，在位置p + 1插入，因为right节点是位于promote键之后的子节点。
        parent->leaf = false;//将父节点的leaf属性设置为false，因为它现在是一个内部节点。
    }
    /*
    假设场景：max_keys = 3，某个子节点已经有4个键溢出了：
    parent:  [300, 700]
          /    |    \
        C0   left   C2
            [400,500,600,650]   ← 溢出了！
    Step 1：找中间键
    int mid = left->key.size() / 2;  // 4/2 = 2
    int promote = left->key[mid];    // key[2] = 600，提升到父节点
    Step 2：分裂左右
    right->key = [650]          // mid+1 之后的
    left->key  = [400, 500]     // mid 之前的（mid本身被提走了）
    Step 3：如果是内部节点，子指针也要分裂
    right->child = left->child 从 mid+1 开始的部分
    left->child  = left->child 保留到 mid+1（包含）
    Step 4：把 promote 插入父节点，right 挂到父节点
    int p = first_ge(parent->key, 600);  // p = 1，因为600在300和700之间
    parent->key.insert(p, 600);          // parent->key = [300, 600, 700]
    parent->child.insert(p+1, right);    // right挂在600右边
    **最终结果：**
    parent:  [300, 600, 700]
            /    |    |    \
            C0  left  right  C2
            [400  [650]
            ,500]
    */

    /* ============================================================
       DELETE (loose): four cases (as in your slides) + fix_shortage
       1) leaf + not found -> return false
       2) leaf + found     -> erase key, return true
       3) internal + not found -> recurse subset[i], then fix_shortage if needed
       4) internal + found -> replace with predecessor (or successor), recurse delete, fix_shortage
       ============================================================ */

    // Remove and return predecessor (max key) from subtree rooted at n.
    //找到并删除子树中的最大键（前驱），用于 Case 4 的替换。一路沿最右子节点递归到叶子，删除最后一个键并返回。
    int remove_predecessor(Node* n) {
        if (n->leaf) {//如果当前节点是叶子节点
            int k = n->key.back();//获取最后一个键，也就是当前子树中的最大键（前驱）。
            n->key.pop_back();//从当前节点的键数组中删除最后一个键。
            return k;//返回被删除的键值。
        }
        int last = (int)n->child.size() - 1;//最后一个子节点的索引，也就是最右边的子节点。
        int k = remove_predecessor(n->child[last]);//递归地在最后一个子节点中继续寻找前驱，并删除它。这个过程会一直沿着最右边的子节点进行，直到到达叶子节点。
        if ((int)n->child[last]->key.size() < min_keys) {//在删除前驱后，检查最后一个子节点的键数是否小于min_keys，如果是，则需要修复这个问题。
            fix_shortage(n, last);//调用fix_shortage函数来修复父节点n的第last个子节点（也就是n->child[last]）的键数不足的问题。这个函数会尝试从兄弟节点借键，或者合并节点，以保持B树的性质。
        }
        return k;
    }

    bool loose_remove(Node* n, int x) {//loose remove的意思是如果在删除过程中某个节点的键数少于min_keys，我们暂时允许它存在少于min_keys个键，之后再通过fix_shortage函数来修复这个问题，也就是从兄弟节点借键或者合并节点。这样做的好处是简化了删除逻辑，使得我们不需要在每次删除时都检查和处理节点是否已经不足了，而是等到最后再统一处理。
        int i = first_ge(n->key, x);//在节点n的键数组中找到第一个大于或等于x的键的位置i。
        bool found = (i < (int)n->key.size() && n->key[i] == x);//检查位置i是否在键数组的范围内，并且n->key[i]是否等于x，如果是，则说明找到了键x，found为true；否则，found为false。

        if (n->leaf) {//如果当前节点是叶子节点：
            // Case 1 and Case 2
            if (!found) return false;                 // Case 1: 没找到，返回false
            n->key.erase(n->key.begin() + i);         // Case 2: 找到了，删除键并返回true
            return true;
        }

        if (!found) {
            // Case 3: recurse into subset[i]
            bool removed = loose_remove(n->child[i], x);//如果当前节点不是叶子节点，并且没有找到键x，我们递归地在第i个子节点n->child[i]中继续删除x。例如：如果n->key = [300, 500, 700]，我们要删除400，那么i = first_ge(n->key, 400)会返回1，因为400是第一个大于或等于500的元素，所以我们应该在n->child[1]中继续删除400。

            // fix shortage on the way back up
            if ((int)n->child[i]->key.size() < min_keys) {//在删除之后，子节点n->child[i]的键数可能会少于min_keys，也就是不满足B树的性质，我们需要修复这个问题。
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
        if (i > 0) {//如果i > 0，说明存在左兄弟节点，我们可以尝试从左兄弟节点借键。
            Node* L = parent->child[i - 1];//左兄弟节点的指针，L是parent->child[i - 1]，也就是c的左兄弟节点。
            if ((int)L->key.size() > min_keys) {//如果左兄弟节点的键数大于min_keys，说明左兄弟节点有多余的键可以借给c，我们可以通过旋转来调整键值。
                // Rotate right
                c->key.insert(c->key.begin(), parent->key[i - 1]);//将父节点parent的第i-1个键插入到c的键数组的开头，这样c就获得了一个新的键。
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
