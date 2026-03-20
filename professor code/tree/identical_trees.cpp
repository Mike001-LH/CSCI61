#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool isIdentical(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr)
        return true;

    if (p == nullptr || q == nullptr)
        return false;

    return (p->val == q->val) &&
           isIdentical(p->left, q->left) &&
           isIdentical(p->right, q->right);
}

int main() {
    TreeNode* t1 = new TreeNode(1);
    t1->left = new TreeNode(2);
    t1->right = new TreeNode(3);

    TreeNode* t2 = new TreeNode(1);
    t2->left = new TreeNode(2);
    t2->right = new TreeNode(3);

    cout << (isIdentical(t1, t2) ? "Identical" : "Not Identical") << endl;
    return 0;
}
