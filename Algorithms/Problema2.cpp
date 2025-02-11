#include <bits/stdc++.h>
using namespace std;

// Define INF as a large value to represent infinity
#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph {
    int V;
    list<iPair> *adj;

public:
    explicit Graph(int V);

    void addEdge(int u, int v, int w) const;
    void shortestPath(int s, int &x) const;
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w) const {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
}

void Graph::shortestPath(int s, int &x) const {

    priority_queue<iPair, vector<iPair>, greater<>> pq;

    vector<int> dist(V, INF);

    pq.emplace(0, s );
    dist[s] = 0;

    while (!pq.empty()) {

        int u = pq.top().second;
        pq.pop();

        for (auto &neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[v] > dist[u] + weight) {

                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }


    //cout << "Vertex Distance from Source" << endl;
    //for (int i = 1; i <= V; ++i)
    //    cout << i << " \t\t " << dist[i] << endl;
    x = dist[V-1];
}


int main() {
    int V, x, y[10], rez[10], k = 0;
    //cout << "Number of vertices: ";
    cin >> V;
    Graph g(V);

    int E, u, v;
    //cout << "Enter number of edges: ";
    cin >> E;


    //cout << "Enter the edges (format: u v weight):" << endl;

    for(int i = 0; i < E; i++)
    {
        cin >> u >> v;
        g.addEdge(u-1, v-1, 1);
    }

    //cout << "Enter the node from which to find the shortest path: ";
    //cin >> s;

    //cout << "Shortest path from node " << s << " is ";
    g.shortestPath(0,x);

    y[0] = x;

    int q;

    cin >> q;


    for (int i = 1; i <= q; i++)
    {
        cin >> u >> v;
        g.addEdge(u-1, v-1, 1);
        g.shortestPath(0, x);
        y[i + 1] = x;
        if (y[i] > y[0])
        {
            rez[i] = i;
            k++;
        }
    }

    cout << q << endl;;

    for (int i = 1; i <= k; i++ )
        cout << rez[i] << " ";

    // afisez daca noul graf are drum mai scurt sau nu, cu Dijsktra unde muchiile au valoare 1, afisez indicii muchiilor
    return 0;
}
