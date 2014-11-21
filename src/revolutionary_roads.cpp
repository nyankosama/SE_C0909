/*=============================================================================
#
# Author: Nyankosama email:i@nyankosama.com
#
# Last modified: 2014-11-18 07:47
#
# Filename: ReverlutionRoad.cpp
#
# Description: acm problems: http://acm.sgu.ru/problem.php?contest=0&problem=525
=============================================================================*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_N 100

struct edge {
    edge(int from, int to, int id):from(from), to(to), id(id) {}
    int from;
    int to;
    int id;
};

bool to[MAX_N][MAX_N], from[MAX_N][MAX_N];
int vn;
int en;
vector<int> g[MAX_N];
vector<edge> edges;

void input() {
    cin >> vn >> en;
    for (int i = 0; i < en; i++) {
        int v = 0;
        int w = 0;
        cin >> v >> w;
        g[v].push_back(w);
        edge e(v, w, i + 1);
        edges.push_back(e);
    }
}

void dfs(int o, int v, bool marked[]) {
    marked[v] = true;
    to[o][v] = true;
    from[v][o] = true;
    for(int w : g[v]) {
        if (!marked[w]) dfs(o, w, marked);
    }
}

void calcTransitiveMatrix() {
    for (int i = 0; i < vn; i++) {
        bool marked[MAX_N];
        memset(marked, 0, MAX_N);
        dfs(i, i, marked);
    }
}

void merge(bool* ret, bool* arr1, bool* arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] == true || arr2[i] == true)
            ret[i] = true;
    }
}


void output(int maxW, const vector<edge>& result){
    cout << maxW << endl;
    cout << result.size() << endl;
    for (auto e : result){
        cout << e.id << " "; 
    }
    cout << endl;
}

void solve() {
    int maxW = 0;
    vector<edge> result;
    for (auto e : edges) {
        bool ret[MAX_N]; 
        memset(ret, 0, MAX_N);
        bool* from_to = to[e.from];
        bool* from_from = from[e.from];
        bool* to_from = from[e.to];
        //合并from_from和to_from
        merge(ret, from_from, to_from, vn);
        int sum = 0;
        for (int i = 0; i < vn; i++) {
            if (from_to[i] == true && ret[i] == true) sum++;
        }
        if (sum > maxW) {
            maxW = sum;
            result.clear();
            result.push_back(e);
        } else if (sum == maxW) {
            result.push_back(e);
        }
    }
    output(maxW, result);
}

int main() {
    freopen("./testcase/2input.txt", "r", stdin);
    input();
    calcTransitiveMatrix();
    solve();
}
