#include <iostream>
#include <vector>
using namespace std;

void printSolution(int color[], int V);

bool isSafe(int v, bool graph[][4], int color[], int c, int V) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

bool graphColoringUtil(bool graph[][4], int m, int color[], int v, int V) {
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1, V))
                return true;
            color[v] = 0;
        }
    }
    return false;
}

bool graphColoring(bool graph[][4], int m, int V) {
    int color[4];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (graphColoringUtil(graph, m, color, 0, V) == false) {
        cout << "Solution does not exist";
        return false;
    }

    printSolution(color, V);
    return true;
}

void printSolution(int color[], int V) {
    cout << "Solution Exists: Following are the assigned colors\n";
    for (int i = 0; i < V; i++)
        cout << " " << color[i] << " ";
    cout << "\n";
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    bool graph[4][4] = {false}; // Assuming maximum vertices as 4

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges in the format (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = true;
        graph[v][u] = true; // Undirected graph
    }

    int m;
    cout << "Enter the number of colors: ";
    cin >> m;

    graphColoring(graph, m, V);
    
    return 0;
}
