#include <bits/stdc++.h>
using namespace std;

class Node {
private:
    int data;
    Node* left;
    Node* right;

public:
    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }

    int getData() { return this->data; }
    Node* getLeft() { return this->left; }
    Node* getRight() { return this->right; }

    void setLeft(Node* left) { this->left = left; }
    void setRight(Node* right) { this->right = right; }
    void setData(int data) { this->data = data; }
};

class BST {
private:
    Node* root;

    // Helper: Insert a node recursively
    Node* insertHelper(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->getData()) {
            node->setLeft(insertHelper(node->getLeft(), val));
        } else if (val > node->getData()) {
            node->setRight(insertHelper(node->getRight(), val));
        }
        // If val == node->getData(), we don't insert duplicates
        return node;
    }

    // Helper: Find minimum value node in a subtree
    Node* findMin(Node* node) {
        while (node && node->getLeft() != nullptr) {
            node = node->getLeft();
        }
        return node;
    }

    // Helper: Find maximum value node in a subtree
    Node* findMax(Node* node) {
        while (node && node->getRight() != nullptr) {
            node = node->getRight();
        }
        return node;
    }

    // Helper: Delete a node recursively (returns new root of subtree)
    Node* deleteHelper(Node* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }

        if (val < node->getData()) {
            node->setLeft(deleteHelper(node->getLeft(), val));
        } else if (val > node->getData()) {
            node->setRight(deleteHelper(node->getRight(), val));
        } else {
            // Node found - handle three cases

            // Case 1: Leaf node (no children)
            if (node->getLeft() == nullptr && node->getRight() == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: One child (right only)
            else if (node->getLeft() == nullptr) {
                Node* temp = node->getRight();
                delete node;
                return temp;
            }

            // Case 2: One child (left only)
            else if (node->getRight() == nullptr) {
                Node* temp = node->getLeft();
                delete node;
                return temp;
            }

            // Case 3: Two children
            // Find inorder successor (smallest in right subtree)
            else {
                Node* successor = findMin(node->getRight());
                node->setData(successor->getData());
                node->setRight(deleteHelper(node->getRight(), successor->getData()));
            }
        }

        return node;
    }

    // Helper: Search for a node
    Node* searchHelper(Node* node, int val) {
        if (node == nullptr || node->getData() == val) {
            return node;
        }

        if (val < node->getData()) {
            return searchHelper(node->getLeft(), val);
        }
        return searchHelper(node->getRight(), val);
    }

    // Helper: Inorder traversal (Left, Root, Right)
    void inorderHelper(Node* node) {
        if (node == nullptr) return;

        inorderHelper(node->getLeft());
        cout << node->getData() << " ";
        inorderHelper(node->getRight());
    }

    // Helper: Preorder traversal (Root, Left, Right)
    void preorderHelper(Node* node) {
        if (node == nullptr) return;

        cout << node->getData() << " ";
        preorderHelper(node->getLeft());
        preorderHelper(node->getRight());
    }

    // Helper: Postorder traversal (Left, Right, Root)
    void postorderHelper(Node* node) {
        if (node == nullptr) return;

        postorderHelper(node->getLeft());
        postorderHelper(node->getRight());
        cout << node->getData() << " ";
    }

    // Helper: Calculate height of tree
    int heightHelper(Node* node) {
        if (node == nullptr) {
            return -1;  // Height of empty tree is -1
        }

        int leftHeight = heightHelper(node->getLeft());
        int rightHeight = heightHelper(node->getRight());

        return max(leftHeight, rightHeight) + 1;
    }

    // Helper: Count total nodes
    int countNodesHelper(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodesHelper(node->getLeft()) + countNodesHelper(node->getRight());
    }

    // Helper: Count leaf nodes
    int countLeavesHelper(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            return 1;
        }
        return countLeavesHelper(node->getLeft()) + countLeavesHelper(node->getRight());
    }

    // Helper: Validate if tree is a valid BST
    bool isBSTHelper(Node* node, int minVal, int maxVal) {
        if (node == nullptr) {
            return true;
        }

        if (node->getData() <= minVal || node->getData() >= maxVal) {
            return false;
        }

        return isBSTHelper(node->getLeft(), minVal, node->getData()) && isBSTHelper(node->getRight(), node->getData(), maxVal);
    }

    // Helper: Destroy tree (for destructor)
    void destroyTree(Node* node) {
        if (node == nullptr) return;

        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
    }

    // Helper: Display tree structure
    void displayHelper(Node* node, int space) {
        if (node == nullptr) return;

        space += 5;

        displayHelper(node->getRight(), space);

        cout << endl;
        for (int i = 5; i < space; i++) {
            cout << " ";
        }
        cout << node->getData() << endl;

        displayHelper(node->getLeft(), space);
    }

public:
    // Constructor
    BST() {
        this->root = nullptr;
    }

    // Destructor
    ~BST() {
        destroyTree(root);
    }

    // Insert a value
    void insert(int val) {
        root = insertHelper(root, val);
    }

    // Delete a value
    void deleteNode(int val) {
        root = deleteHelper(root, val);
    }

    // Search for a value
    bool search(int val) {
        return searchHelper(root, val) != nullptr;
    }

    // Update: delete old value and insert new value
    void update(int oldVal, int newVal) {
        if (search(oldVal)) {
            deleteNode(oldVal);
            insert(newVal);
        } else {
            cout << "Value " << oldVal << " not found in tree!" << endl;
        }
    }

    // Inorder traversal (gives sorted order)
    void inorder() {
        cout << "Inorder: ";
        inorderHelper(root);
        cout << endl;
    }

    // Preorder traversal
    void preorder() {
        cout << "Preorder: ";
        preorderHelper(root);
        cout << endl;
    }

    // Postorder traversal
    void postorder() {
        cout << "Postorder: ";
        postorderHelper(root);
        cout << endl;
    }

    // Level order traversal (BFS)
    void levelOrder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        cout << "Level Order: ";
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->getData() << " ";

            if (current->getLeft() != nullptr) {
                q.push(current->getLeft());
            }
            if (current->getRight() != nullptr) {
                q.push(current->getRight());
            }
        }
        cout << endl;
    }

    // Get minimum value in tree
    int getMin() {
        if (root == nullptr) {
            throw runtime_error("Tree is empty!");
        }
        return findMin(root)->getData();
    }

    // Get maximum value in tree
    int getMax() {
        if (root == nullptr) {
            throw runtime_error("Tree is empty!");
        }
        return findMax(root)->getData();
    }

    // Get height of tree
    int height() {
        return heightHelper(root);
    }

    // Count total nodes
    int countNodes() {
        return countNodesHelper(root);
    }

    // Count leaf nodes
    int countLeaves() {
        return countLeavesHelper(root);
    }

    // Check if tree is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Validate if tree is a valid BST
    bool isBST() {
        return isBSTHelper(root, INT_MIN, INT_MAX);
    }

    // Display tree structure
    void display() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        cout << "Tree Structure:" << endl;
        displayHelper(root, 0);
    }
};

// Main function with comprehensive testing
int main() {
    BST tree;

    cout << "=== Binary Search Tree Implementation ===" << endl << endl;

    // Test insertion
    cout << "Inserting: 50, 30, 70, 20, 40, 60, 80" << endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Display tree
    tree.display();
    cout << endl;

    // Test traversals
    tree.inorder();
    tree.preorder();
    tree.postorder();
    tree.levelOrder();
    cout << endl;

    // Test search
    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;
    cout << endl;

    // Test min/max
    cout << "Minimum value: " << tree.getMin() << endl;
    cout << "Maximum value: " << tree.getMax() << endl;
    cout << endl;

    // Test height and counts
    cout << "Height of tree: " << tree.height() << endl;
    cout << "Total nodes: " << tree.countNodes() << endl;
    cout << "Leaf nodes: " << tree.countLeaves() << endl;
    cout << "Is valid BST: " << (tree.isBST() ? "Yes" : "No") << endl;
    cout << endl;

    // Test update
    cout << "Updating 30 to 35" << endl;
    tree.update(30, 35);
    tree.inorder();
    cout << endl;

    // Test deletion
    cout << "Deleting 20 (leaf node)" << endl;
    tree.deleteNode(20);
    tree.inorder();

    cout << "Deleting 70 (node with two children)" << endl;
    tree.deleteNode(70);
    tree.inorder();

    cout << "Deleting 35 (node with one child)" << endl;
    tree.deleteNode(35);
    tree.inorder();
    cout << endl;

    // Final tree structure
    tree.display();

    return 0;
}
