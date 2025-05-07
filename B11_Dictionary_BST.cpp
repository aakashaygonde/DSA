/*
"A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Binary Search Tree for implementation."
*/
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;

    Node(string key, string mean) {
        keyword = key;
        meaning = mean;
        left = right = nullptr;
    }
};

class Dictionary {
    Node* root;

    Node* insert(Node* root, string key, string mean) {
        if (root == nullptr) {
            return new Node(key, mean);
        }
        if (key < root->keyword) {
            root->left = insert(root->left, key, mean);
        } else if (key > root->keyword) {
            root->right = insert(root->right, key, mean);
        } else {
            cout << "Keyword already exists.\n";
        }
        return root;
    }

    Node* findMin(Node* root) {
        while (root->left != nullptr)
            root = root->left;
        return root;
    }

    Node* remove(Node* root, string key) {
        if (root == nullptr) {
            cout << "Keyword not found.\n";
            return root;
        }
        if (key < root->keyword) {
            root->left = remove(root->left, key);
        } else if (key > root->keyword) {
            root->right = remove(root->right, key);
        } else {
            // Keyword found
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            } else {
                Node* temp = findMin(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = remove(root->right, temp->keyword);
            }
        }
        return root;
    }

    Node* search(Node* root, string key, int &comparisons) {
        if (root == nullptr) {
            return nullptr;
        }
        comparisons++;
        if (key == root->keyword) {
            return root;
        } else if (key < root->keyword) {
            return search(root->left, key, comparisons);
        } else {
            return search(root->right, key, comparisons);
        }
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->keyword << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    void reverseInorder(Node* root) {
        if (root != nullptr) {
            reverseInorder(root->right);
            cout << root->keyword << " : " << root->meaning << endl;
            reverseInorder(root->left);
        }
    }

    int findHeight(Node* root) {
        if (root == nullptr)
            return 0;
        int leftHeight = findHeight(root->left);
        int rightHeight = findHeight(root->right);
        return max(leftHeight, rightHeight) + 1;
    }

public:
    Dictionary() {
        root = nullptr;
    }

    void addKeyword(string key, string mean) {
        root = insert(root, key, mean);
    }

    void deleteKeyword(string key) {
        root = remove(root, key);
    }

    void updateMeaning(string key, string newMeaning) {
        int comparisons = 0;
        Node* result = search(root, key, comparisons);
        if (result != nullptr) {
            result->meaning = newMeaning;
            cout << "Meaning updated successfully.\n";
        } else {
            cout << "Keyword not found.\n";
        }
    }

    void searchKeyword(string key) {
        int comparisons = 0;
        Node* result = search(root, key, comparisons);
        if (result != nullptr) {
            cout << "Keyword found: " << result->keyword << " : " << result->meaning << endl;
            cout << "Comparisons made: " << comparisons << endl;
        } else {
            cout << "Keyword not found.\n";
            cout << "Comparisons made: " << comparisons << endl;
        }
    }

    void displayAscending() {
        cout << "Dictionary (Ascending Order):\n";
        inorder(root);
    }

    void displayDescending() {
        cout << "Dictionary (Descending Order):\n";
        reverseInorder(root);
    }

    void maxComparisons() {
        int height = findHeight(root);
        cout << "Maximum comparisons required: " << height << endl;
    }
};

// ---------- MAIN ----------
int main() {
    Dictionary dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n----- Dictionary Menu -----\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Search Keyword\n";
        cout << "5. Display (Ascending Order)\n";
        cout << "6. Display (Descending Order)\n";
        cout << "7. Maximum Comparisons Required\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            cin >> key;
            cout << "Enter meaning: ";
            cin.ignore();
            getline(cin, meaning);
            dict.addKeyword(key, meaning);
            break;

        case 2:
            cout << "Enter keyword to delete: ";
            cin >> key;
            dict.deleteKeyword(key);
            break;

        case 3:
            cout << "Enter keyword to update: ";
            cin >> key;
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, meaning);
            dict.updateMeaning(key, meaning);
            break;

        case 4:
            cout << "Enter keyword to search: ";
            cin >> key;
            dict.searchKeyword(key);
            break;

        case 5:
            dict.displayAscending();
            break;

        case 6:
            dict.displayDescending();
            break;

        case 7:
            dict.maxComparisons();
            break;

        case 8:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 8);

    return 0;
}
