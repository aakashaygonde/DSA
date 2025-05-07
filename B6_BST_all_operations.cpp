/*
B6 : 
        "Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given. After constructing a binary tree - i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data value found in the tree, iv. Change a tree so that the roles of the left and right pointers are swapped at every node, v. Search a value"
*/
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BST {
    Node* root;

    Node* insert(Node* root, int value) {
        if (root == nullptr)
            return new Node(value);

        if (value < root->data)
            root->left = insert(root->left, value);
        else if (value > root->data)
            root->right = insert(root->right, value);

        return root;
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    int height(Node* root) {
        if (root == nullptr) return 0;
        int lh = height(root->left);
        int rh = height(root->right);
        return 1 + max(lh, rh);
    }

    int findMin(Node* root) {
        if (!root) return -1;
        while (root->left)
            root = root->left;
        return root->data;
    }

    void mirror(Node* root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }

    bool search(Node* root, int value) {
        if (root == nullptr) return false;
        if (value == root->data) return true;
        if (value < root->data)
            return search(root->left, value);
        else
            return search(root->right, value);
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void displayInorder() {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << endl;
    }

    void findHeight() {
        cout << "Longest path from root (height): " << height(root) << endl;
    }

    void findMinValue() {
        int minVal = findMin(root);
        if (minVal != -1)
            cout << "Minimum value in tree: " << minVal << endl;
        else
            cout << "Tree is empty.\n";
    }

    void mirrorTree() {
        mirror(root);
        cout << "Tree has been mirrored.\n";
    }

    void searchValue(int value) {
        bool found = search(root, value);
        if (found)
            cout << value << " is found in the tree.\n";
        else
            cout << value << " is not found in the tree.\n";
    }
};

// ---------- MAIN FUNCTION ----------
int main() {
    BST tree;
    int n, value, choice;

    cout << "Enter number of initial nodes to insert: ";
    cin >> n;
    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insert(value);
    }

    do {
        cout << "\n--- BST Operations Menu ---\n";
        cout << "1. Insert new node\n";
        cout << "2. Display inorder\n";
        cout << "3. Find longest path from root (height)\n";
        cout << "4. Find minimum data value\n";
        cout << "5. Mirror the tree\n";
        cout << "6. Search a value\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            tree.displayInorder();
            break;
        case 3:
            tree.findHeight();
            break;
        case 4:
            tree.findMinValue();
            break;
        case 5:
            tree.mirrorTree();
            break;
        case 6:
            cout << "Enter value to search: ";
            cin >> value;
            tree.searchValue(value);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
