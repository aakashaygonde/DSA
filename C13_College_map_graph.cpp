/*
 C13 : 
         "Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS.
         Use the map of the area around the college as the graph. Identify the prominent land marks as nodes and
        perform DFS and BFS on that."
*/
#include <iostream>
using namespace std;

const int MAX = 10;

// DFS using Adjacency Matrix
class GraphMatrix {
    int adj[MAX][MAX];
    bool visited[MAX];
    int n;

public:
    GraphMatrix(int nodes) {
        n = nodes;
        for (int i = 0; i < n; i++) {
            visited[i] = false;
            for (int j = 0; j < n; j++)
                adj[i][j] = 0;
        }
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; // since it's undirected
    }

    void DFS(int v) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i])
                DFS(i);
        }
    }

    void startDFS(int start) {
        for (int i = 0; i < n; i++)
            visited[i] = false;
        cout << "DFS Traversal: ";
        DFS(start);
        cout << endl;
    }
};

// BFS using Adjacency List
class GraphList {
    struct Node {
        int vertex;
        Node* next;
    };

    Node* adjList[MAX];
    int n;

public:
    GraphList(int nodes) {
        n = nodes;
        for (int i = 0; i < n; i++)
            adjList[i] = nullptr;
    }

    void addEdge(int u, int v) {
        Node* newNode = new Node{v, adjList[u]};
        adjList[u] = newNode;

        newNode = new Node{u, adjList[v]};
        adjList[v] = newNode;
    }

    void BFS(int start) {
        bool visited[MAX] = {false};
        int queue[MAX], front = 0, rear = 0;

        visited[start] = true;
        queue[rear++] = start;

        cout << "BFS Traversal: ";

        while (front < rear) {
            int curr = queue[front++];
            cout << curr << " ";

            Node* temp = adjList[curr];
            while (temp != nullptr) {
                if (!visited[temp->vertex]) {
                    visited[temp->vertex] = true;
                    queue[rear++] = temp->vertex;
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }
};

// --- Main Program ---
int main() {
    int nodes = 6;

    // Map node index to landmark
    string landmarks[] = {
        "College", "Library", "Canteen", "Hostel", "Bus Stop", "Playground"
    };

    // Sample edges
    int edges[][2] = {
        {0, 1}, {0, 2}, {0, 3}, {1, 4}, {2, 4}, {3, 5}, {4, 5}
    };

    GraphMatrix gMatrix(nodes);
    GraphList gList(nodes);

    // Add edges to both graphs
    for (int i = 0; i < 7; i++) {
        gMatrix.addEdge(edges[i][0], edges[i][1]);
        gList.addEdge(edges[i][0], edges[i][1]);
    }

    cout << "--- Landmarks ---\n";
    for (int i = 0; i < nodes; i++) {
        cout << i << ": " << landmarks[i] << endl;
    }

    int start;
    cout << "\nEnter starting node index (0-" << nodes-1 << ") for traversal: ";
    cin >> start;

    gMatrix.startDFS(start);
    gList.BFS(start);

    return 0;
}
