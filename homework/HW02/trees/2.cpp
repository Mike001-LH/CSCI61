/*
Implementation Choices:
I used recursive functions to implement the binary search tree insertion by comparing and inserting smaller values to the left and larger values to the right. 
For searching, I also used recursion to traverse the tree based on comparisons.

Challenges Encountered:
I found it challanging to manage the input reading in main function, so I found that cin.peek() can help to check for newline character to stop reading the first line.
*/

/*
2 . [20 points] Monica, Chandler and Joey are hosting a party.
Monica, Chandler and Joey are hosting a party. There are currently N guests at the party. Each guest was given a placard with a number as they arrived. Monica being the organizer that she is, arranged all the guests analogous to a binary search tree with each of its nodes as a guest holding a placard. There are still M more guests to come. As one of the M guests arrive, they choose an arbitrary integer X, and they wish to be seated with a guest who has number X on their placard. Joey who is acting as a gatekeeper either lets a guest in if a guest with X on their placard exists in the party or sends the guest away if no one in the party has X on their placard. Every time, Joey asks Chandler to go look for the guest with X on their placard and shout YES or NO. Write a C++ program that helps Chandler to look for the guest in the most efficient way possible.

Possible Input:

45 27 14 23 48 46 52 50

9 11 45 14 23 34

Possible Output:

No No Yes Yes Yes No

First line of input contains the numbers on placards of N guests in the party. Second line of input represents the numbers that the M guests have picked. Here N is 8 and M is 6. Output is the corresponding Yes or No for each input of M. 
*/
#include <iostream>
using namespace std;

struct binaryTreeNode {
    int data;
    binaryTreeNode* leftChild;
    binaryTreeNode* rightChild;
    binaryTreeNode(const int& value) : data(value), leftChild(nullptr), rightChild(nullptr) {}
};

binaryTreeNode* insert(binaryTreeNode* root, const int& value) {
    if (root == nullptr) {
        return new binaryTreeNode(value);
    }
    if (value < root->data) {
        root->leftChild = insert(root->leftChild, value);
    }
    else if (value > root->data) {
        root->rightChild = insert(root->rightChild, value);
    }
    return root;
}

bool search(binaryTreeNode* root, const int& value) {
    if (root == nullptr) {
        return false;
    }
    if (root->data == value) {
        return true;
    }
    if (value < root->data) {
        return search(root->leftChild, value);
    }
    else {
        return search(root->rightChild, value);
    }
}

void deleteTree(binaryTreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->leftChild);
    deleteTree(root->rightChild);
    delete root;
}

int main() {
    binaryTreeNode* root = nullptr;
    int value;
    
    // read N guest placard numbers and build the BST
    cout << "Enter placard numbers of current guests: " << endl;
    while (cin >> value) {//continue reading until the line ends
        root = insert(root, value);//insert value into the BST
        if (cin.peek() == '\n') break; //如果遇到换行符则停止读取,cin.peek()查看下一个字符但不提取它// check if the next character is a newline
    }
    // read M guest placard numbers and search in the BST
    cout << "Enter placard numbers of arriving guests: " << endl;
    bool firstOutput = true;
    while (cin >> value) {
        if(!firstOutput) {
            cout << " ";
        }
        if(search(root, value)){
            cout << "Yes";
        } else {
            cout << "No";
        }
        firstOutput = false;
    }
    cout << endl;

    deleteTree(root);//free allocated memory
    return 0;
}