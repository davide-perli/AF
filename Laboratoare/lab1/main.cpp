#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void matrice_adiacenta(ifstream& f)
{
    int n;
    f >> n;

    int m;
    f >> m;

    int orientat;

    f>> orientat;

    int x, y;
    int mat[n+1][n+1] = {0};
    for (int i = 0; i < m; i++) {
        f >> x >> y;
        if(orientat == 0) //graful este neorientat, 0 este valoare de fals
        {
            mat[x][y] = 1;
            mat[y][x] = 1;
        }
        else {
            mat[x][y] = 1;
        }

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

}

void lista_adiacenta(ifstream& f)
{
    int n;
    f >> n;

    int m;
    f >> m;

    int orientat;

    f>> orientat;

    vector<vector<int>> lista(n);

    int x, y;
    for (int i = 0; i < m; i++) {
        f >> x >> y;
        lista[x - 1].push_back(y - 1); //ajustare indexare
        if (orientat == 0) { // graf neorientat, 0 este valoare de fals
            lista[y - 1].push_back(x - 1);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Nodul " << (i + 1) << ": ";
        for (int j : lista[i]) {
            cout << (j + 1) << " ";
        }
        cout << endl;
    }
}

int main() {
    ifstream f("input.in");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return {};
    }

    matrice_adiacenta(f);
    f.close();

    cout << endl;
    cout << endl;
    cout << endl;

    ifstream g("input.in");

    if (!g.is_open()) {
        cerr << "Error opening the file!";
        return {};
    }

    lista_adiacenta(g);
    g.close();

}