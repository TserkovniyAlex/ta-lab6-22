#include <iostream>
#include <iomanip>
using namespace std;

const int INF = 1000000;               // "нескінченність"
const int n = 8;                       // кількість вершин (варіант 22)

void printMatrix(int D[n][n], int k) {
    cout << "D(" << k << "):\n     ";
    for (int j = 0; j < n; j++) cout << setw(4) << j + 1;
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << i + 1 << " ";
        for (int j = 0; j < n; j++)
            if (D[i][j] >= INF) cout << setw(4) << "inf";
            else cout << setw(4) << D[i][j];
        cout << "\n";
    }
}

// Floyd(W[1..n, 1..n]) -> D
void Floyd(int W[n][n], int D[n][n]) {
    for (int i = 0; i < n; i++)        // D <- W
        for (int j = 0; j < n; j++)
            D[i][j] = W[i][j];
    printMatrix(D, 0);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (D[i][k] + D[k][j] < D[i][j])   // min{D[i,j], D[i,k]+D[k,j]}
                    D[i][j] = D[i][k] + D[k][j];
        printMatrix(D, k + 1);
    }
}

int main() {
    const int I = INF;
    // вагова матриця W графа варіанта 22 (0 на діагоналі, inf - немає ребра)
    int W[n][n] = {
    //    1  2  3  4  5  6  7  8
        { 0, 4, 1, 6, I, I, I, I },   // 1
        { 4, 0, I, 8, I, 3, I, I },   // 2
        { 1, I, 0, I, I, I, I, 2 },   // 3
        { 6, 8, I, 0, 3, I, I, I },   // 4
        { I, I, I, 3, 0, 9, 5, I },   // 5
        { I, 3, I, I, 9, 0, 7, 1 },   // 6
        { I, I, I, I, 5, 7, 0, 7 },   // 7
        { I, I, 2, I, I, 1, 7, 0 }    // 8
    };
    int D[n][n];
    Floyd(W, D);
    return 0;
}
