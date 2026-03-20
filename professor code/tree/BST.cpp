#include <iostream>
using namespace std;

template <class Item>
class BinaryTreeNode {
public:
    Item data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    explicit BinaryTreeNode(const Item& val)//传入的是引用，避免不必要的拷贝
        : data(val), left(nullptr), right(nullptr) {}
};

template <class Item>
void insert(BinaryTreeNode<Item>*& root, const Item& val) {
    if (root == nullptr) {
        root = new BinaryTreeNode<Item>(val);
        return;
    }
    if (val < root->data) {
        insert(root->left, val);
    } else if (val > root->data) {
        insert(root->right, val);
    }
}

template <class Item>
bool search(BinaryTreeNode<Item>* root, const Item& val) {
    if (root == nullptr) {
        return false;
    }
    if (val == root->data) {
        return true;
    }
    else if (val < root->data) {
        return search(root->left, val);
    }
    else {
        return search(root->right, val);
    }
}

template <class Item>
void remove(BinaryTreeNode<Item>*& root, const Item& target) {
    if (root == nullptr) {
        return; // Tree is empty or target not found
    }
    if (target < root->data) {
        remove(root->left, target);
    }
    else if (target > root->data) {
        remove(root->right, target);
    }
    else {
        // Target found

        // Case 1: leaf node
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }

        // Case 2: one right child
        else if (root->left == nullptr) {
            BinaryTreeNode<Item>* temp = root->right;//保存右子节点指针
            delete root;//删除当前节点
            root = temp;//将当前节点指向右子节点
        }

        // Case 3: one left child
        else if (root->right == nullptr) {
            BinaryTreeNode<Item>* temp = root->left;//保存左子节点指针
            delete root;//删除当前节点
            root = temp;//将当前节点指向左子节点
        }
        else {//如果有两个子节点，那么要找到这个节点右边的树的最小值来替换当前节点
            // Case 4: two children
            // Find the inorder successor (minimum in right subtree)
            BinaryTreeNode<Item>* successor = root->right;//当前节点的右子节点
            while (successor->left != nullptr) {//用while循环不断往左找到右子树的最小值
                successor = successor->left;
            }
            // Copy the inorder successor's data to this node//直接把当前节点的值改成右子树最小值
            root->data = successor->data;
            // Delete the inorder successor
            remove(root->right, successor->data);//递归删除右子树中的最小值节点
        }
    }
}

template <class Item>
void destroy(BinaryTreeNode<Item>* root) {
    if (root == nullptr) {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}
template <class Item>
void preorder(BinaryTreeNode<Item>* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

template <class Item>
void inorder(BinaryTreeNode<Item>* root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

template <class Item>
void postorder(BinaryTreeNode<Item>* root) {
    if (root == nullptr) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

template <class Item>
int countNodes(BinaryTreeNode<Item>* root) {
    if (root == nullptr)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

template <class Item>
int treeHeight(BinaryTreeNode<Item>* root) {
    if (root == nullptr)
        return 0;
    int leftHeight = treeHeight(root->left);//递归计算左子树高度
    int rightHeight = treeHeight(root->right);//递归计算右子树高度
    return 1 + max(leftHeight, rightHeight);
}

int main() {
    BinaryTreeNode<int>* root = nullptr;

    insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    cout << "Search 40: " << (search(root, 40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (search(root, 90) ? "Found" : "Not Found") << endl;

    cout << "Total nodes: " << countNodes(root) << endl;
    cout << "Tree height: " << treeHeight(root) << endl;

    remove(root, 20);
    cout << "Inorder traversal after deleting 20: ";
    inorder(root);
    cout << endl;

    remove(root, 30);
    cout << "Inorder traversal after deleting 30: ";
    inorder(root);
    cout << endl;

    remove(root, 50);
    cout << "Inorder traversal after deleting 50: ";
    inorder(root);
    cout << endl;

    destroy(root);
    return 0;
}