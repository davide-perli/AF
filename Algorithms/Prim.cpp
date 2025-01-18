#include <bits/stdc++.h>
using namespace std;

int spanningTree(int V, int E, vector<vector<int>> &edges) {
    vector<vector<int>> adj[V];
    for (int i = 0; i < E; i++) {
        int u = edges[i][0] - 1; // Adjust for 1-based index
        int v = edges[i][1] - 1; // Adjust for 1-based index
        int wt = edges[i][2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<bool> visited(V, false);
    int res = 0;
    pq.push({0, 0}); // Start from vertex 0
    
    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();
        
        int wt = p.first;
        int u = p.second;
        
        if(visited[u]) {
            continue;
        }
        
        res += wt;
        visited[u] = true;

        for(auto v : adj[u]){
            if(!visited[v[0]]){
                pq.push({v[1], v[0]});
            }
        }
    }
    
    return res;
}

int main() {
    int V, E;
    cout << "Number of vertices: ";
    cin >> V;
    cout << "Number of edges: ";
    cin >> E;
    vector<vector<int>> graph(E, vector<int>(3));

    cout << "Enter the edges (format: u v weight):" << endl;
    
    for (int i = 0; i < E; i++) {
        cin >> graph[i][0] >> graph[i][1] >> graph[i][2];
    }

    cout << "Minimum weight of MST: " << spanningTree(V, E, graph) << endl;

    return 0;
}
