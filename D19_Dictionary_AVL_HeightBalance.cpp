/*
D19 : 
        " A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword"
*/

#include <iostream>
using namespace std;

struct Node {
    string keyword, meaning;
    Node *left, *right;
    int height;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, string key, string meaning) {
    if (!node) return new Node(key, meaning);
    if (key < node->keyword)
        node->left = insert(node->left, key, meaning);
    else if (key > node->keyword)
        node->right = insert(node->right, key, meaning);
    else {
        cout << "Keyword already exists. Use update.\n";
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->keyword)
        return rotateRight(node);
    if (balance < -1 && key > node->right->keyword)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->keyword) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->keyword) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, string key) {
    if (!root) return root;
    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) return nullptr;
            *root = *temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* update(Node* root, string key, string newMeaning) {
    if (!root) return nullptr;
    if (key == root->keyword) {
        root->meaning = newMeaning;
        return root;
    } else if (key < root->keyword)
        return update(root->left, key, newMeaning);
    else
        return update(root->right, key, newMeaning);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->keyword << " : " << root->meaning << endl;
    inorder(root->right);
}

void reverseInorder(Node* root) {
    if (!root) return;
    reverseInorder(root->right);
    cout << root->keyword << " : " << root->meaning << endl;
    reverseInorder(root->left);
}

bool search(Node* root, string key, int &comparisons) {
    comparisons++;
    if (!root) return false;
    if (key == root->keyword) return true;
    if (key < root->keyword)
        return search(root->left, key, comparisons);
    else
        return search(root->right, key, comparisons);
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\nMenu:\n1. Add\n2. Delete\n3. Update\n4. Display Ascending\n5. Display Descending\n6. Search\n7. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, key, meaning);
                break;

            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;

            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                if (update(root, key, meaning))
                    cout << "Updated.\n";
                else
                    cout << "Keyword not found.\n";
                break;

            case 4:
                cout << "Dictionary in Ascending order:\n";
                inorder(root);
                break;

            case 5:
                cout << "Dictionary in Descending order:\n";
                reverseInorder(root);
                break;

            case 6:
                cout << "Enter keyword to search: ";
                cin >> key;
                int comparisons = 0;
                if (search(root, key, comparisons))
                    cout << "Found in " << comparisons << " comparisons.\n";
                else
                    cout << "Not found. Comparisons made: " << comparisons << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}
