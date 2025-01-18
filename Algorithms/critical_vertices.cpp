#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
    int V;
    list<int>* adj;

    void DFS(int u, vector<bool>& visited, int disc[], int low[], int parent[], vector<bool>& ap);

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int v, int w);
    void findArticulationPoints();
};

void Graph::addEdge(int v, int w) {
    adj[v - 1].push_back(w - 1);
    adj[w - 1].push_back(v - 1);
}

void Graph::DFS(int u, vector<bool>& visited, int disc[], int low[], int parent[], vector<bool>& ap) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            children++;
            DFS(v, visited, disc, low, parent, ap);
            low[u] = min(low[u], low[v]);
            if (parent[u] == -1 && children > 1) {
                ap[u] = true;
            }
            if (parent[u] != -1 && low[v] >= disc[u]) {
                ap[u] = true;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void Graph::findArticulationPoints() {
    vector<bool> visited(V, false);
    int* disc = new int[V];
    int* low = new int[V];
    int* parent = new int[V];
    vector<bool> ap(V, false);

    for (int i = 0; i < V; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i, visited, disc, low, parent, ap);
        }
    }

    for (int i = 0; i < V; i++) {
        if (ap[i]) {
            cout << "Critical vertex: " << i + 1 << endl;
        }
    }

    delete[] disc;
    delete[] low;
    delete[] parent;
}

int main() {
    int V, E;

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter the edges (format: u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        if (u >= 1 && u <= V && v >= 1 && v <= V) {
            g.addEdge(u, v);
        } else {
            cout << "Invalid edge: " << u << " - " << v << ". Please enter vertices between 1 and " << V << "." << endl;
            i--;
        }
    }

    g.findArticulationPoints();

    return 0;
}
