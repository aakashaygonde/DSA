/*
C15 : 
        "You have a business with several offices; you want to lease phone lines to connect them up with each other; 
        and the phone company charges different amounts of money to connect different pairs of cities. 
        You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by
        suggesting appropriate data structures."
*/
#include <iostream>
using namespace std;

const int MAX = 100;

struct Edge {
    int u, v, weight;
};

class UnionFind {
    int parent[MAX];

public:
    void makeSet(int n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        parent[px] = py;
    }
};

void sortEdges(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int main() {
    int V, E;
    Edge edges[MAX];

    cout << "Enter number of offices (vertices): ";
    cin >> V;
    cout << "Enter number of possible connections (edges): ";
    cin >> E;

    for (int i = 0; i < E; i++) {
        cout << "Enter edge " << i + 1 << " (from to cost): ";
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // Sort edges by weight
    sortEdges(edges, E);

    UnionFind uf;
    uf.makeSet(V);

    int mstCost = 0;
    cout << "\nMinimum Spanning Tree edges:\n";

    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            cout << u << " - " << v << " : " << edges[i].weight << "\n";
            mstCost += edges[i].weight;
        }
    }

    cout << "\nTotal minimum cost: " << mstCost << endl;
    return 0;
}
