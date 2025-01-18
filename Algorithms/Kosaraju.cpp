#include <iostream>
#include <list>
using namespace std;

class Graph {
    int V;
    list<int>* adj;

    void DFSUtil(int v, bool visited[]);

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int v, int w);
    bool isSC();
    Graph getTranspose();
};

void Graph::DFSUtil(int v, bool visited[]) {
    visited[v] = true;
    for (int i : adj[v])
        if (!visited[i])
            DFSUtil(i, visited);
}

Graph Graph::getTranspose() {
    Graph g(V);
    for (int v = 0; v < V; v++) {
        for (int i : adj[v]) {
            g.adj[i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

bool Graph::isSC() {
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSUtil(0, visited);

    for (int i = 0; i < V; i++)
        if (!visited[i])
            return false;

    Graph gr = getTranspose();

    for (int i = 0; i < V; i++)
        visited[i] = false;

    gr.DFSUtil(0, visited);

    for (int i = 0; i < V; i++)
        if (!visited[i])
            return false;

    return true;
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
        g.addEdge(u, v);
    }

    g.isSC() ? cout << "Yes\n" : cout << "No\n";

    return 0;
}
