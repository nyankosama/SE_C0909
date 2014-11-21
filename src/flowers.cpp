/*=============================================================================
#
# Author: Nyankosama email:i@nyankosama.com
#
# Last modified: 2014-11-21 04:41
#
# Filename: flowers.cpp
#
# Description: http://acm.sgu.ru/problem.php?contest=0&problem=104 
#
=============================================================================*/
#include <iostream>
#include <vector>

using namespace std;

#define MAX_FN 100
#define MAX_VN 100

int fn;
int vn;
int A[MAX_FN][MAX_VN];
int S[MAX_FN][MAX_VN];
int vase_index[MAX_FN];
int vaseTo[MAX_VN];


void input(){
    cin >> fn >> vn;
    for (int f = 0; f < fn; f++){
        for (int v = 0; v < vn; v++){
            cin >> A[f + 1][v + 1];
        }
    }
}

void process(){
    S[1][1] =A[1][1];
    for (int f = 1; f <= fn; f++){
        for (int v = 2; v <= vn; v++){
            S[f][v] = max(S[f][v - 1], A[f][v] + S[f - 1][v - 1]);
        }
    }
}

void output(){
    cout << S[fn][vn] << endl;
}

int main(){
    freopen("./testcase/flowers_input.txt", "r", stdin);
    input();
    process();
    output();
}
