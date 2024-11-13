#include <bits/stdc++.h>
using namespace std;

// Functie pentru a adauga o muchie in lista de adiacenta
void addEdge(vector<vector<int>> &adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// DFS pentru identificarea muchiilor critice
void DFSBridge(int u, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<pair<int, int>> &bridges, int &time) {
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            DFSBridge(v, adj, visited, disc, low, parent, bridges, time);

            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u]) {
                bridges.push_back({u, v}); // Muchia (u, v) este critica
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

// Functie pentru a gasi toate muchiile critice din graf
vector<pair<int, int>> findBridges(vector<vector<int>> &adj, int n) {
    vector<bool> visited(n, false);
    vector<int> disc(n, -1), low(n, -1), parent(n, -1);
    vector<pair<int, int>> bridges;
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFSBridge(i, adj, visited, disc, low, parent, bridges, time);
        }
    }

    return bridges;
}

int main() {
    ifstream inFile("input.in");
    ofstream outFile("output.out");

    int N, M; // N = nr de noduri, M = nr de muchii
    inFile >> N >> M;

    vector<vector<int>> adj(N);  // Lista de adiacenta pentru graf

    // Citire muchii din fisierul de intrare
    for (int i = 0; i < M; i++) {
        int X, Y;
        inFile >> X >> Y;
        addEdge(adj, X - 1, Y - 1);  // Ajustare pentru indexare de la 0
    }

    // Gasesc si afisez muchiile critice
    vector<pair<int, int>> bridges = findBridges(adj, N);

    if (bridges.empty()) {
        outFile << "Nu exista muchii critice." << endl;
    } else {
        outFile << "Muchiile critice sunt:" << endl;
        for (auto &bridge : bridges) {
            outFile << bridge.first + 1 << " " << bridge.second + 1 << endl;  // Ajustare pentru indexare de la 1
        }
    }

    inFile.close();
    outFile.close();

    return 0;
}
