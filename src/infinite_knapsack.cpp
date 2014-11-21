#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_WEIGHT 100

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
int sum[MAX_WEIGHT];

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
    cout << sum[target_weight] << endl;
}

void process(){
    sort(items.begin(), items.end());
    int min_weight = items[0].weight;
    for (int w = min_weight; w < MAX_WEIGHT; w++)
        for (auto item : items)
            if (w >= item.weight) sum[w] = max(sum[w - 1], sum[w - item.weight] + item.value);
}

int main(){
    freopen("./testcase/infinite_knapsack_input.txt", "r", stdin);
    input();
    process();
    output();
#ifdef DEBUG
    for (int i = 0; i < 21; i++){
        cout << "sum["  << i << "]=" << sum[i] << endl;    
    }
    cout << endl;
    for (int i = 0; i < 21; i++){
        cout << "weightTo["  << i << "]=" << weightTo[i] << endl;    
    }
#endif 
}
