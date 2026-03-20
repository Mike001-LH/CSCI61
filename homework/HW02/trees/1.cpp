/*
Implementation Choices:
I used a struct to define the binary tree node, then I used recursive functions and some idea found on ppt to implement preorder and postorder traversals.

Challenges Encountered:
I have to think how to manage the recursive calls to achieve the effect of preorder and postorder traversals correctly.
*/


#include <iostream>
using namespace std;

//1.	Traverse and output the nodes in preorder.
//2.	Traverse and output the nodes in postorder.

struct binaryTreeNode {
    char data;
    binaryTreeNode* leftChild;
    binaryTreeNode* rightChild;
    binaryTreeNode(const char& value) : data(value), leftChild(nullptr), rightChild(nullptr) {}
};

void preOrder(binaryTreeNode* node) {
    if (node == nullptr) {
        return;
    }
    cout << node->data << " ";
    preOrder(node->leftChild);
    preOrder(node->rightChild);
}

void postOrder(binaryTreeNode* node) {
    if (node == nullptr) {
        return;
    }
    postOrder(node->leftChild);
    postOrder(node->rightChild);
    cout << node->data << " ";
}

int main(){
    // Binary Tree is
    //         A
    //       /   \
    //      L     G
    //     / \   / \
    //    O   R  I  T
    //   / \  /
    //  H   M S
    binaryTreeNode* root = new binaryTreeNode('A');
    root->leftChild = new binaryTreeNode('L');
    root->rightChild = new binaryTreeNode('G');
    root->leftChild->leftChild = new binaryTreeNode('O');
    root->leftChild->rightChild = new binaryTreeNode('R');
    root->rightChild->leftChild = new binaryTreeNode('I');
    root->rightChild->rightChild = new binaryTreeNode('T');
    root->leftChild->leftChild->leftChild = new binaryTreeNode('H');
    root->leftChild->leftChild->rightChild = new binaryTreeNode('M');
    root->leftChild->rightChild->leftChild = new binaryTreeNode('S');
    cout << "Preorder Traversal: ";
    preOrder(root);
    cout << endl;
    cout << "Postorder Traversal: ";
    postOrder(root);
    cout << endl;
    return 0;
}
// Output:
// Preorder Traversal: A L O H M R S G I T
// Postorder Traversal: H M O S R L I T G A