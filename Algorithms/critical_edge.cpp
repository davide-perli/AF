#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
    int V;
    list<int>* adj;

    void DFS(int u, bool visited[], int disc[], int low[], int parent[], vector<pair<int, int>>& bridges);

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int v, int w);
    void findBridges();
};

void Graph::addEdge(int v, int w) {
    adj[v - 1].push_back(w - 1);
    adj[w - 1].push_back(v - 1);
}

void Graph::DFS(int u, bool visited[], int disc[], int low[], int parent[], vector<pair<int, int>>& bridges) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            DFS(v, visited, disc, low, parent, bridges);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u]) {
                bridges.push_back({u + 1, v + 1});
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void Graph::findBridges() {
    bool* visited = new bool[V];
    int* disc = new int[V];
    int* low = new int[V];
    int* parent = new int[V];
    vector<pair<int, int>> bridges;

    for (int i = 0; i < V; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i, visited, disc, low, parent, bridges);
        }
    }

    for (auto bridge : bridges) {
        cout << "Critical edge: " << bridge.first << " - " << bridge.second << endl;
    }

    delete[] visited;
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

    g.findBridges();

    return 0;
}
