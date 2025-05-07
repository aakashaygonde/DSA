/*
 D18 : 
        "Given sequence k = k1 <k2 < … <kn of n sorted keys, with a search probability pi for each key ki . Build the Binary search tree that has the least search cost given the access probability for each key?"
*/
#include <iostream>
using namespace std;

const int MAX = 100;
float p[MAX]; // probabilities
string keys[MAX];
float cost[MAX][MAX]; // DP table
float sum[MAX][MAX];
int root[MAX][MAX]; // To store roots for optimal subtrees

void buildTree(int i, int j, string indent = "") {
    if (i > j) return;
    int r = root[i][j];
    cout << indent << keys[r] << endl;
    buildTree(i, r - 1, indent + "  L-");
    buildTree(r + 1, j, indent + "  R-");
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter " << n << " sorted keys and their search probabilities:\n";
    for (int i = 1; i <= n; i++) {
        cin >> keys[i] >> p[i];
    }

    // Initialize cost and sum arrays
    for (int i = 1; i <= n; i++) {
        cost[i][i - 1] = 0;
        cost[i][i] = p[i];
        sum[i][i] = p[i];
        root[i][i] = i;
    }
    cost[n + 1][n] = 0;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = 999999;
            sum[i][j] = sum[i][j - 1] + p[j];

            for (int r = i; r <= j; r++) {
                float c = cost[i][r - 1] + cost[r + 1][j];
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
            cost[i][j] += sum[i][j];
        }
    }

    cout << "\nMinimum Expected Search Cost: " << cost[1][n] << endl;
    cout << "\nOptimal Binary Search Tree Structure:\n";
    buildTree(1, n);

    return 0;
}
