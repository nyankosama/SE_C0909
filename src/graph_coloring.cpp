/*=============================================================================
#
# Author: Nyankosama email:i@nyankosama.com
#
# Last modified: 2014-11-21 04:43
#
# Filename: graph_coloring.cpp
#
# Description: http://poj.org/problem?id=1419
#
=============================================================================*/
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_VN 100

vector<int> g[MAX_VN]; 
bool marked[MAX_VN];
bool color[MAX_VN]; //false for white, true for black
int vn, en, tn;
int max_black_color;
vector<int> ret_vertex;

void setup(){
    for (auto gi : g) gi.clear();
    memset(marked, 0, MAX_VN);
    max_black_color = 0;
}

void dfs(int v){
    marked[v] = true;
    bool adj_has_black = false;
    for (auto w : g[v]){
        if (color[w]){
            adj_has_black = true;
            break;
        }
    }
    if (adj_has_black)  color[v] = false;
    else                color[v] = true; 
    for (auto w : g[v]){
        if (!marked[w]) dfs(w);
    }
}


void input(){
    setup();
    cin >> vn >> en;
    for (int i = 0; i < en; i++){
        int v, w;
        cin >> v >> w;
        g[v].push_back(w);
        g[w].push_back(v);
    }
}

void process(){
    for (int v = 0; v < vn; v++){
        if (!marked[v]) dfs(v); 
    }
    for (int i = 0; i < vn; i++){
        if (color[i] == true){
            max_black_color++;
            ret_vertex.push_back(i);
        }
    }
}

void output(){
    cout << max_black_color << endl;
    for (auto v : ret_vertex) cout << v << " ";
    cout << endl;
}


int main(){
    freopen("./testcase/graph_coloring_input.txt", "r", stdin);
    cin >> tn;
    for (int i = 0; i < tn; i++){
        input();
        process();
        output();
    }
}
