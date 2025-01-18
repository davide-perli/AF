#include <bits/stdc++.h>
using namespace std;

void topologicalSortUtil(int v, vector<vector<int>>& adj,
                         vector<bool>& visited,
                         stack<int>& Stack)
{
    visited[v] = true; 

    for (int i : adj[v]) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, Stack);
    }

    Stack.push(v); 
}

void topologicalSort(vector<vector<int>>& adj, int V)
{
    stack<int> Stack;
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, Stack);
    }

    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

int main()
{
    int V; 
    cout << "Enter the number of vertices: ";
    cin >> V;

    int E; 
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> edges(E);
    
    cout << "Enter the edges (format: u v for an edge from u to v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v}; 
    }

    vector<vector<int>> adj(V);

    for (auto i : edges) {
        adj[i[0]].push_back(i[1]);
    }

    cout << "Topological sorting of the graph: ";
    topologicalSort(adj, V);

    return 0;
}
