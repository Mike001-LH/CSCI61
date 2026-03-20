#include <iostream>
#include <queue>

using namespace std;

// Define the binary_tree_node template class
template <class Item>
class binary_tree_node {
public:
    Item data_field;
    binary_tree_node* left_field;
    binary_tree_node* right_field;

    explicit binary_tree_node(const Item& item)//explicit的作用是防止单参数构造函数被隐式调用，隐式类型转换的意思是防止编译器自动将其他类型转换为该类型，从而避免潜在的错误
        : data_field(item), left_field(nullptr), right_field(nullptr) {}
};

// Insert a value into the binary tree using level-order insertion
template <class Item>
void insert(binary_tree_node<Item>*& root, const Item& val) {
    if (root == nullptr) {
        root = new binary_tree_node<Item>(val);//如果当前节点为空，创建新节点
        return;
    }

    queue<binary_tree_node<Item>*> nodeQueue;//
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        binary_tree_node<Item>* current = nodeQueue.front();
        nodeQueue.pop();

        if (current->left_field == nullptr) {
            current->left_field = new binary_tree_node<Item>(val);
            return;
        } else {
            nodeQueue.push(current->left_field);
        }

        if (current->right_field == nullptr) {
            current->right_field = new binary_tree_node<Item>(val);
            return;
        } else {
            nodeQueue.push(current->right_field);
        }
    }
}

// In-order traversal
template <class Item>
void inOrderTraversal(binary_tree_node<Item>* root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left_field);
    cout << root->data_field << " ";
    inOrderTraversal(root->right_field);
}

// Cleanup
template <class Item>
void destroy(binary_tree_node<Item>* root) {
    if (root == nullptr) {
        return;
    }
    destroy(root->left_field);
    destroy(root->right_field);
    delete root;
}

template <class Item>
void remove(binary_tree_node<Item>*& root, const Item& target) {
    if (root == nullptr) {
        return; // Tree is empty or target not found
    }

    if (target < root->data_field) {
        remove(root->left_field, target);
    }
    else if (target > root->data_field) {
        remove(root->right_field, target);
    }
    else {
        // Target found

        // Case 1: leaf node
        if (root->left_field == nullptr && root->right_field == nullptr) {
            delete root;
            root = nullptr;
        }
        // Case 2: one right child
        else if (root->left_field == nullptr) {
            binary_tree_node<Item>* temp = root;
            root = root->right_field;
            delete temp;
        }
        // Case 2: one left child
        else if (root->right_field == nullptr) {
            binary_tree_node<Item>* temp = root;
            root = root->left_field;
            delete temp;
        }
        // Case 3: two children
        else {
            // Find in-order successor (minimum in right subtree)
            binary_tree_node<Item>* successor = root->right_field;
            while (successor->left_field != nullptr) {
                successor = successor->left_field;
            }

            // Copy successor's data to current node
            root->data_field = successor->data_field;

            // Remove successor
            remove(root->right_field, successor->data_field);
        }
    }
}


int main() {
    binary_tree_node<int>* root = nullptr;

    insert(root, 1);
    insert(root, 2);
    insert(root, 3);
    insert(root, 4);
    insert(root, 5);
    insert(root, 6);
    insert(root, 7);

    cout << "In-order Traversal of the Constructed Tree: ";
    inOrderTraversal(root);
    cout << endl;

    destroy(root);
    return 0;
}
