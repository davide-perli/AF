#include <bits/stdc++.h>
using namespace std;

// Define INF as a large value to represent infinity
#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph {
    int V; 
    list<iPair> *adj; 

public:
    Graph(int V); 

    void addEdge(int u, int v, int w);
    void shortestPath(int s);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w)); 
}

void Graph::shortestPath(int src) {
   
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {

        int u = pq.top().second;
        pq.pop();

        for (auto &neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[v] > dist[u] + weight) {

                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }


    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < V; ++i)
        cout << i << " \t\t " << dist[i] << endl;
}


int main() {
    int V;
    cout << "Number of vertices: ";
    cin >> V;
    Graph g(V);

    int E, u, v, w;
    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter the edges (format: u v weight):" << endl;
    
    for(int i = 0; i < E; i++)
    {
     cin >> u >> v >> w;
     g.addEdge(u, v, w);
    }

    int s;
    cout << "Enter the node from which to find the shortest path: ";
    cin >> s; 

    cout << "Shortest path from node " << s << " is ";
    g.shortestPath(s);

    return 0;
}
