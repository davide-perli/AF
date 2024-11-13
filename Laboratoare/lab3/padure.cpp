#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

// Vectori pentru deplasări în cele patru direcții
int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

struct Node {
    int row, col, diamonds;
    bool operator>(const Node& other) const {
        return diamonds > other.diamonds;
    }
};

int minimumDiamonds(vector<vector<int>>& forest, int N, int M, int startRow, int startCol, int castleRow, int castleCol) {
    vector<vector<int>> cost(N, vector<int>(M, INF));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    cost[startRow][startCol] = 0;
    pq.push({startRow, startCol, 0});

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        int row = node.row, col = node.col, diamonds = node.diamonds;

        if (row == castleRow && col == castleCol) {
            return diamonds;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = row + dRow[i];
            int newCol = col + dCol[i];

            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M) {
                int newDiamonds = diamonds + (forest[row][col] != forest[newRow][newCol]);

                if (newDiamonds < cost[newRow][newCol]) {
                    cost[newRow][newCol] = newDiamonds;
                    pq.push({newRow, newCol, newDiamonds});
                }
            }
        }
    }
    return -1; // în caz că nu se găsește un drum (deși în enunț se specifică că un drum trebuie să existe)
}

int main() {
    ifstream inFile("padure.in");
    ofstream outFile("padure.out");

    int N, M, pl, pc, cl, cc;
    inFile >> N >> M >> pl >> pc >> cl >> cc;
    pl--; pc--; cl--; cc--;  // Ajustare pentru indexare de la 0

    vector<vector<int>> forest(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            inFile >> forest[i][j];
        }
    }

    int result = minimumDiamonds(forest, N, M, pl, pc, cl, cc);
    outFile << result << endl;

    inFile.close();
    outFile.close();

    return 0;
}
