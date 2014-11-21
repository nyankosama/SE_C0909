/*=============================================================================
#
# Author: Nyankosama email:i@nyankosama.com
#
# Last modified: 2014-11-21 04:44
#
# Filename: popular_cow.cpp
#
# Description: 万人迷问题(http://poj.org/problem?id=2186)
#
=============================================================================*/
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

#define MAX_N 100

int vn, en;
vector<int> g[MAX_N];
vector<int> reverse_post_order;
bool marked[MAX_N];

int scc[MAX_N];
int scc_count;
vector<int> scc_vertex[MAX_N];
vector<int> scc_g[MAX_N];
vector<int> scc_g_reverse[MAX_N];
int scc_finish_time[MAX_N];
int finish_time_scc[MAX_N * 2];

void input(){
    cin >> vn >> en;
    for (int i = 0; i < en; i++){
        int v;
        int w;
        cin >> v >> w;
        g[v].push_back(w);
    }
}

void output(int max_scc){
    for (auto v : scc_vertex[max_scc]){
        cout << v << " "; 
    }
    cout << endl;
}

void dfs_reverse_order(int v){
    marked[v] = true;
    for (auto w : g[v]){
        if (!marked[w]) dfs_reverse_order(w); 
    }
    reverse_post_order.push_back(v);
}

void dfs_scc(int v, int count){
    marked[v] = true;
    scc[v] = count;
    scc_vertex[count].push_back(v);
    for (auto w : g[v]){
        if (!marked[w]) dfs_scc(w, count);
    }
}

void dfs_scc_reverse(int v, int& count){
    marked[v] = true;
    for (auto w : scc_g_reverse[v]){
        if (!marked[w]) dfs_scc_reverse(w, ++count);  
    }
    scc_finish_time[v] = ++count;
    finish_time_scc[count] = v;
}


int main(){
    freopen("./testcase/popular_cows_input.txt", "r", stdin);
    //freopen("./testcase/popular_cows_output.txt", "w", stdout);
    input();
    memset(marked, 0, MAX_N);
    for (int i = 0; i < vn; i++){
        if (!marked[i]) dfs_reverse_order(i);
    }
    memset(marked, 0, MAX_N);
    for (auto v : reverse_post_order){
        if (!marked[v]){
            dfs_scc(v, scc_count); 
            scc_count++;
        } 

    }
    //强连通分量缩点
    for (int v = 0; v < vn; v++){
        for (auto w : g[v]){
            if (scc[v] != scc[w]){
                scc_g[scc[v]].push_back(scc[w]);
            } 
        }
    }    
    //求汇就等于求源，对scc_g取reverse
    for (int v = 0; v < vn; v++){
        for (auto w : scc_g[v]){
            scc_g_reverse[w].push_back(v);             
        } 
    }
    memset(marked, 0, MAX_N);
    int count = 0;
    for (int v = 0; v < scc_count; v++){
        if (!marked[v]) dfs_scc_reverse(v, count);
    }
    sort(scc_finish_time, scc_finish_time + scc_count, greater<int>());
    int max_scc = finish_time_scc[scc_finish_time[0]];
    output(max_scc);
}
