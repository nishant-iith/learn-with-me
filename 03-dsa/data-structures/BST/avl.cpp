#include<bits/stdc++.h>
using namespace std;

/**
 * AVL Tree Node
 */
class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height; 

    // constructor
    Node(int val){
        this->key = val;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

/**
 * AVL Tree Class
 */
class AVL {
private:
    Node* root; // Pointer to the root node;
    
    int height(Node* N){
        if(N == nullptr) return 0;
        return N->height;
    }

    int getBalance(Node* N){
        if(N == nullptr) return 0;
        return height(N->left) - height(N->right); // if B > 1 => Left heavy, if B < -1 => Right heavy
    }

    /**
     * Rotations : 
     * 1. Right Rotate
     * 2. Left Rotate
     * 3. Left-Right Rotate
     * 4. Right-Left Rotate
     */

     // Right Rotate
    Node* rightRotate(Node* x){
        Node* x1 = x->right, *y = x1->left, *y1 = x->left->right;
        // right rotate;
        x->left = y1;
        y->right = x;
        // update heights
        x->height = max(height((x->left)), height((x->right))) + 1;
        y->height = max(height((y->left)), height((y->right))) + 1;
        return y; // new root
    }
};