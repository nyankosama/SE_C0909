#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_WEIGHT 100
#define MAX_ITEM 100

struct Item{
    int id;
    int weight;
    int value;
    friend bool operator < (const Item& it1, const Item& it2){
        return it1.weight < it2.weight;
    }
};

vector<Item> items;
int target_weight;
int kn;
int sum[MAX_ITEM][MAX_WEIGHT];

void input(){
    cin >> kn;
    for (int i = 0; i < kn; i++){
        Item item;
        cin >> item.id >> item.weight >> item.value;
        items.push_back(item);
    }
    cin >> target_weight;
}

void output(){
    cout << sum[kn][target_weight] << endl;
}

void process(){
    sort(items.begin(), items.end());
    for (int j = 1; j <= kn; j++){
        for (int w = 1; w < MAX_WEIGHT; w++){
            if (items[j - 1].weight > w)    
                sum[j][w] = sum[j - 1][w]; 
            else  
                sum[j][w] = max(sum[j - 1][w], sum[j - 1][w - items[j - 1].weight] + items[j - 1].value);
        }
    }
}

int main(){
    freopen("./testcase/infinite_knapsack_input.txt", "r", stdin);
    input();    
    process();
    output();
}
