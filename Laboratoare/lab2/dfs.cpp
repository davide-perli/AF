#include <bits/stdc++.h>
using namespace std;

// Traversare dfs recursiva
void DFSRec(vector<vector<int>> &adj, vector<bool> &visited, int s) {
    visited[s] = true;
    for (int i : adj[s]) {
        if (!visited[i]) {
            DFSRec(adj, visited, i);
        }
    }
}

// Adaug o muchie
void addEdge(vector<vector<int>> &adj, int s, int t) {
    adj[s].push_back(t); 
    adj[t].push_back(s); 
}

// Functie care numara componentele conexe
int countConnectedComponents(vector<vector<int>> &adj, int n) {
    vector<bool> visited(n, false);
    int componentCount = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {  // Incep un nou DFS pentru fiecare nod nevizitat
            DFSRec(adj, visited, i);
            componentCount++;  // Se incrementeaza contorul pentru fiecare componenta conexa gasita
        }
    }
    return componentCount;
}

int main() {
    ifstream inFile("dfs.in");
    ofstream outFile("dfs.out");

    int N, M; // N = nr noduri, M = nr muchii
    inFile >> N >> M;

    vector<vector<int>> adj(N);  // Adjacency list for graph

    // Citesc muchiile din fisierul de intrare
    for (int i = 0; i < M; i++) {
        int X, Y;
        inFile >> X >> Y;
        addEdge(adj, X - 1, Y - 1);  // Reglare pentru indexare de la 0
    }

    int componentCount = countConnectedComponents(adj, N);

    // Afisez numarul de componente conexe in fisierul dfs.out
    outFile << componentCount << endl;

    inFile.close();
    outFile.close();

    return 0;
}
