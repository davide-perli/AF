#include <bits/stdc++.h>
using namespace std;

// Functie pentru a adăuga o muchie
void addEdge(vector<vector<int>> &adj, int s, int t) {
    adj[s].push_back(t); 
    adj[t].push_back(s); 
}

// Functie care verifică dacă graful este bipartit
bool isBipartite(vector<vector<int>> &adj, int n) {
    vector<int> color(n, -1);  // Vector pentru colorarea nodurilor (-1: necolorat)

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {  // Dacă nodul nu a fost colorat, încep BFS de la acest nod
            queue<int> q;
            q.push(i);
            color[i] = 0;  // Pornesc colorarea cu culoarea 0

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];  // Colorez nodul adiacent cu culoarea opusă
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;  // Noduri adiacente au aceeași culoare, deci graful nu este bipartit
                    }
                }
            }
        }
    }
    return true;  // Graful este bipartit dacă toate perechile adiacente sunt colorate diferit
}

int main() {
    ifstream inFile("dfs.in");
    ofstream outFile("dfs.out");

    int N, M; // N = nr noduri, M = nr muchii
    inFile >> N >> M;

    vector<vector<int>> adj(N);  // Lista de adiacență pentru graf

    // Citire muchii din fisierul de intrare
    for (int i = 0; i < M; i++) {
        int X, Y;
        inFile >> X >> Y;
        addEdge(adj, X - 1, Y - 1);  // Ajustare pentru indexare de la 0
    }

    // Verific bipartitatea
    bool bipartite = isBipartite(adj, N);

    // Scriu rezultatul în fisierul de ieșire
    outFile << (bipartite ? "YES" : "NO") << endl;

    inFile.close();
    outFile.close();

    return 0;
}
