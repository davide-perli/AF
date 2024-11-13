#include <bits/stdc++.h>
using namespace std;

// Funcția pentru a adăuga o muchie în graf
void addEdge(vector<vector<int>> &adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Funcția pentru a calcula distanțele minime față de punctele de control
vector<int> minDistanceToControlPoints(vector<vector<int>> &adj, int n, vector<int> &controlPoints) {
    vector<int> distances(n, INT_MAX);
    queue<int> q;

    // Adăugăm punctele de control în coadă și setăm distanțele lor la 0
    for (int control : controlPoints) {
        q.push(control);
        distances[control] = 0;
    }

    // BFS pentru calculul distanțelor minime
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (distances[neighbor] > distances[node] + 1) {
                distances[neighbor] = distances[node] + 1;
                q.push(neighbor);
            }
        }
    }

    return distances;
}

int main() {
    ifstream inFile("graf.in");
    ofstream outFile("graf.out");

    int n, m;  // n = număr de noduri, m = număr de muchii
    inFile >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        inFile >> u >> v;
        addEdge(adj, u - 1, v - 1);  // Ajustare pentru indexare de la 0
    }

    // Citim punctele de control de pe ultima linie
    vector<int> controlPoints;
    int controlPoint;
    while (inFile >> controlPoint) {
        controlPoints.push_back(controlPoint - 1);  // Ajustare pentru indexare de la 0
    }

    // Calculăm distanțele minime pentru fiecare nod față de punctele de control
    vector<int> distances = minDistanceToControlPoints(adj, n, controlPoints);

    // Scriem rezultatul în fișierul de ieșire
    for (int i = 0; i < n; i++) {
        outFile << distances[i] << " ";
    }
    outFile << endl;

    inFile.close();
    outFile.close();

    return 0;
}
