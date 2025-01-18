#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;

class Graph {
public:
    vector<vector<int>> adj_matrix;
    vector<string> vertex_data;
    int size;

    Graph(int size) {
        this->size = size;
        adj_matrix.resize(size, vector<int>(size, 0));
        vertex_data.resize(size);
    }

    void add_edge(int u, int v, int c) {
        adj_matrix[u][v] = c;
    }

    void add_vertex_data(int vertex, const string& data) {
        if (0 <= vertex && vertex < size) {
            vertex_data[vertex] = data;
        }
    }

    bool bfs(int s, int t, vector<int>& parent) {
        vector<bool> visited(size, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int ind = 0; ind < size; ind++) {
                if (!visited[ind] && adj_matrix[u][ind] > 0) {
                    q.push(ind);
                    visited[ind] = true;
                    parent[ind] = u;
                }
            }
        }
        return visited[t];
    }

    int edmonds_karp(int source, int sink) {
        vector<int> parent(size);
        int max_flow = 0;

        while (bfs(source, sink, parent)) {
            int path_flow = numeric_limits<int>::max();
            int s = sink;
            while (s != source) {
                path_flow = min(path_flow, adj_matrix[parent[s]][s]);
                s = parent[s];
            }

            max_flow += path_flow;
            int v = sink;
            while (v != source) {
                int u = parent[v];
                adj_matrix[u][v] -= path_flow;
                adj_matrix[v][u] += path_flow;
                v = parent[v];
            }

            vector<int> path;
            v = sink;
            while (v != source) {
                path.push_back(v);
                v = parent[v];
            }
            path.push_back(source);
            reverse(path.begin(), path.end());
            vector<string> path_names;
            for (int node : path) {
                path_names.push_back(vertex_data[node]);
            }
            cout << "Path: " << join(path_names, " -> ") << ", Flow: " << path_flow << endl;
        }

        return max_flow;
    }

private:
    string join(const vector<string>& vec, const string& delimiter) {
        string result;
        for (size_t i = 0; i < vec.size(); ++i) {
            result += vec[i];
            if (i < vec.size() - 1) result += delimiter;
        }
        return result;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph g(V);
    cout << "Enter vertex names:\n";
    for (int i = 0; i < V; i++) {
        string name;
        cin >> name;
        g.add_vertex_data(i, name);
    }

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges in the format (u v capacity):\n";
    for (int i = 0; i < E; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        g.add_edge(u, v, c);
    }

    int source, sink;
    cout << "Enter the source and sink vertices: ";
    cin >> source >> sink;

    cout << "The maximum possible flow is " << g.edmonds_karp(source, sink) << endl;

    return 0;
}
