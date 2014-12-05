/*=============================================================================
#
# Author: Nyankosama email:i@nyankosama.com
#
# Last modified: 2014-11-21 04:46
#
# Filename: pair_problem.cpp
#
# Description: 配对问题 intput: pair pair int int int output:pair<pair<int,int>,int>
#
=============================================================================*/
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> tokenList;

void input(){
    string token;
    while(cin >> token){
        tokenList.push_back(token);
    }
}

void output(string ret){
    cout << ret << endl;
}

bool process_pair(vector<string>::size_type start, string& res){
    if (start == tokenList.size()) return false;
    string token = tokenList[start];
    res += token;
    bool ret = true;
    if (token == "pair"){
        res += "<";
        ret = process_pair(++start, res);
        res += ",";
        ret = process_pair(++start, res);
        res += ">";
    } else{
        ret = false; 
    }
    return ret;
}

int main(){
    freopen("./testcase/pair_input.txt", "r", stdin);
    input();
    string ret;
    process_pair(0, ret);
    output(ret);
}
