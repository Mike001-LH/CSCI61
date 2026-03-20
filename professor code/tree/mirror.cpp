#include <iostream>
using namespace std;

struct tree_node {
    int data;
    tree_node* left_field;
    tree_node* right_field;

    explicit tree_node(int val)
        : data(val), left_field(nullptr), right_field(nullptr) {}
};

bool mirror(const tree_node* a, const tree_node* b) {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;

    return mirror(a->left_field,  b->right_field) &&
           mirror(a->right_field, b->left_field);
}
