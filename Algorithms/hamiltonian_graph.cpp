#include <bits/stdc++.h>
using namespace std;

void printSolution(int path[], int V);

bool isSafe(int v, vector<vector<int>>& graph, int path[], int pos) 
{ 
    if (graph[path[pos - 1]][v] == 0) 
        return false; 

    for (int i = 0; i < pos; i++) 
        if (path[i] == v) 
            return false; 

    return true; 
} 

bool hamCycleUtil(vector<vector<int>>& graph, int path[], int pos, int V) 
{ 
    if (pos == V) 
    { 
        if (graph[path[pos - 1]][path[0]] == 1) 
            return true; 
        else
            return false; 
    } 

    for (int v = 1; v < V; v++) 
    { 
        if (isSafe(v, graph, path, pos)) 
        { 
            path[pos] = v; 

            if (hamCycleUtil(graph, path, pos + 1, V) == true) 
                return true; 

            path[pos] = -1; 
        } 
    } 

    return false; 
} 

bool hamCycle(vector<vector<int>>& graph, int V) 
{ 
    int *path = new int[V]; 
    for (int i = 0; i < V; i++) 
        path[i] = -1; 

    path[0] = 0; 
    if (hamCycleUtil(graph, path, 1, V) == false ) 
    { 
        cout << "\nSolution does not exist"; 
        return false; 
    } 

    printSolution(path, V); 
    return true; 
} 

void printSolution(int path[], int V) 
{ 
    cout << "Solution Exists: Following is one Hamiltonian Cycle \n"; 
    for (int i = 0; i < V; i++) 
        cout << path[i] << " "; 

    cout << path[0] << " "; // To show the complete cycle
    cout << endl;
} 

int main() 
{ 
    int V, E;
    
    cout << "Enter the number of vertices: ";
    cin >> V;
    
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    
    cout << "Enter edges in the format (u, v):" << endl;
    
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    hamCycle(graph, V); 

    return 0; 
}
