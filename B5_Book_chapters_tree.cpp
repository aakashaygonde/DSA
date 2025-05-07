/*
 B5 : 
        " A book consists of chapters, chapters consist of sections and sections consist of subsections. Construct a tree and print the nodes. Find the time and space requirements of your method"
*/
#include <iostream>
using namespace std;

const int MAX = 10;

class TreeNode {
public:
    string name;
    int childCount;
    TreeNode* children[MAX];

    TreeNode(string name) {
        this->name = name;
        childCount = 0;
    }

    void addChild(TreeNode* child) {
        if (childCount < MAX)
            children[childCount++] = child;
        else
            cout << "Max children reached for " << name << endl;
    }
};

void printTree(TreeNode* node, int level = 0) {
    for (int i = 0; i < level; ++i) cout << "  ";
    cout << node->name << endl;

    for (int i = 0; i < node->childCount; ++i)
        printTree(node->children[i], level + 1);
}

int main() {
    TreeNode* root = new TreeNode("Book");

    int chCount, secCount, subsecCount;
    string name;

    cout << "Enter number of chapters: ";
    cin >> chCount;

    for (int i = 0; i < chCount; i++) {
        cout << "Enter name of Chapter " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, name);
        TreeNode* chapter = new TreeNode(name);

        cout << "  Enter number of sections in " << name << ": ";
        cin >> secCount;

        for (int j = 0; j < secCount; j++) {
            cout << "  Enter name of Section " << (j + 1) << ": ";
            cin.ignore();
            getline(cin, name);
            TreeNode* section = new TreeNode(name);

            cout << "    Enter number of subsections in " << name << ": ";
            cin >> subsecCount;

            for (int k = 0; k < subsecCount; k++) {
                cout << "    Enter name of Subsection " << (k + 1) << ": ";
                cin.ignore();
                getline(cin, name);
                TreeNode* subsection = new TreeNode(name);
                section->addChild(subsection);
            }

            chapter->addChild(section);
        }

        root->addChild(chapter);
    }

    cout << "\n----- Book Tree Structure -----\n";
    printTree(root);

    return 0;
}


/*
Time Complexity (Input + Print):
𝑂(𝑁) where 𝑁 is the total number of nodes (chapters + sections + subsections)

Space Complexity:
O(N) for storing the tree in memory

*/