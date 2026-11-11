#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;
const int V = 8;                       // кількість вершин (варіант 22)

// ребро списку суміжності: суміжна вершина та вага
struct Edge { int to, w; };

// друк шляху від s до v за масивом pred (рекурсивно)
void printPath(const vector<int>& pred, int v) {
    if (pred[v] != -1) { printPath(pred, pred[v]); cout << " -> "; }
    cout << v + 1;
}

// Dijkstra(G, s) -> (pred, dist)
void Dijkstra(const vector<vector<Edge>>& G, int s,
              vector<int>& pred, vector<int>& dist) {
    pred.assign(V, -1);                // pred[v] <- -1
    dist.assign(V, INF);               // dist[v] <- inf
    dist[s] = 0;                       // dist[s] <- 0
    vector<bool> done(V, false);
    // черга з пріоритетами: пара (dist, вершина), мінімум зверху
    priority_queue<pair<int,int>, vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;
    pq.push({0, s});
    int step = 0;
    while (!pq.empty()) {              // while SizePQ(pq) != 0
        int u = pq.top().second;       // u <- ExtractMinFromPQ(pq)
        pq.pop();
        if (done[u]) continue;         // застарілий запис у черзі
        done[u] = true;
        cout << "Step " << ++step << ": u = " << u + 1
             << " (dist = " << dist[u] << ")\n";
        for (const Edge& e : G[u]) {   // перебір суміжних вершин
            int v = e.to;
            if (!done[v] && dist[u] + e.w < dist[v]) {   // релаксація
                dist[v] = dist[u] + e.w;
                pred[v] = u;
                pq.push({dist[v], v}); // UpdatePQ(pq, v, dist[v])
                cout << "   relax " << u + 1 << "-" << v + 1
                     << ": dist[" << v + 1 << "] = " << dist[v] << "\n";
            }
        }
    }
}

int main() {
    // список ребер графа варіанта 22: (u, v, вага), вершини 1..8
    int edges[][3] = {
        {1,2,4}, {1,3,1}, {1,4,6}, {2,4,8}, {2,6,3}, {3,8,2},
        {4,5,3}, {5,6,9}, {5,7,5}, {6,7,7}, {6,8,1}, {7,8,7}
    };
    vector<vector<Edge>> G(V);         // списки суміжності
    for (auto& e : edges) {
        G[e[0]-1].push_back({e[1]-1, e[2]});
        G[e[1]-1].push_back({e[0]-1, e[2]});   // граф неорієнтований
    }
    int s = 0;                         // стартова вершина 1
    vector<int> pred, dist;
    Dijkstra(G, s, pred, dist);

    cout << "\nVertex | dist | pred | path\n";
    for (int v = 0; v < V; v++) {
        if (v == s) continue;
        cout << "   " << v + 1 << "   |  " << dist[v] << (dist[v] < 10 ? " " : "")
             << "  |  " << pred[v] + 1 << "   | ";
        printPath(pred, v);
        cout << "\n";
    }
    return 0;
}
