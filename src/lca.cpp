#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 100
#define MAX_LOG_V 14

int vn, en;
vector<int> g[MAX_N];
int depth[MAX_N];
int parent[MAX_LOG_V][MAX_N];
bool marked[MAX_N];
int root = 0;
int u, v;

void input() {
    cin >> vn >> en;
    for (int i = 0; i < en; i++) {
        int v, w;
        cin >> v >> w;
        g[v].push_back(w);
        g[w].push_back(v);
    }
    cin >> u >> v;
}

void output(int lca_vertex){
    cout << lca_vertex << endl;
}

void dfs(int v, int p, int d){
    marked[v] = true;
    parent[0][v] = p;
    depth[v] = d;
    for (auto w : g[v]) 
        if (!marked[w]) dfs(w, v, d + 1);
}

void pre_process(){
    dfs(root, -1, 0);
    for (int k = 0; k < MAX_LOG_V; k++){
        for (int v = 0; v < vn; v++){
            if (parent[k][v] < 0) parent[k + 1][v] = -1; 
            else parent[k + 1][v] = parent[k][parent[k][v]];
        } 
    }
}

int lca(int u, int v){
    if (depth[u] > depth[v]) swap(u, v); //depth[v] >= depth[u]
    for (int k = 0; k < MAX_LOG_V; k++){
        if ((depth[v] - depth[u]) >> k & 1) 
            v = parent[k][v];
    }
    if (u == v) return v;
    for (int k = MAX_LOG_V; k >= 0; k--){
        if (parent[k][u] != parent[k][v]){
            u = parent[k][u];
            v = parent[k][v];
        } 
    }    
    return parent[0][u];
}

int main() {
    freopen("./testcase/lca_input.txt", "r", stdin);
    input();
    pre_process();
    int ret = lca(u, v);
    output(ret); 
}
