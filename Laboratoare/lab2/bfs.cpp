#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

void bfs(const vector<vector<int>>& adj, int s, vector<int>& distances) 
{
    queue<int> q;
    distances[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int neighbor : adj[curr]) {
            if (distances[neighbor] == -1) {  // Adica nevizitat
                distances[neighbor] = distances[curr] + 1;
                q.push(neighbor);
            }
        }
    }
}

// Adaug mucchie direct la graf
void addEdge(vector<vector<int>>& adj, int u, int v) 
{
    adj[u].push_back(v);
}

int main() 
{
    ifstream infile("bfs.in");
    if (!infile) {
        cerr << "Error opening file bfs.in\n";
        return 1;
    }

    ofstream outfile("bfs.out");
    if (!outfile) {
        cerr << "Error opening file bfs.out\n";
        return 1;
    }

    int N, M, S;
    infile >> N >> M >> S;

    vector<vector<int>> adj(N + 1); // Noduri indexate de la 1

    // Citesc muchiile din fisier
    for (int i = 0; i < M; ++i) {
        int u, v;
        infile >> u >> v;
        addEdge(adj, u, v);
    }
    infile.close();

    // Initializez distanta cu -1 pentru nodurile izolate
    vector<int> distances(N + 1, -1);

    // Apelez functia pentru bfs
    bfs(adj, S, distances);

    // Afisez in bfs.out
    for (int i = 1; i <= N; ++i) {
        outfile << distances[i] << " ";
    }
    outfile.close();

    return 0;
}
