#include <iostream>
#include <vector>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8);
    dist[src] = 0;

    for (int i = 0; i < V; i++) {
        for (vector<int> edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                if(i == V - 1)
                    return {-1};
                dist[v] = dist[u] + wt;
            }
        }
    }

    return dist;
}

int main() {
    int V, E;
    
    cout << "Enter the number of vertices: ";
    cin >> V;
    
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> edges(E, vector<int>(3));
    
    cout << "Enter the edges in the format (u v weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    vector<int> ans = bellmanFord(V, edges, src);
    
    if (ans[0] == -1) {
        cout << "Negative cycle detected." << endl;
    } else {
        cout << "Shortest distances from source vertex " << src << ":\n";
        for (int dist : ans) 
            cout << dist << " ";
        cout << endl;
    }

    return 0;
}
