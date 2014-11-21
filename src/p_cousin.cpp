/*=============================================================================
#
# Author: Nyankosama email:i@nyankosama.com
#
# Last modified: 2014-11-21 04:44
#
# Filename: p_cousin.cpp
#
# Description: P_Cousin问题
#
=============================================================================*/
#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 100

int vn, en;
vector<int> g[MAX_N];
vector<int> depth_list[MAX_N];
int begin_time[MAX_N];
int finish_time[MAX_N];
int depth[MAX_N];
bool marked[MAX_N];
int root = 0;
int pp;
int pc;

void input() {
    cin >> vn >> en;
    for (int i = 0; i < en; i++) {
        int v, w;
        cin >> v >> w;
        g[v].push_back(w);
        g[w].push_back(v);
    }
    cin >> pp >> pc;
}

void output(const vector<int>& ret){
    for (auto i : ret){
        cout << i << " "; 
    }
    cout << endl;
}

void dfs(int v, int d, int& count){
    marked[v] = true;
    depth[v] = d;
    depth_list[d].push_back(v);
    begin_time[v] = count;
    for (auto w : g[v]) 
        if (!marked[w]) dfs(w, d + 1, ++count);
    finish_time[v] = ++count;
}

void pre_process(){
    int count = 0;
    dfs(root, 0, count);
}

void p_cousin(int parent, int p_cousin, vector<int>& ret){
    int cousin_depth = depth[parent] + p_cousin;
    int p_begin_time = begin_time[parent], p_finish_time = finish_time[parent];
    for (auto v : depth_list[cousin_depth]){
        if (begin_time[v] >= p_begin_time && finish_time[v] <= p_finish_time)
            ret.push_back(v);
    }
}

int main() {
    freopen("./testcase/p_cousin.txt", "r", stdin);
    input();
    pre_process();
    vector<int> ret;
    p_cousin(pp, pc, ret);
    output(ret); 
}
