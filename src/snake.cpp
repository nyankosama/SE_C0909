#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_MAP_N 20

int dx[4]= {1,-1,0,0}; //左右上下
int dy[4]= {0,0,-1,1};
char map[MAX_MAP_N][MAX_MAP_N];//地图
bool is_visit[MAX_MAP_N][MAX_MAP_N][4];
int tx,ty; //target
int sx,sy; //snake的头部
int n,m; //n m 是地图的长宽
int snake_lenth;

struct State {
    int hx;
    int hy;
    int move;
    char map[MAX_MAP_N][MAX_MAP_N];
    bool is_finish = false;

    State(int hx, int hy, char omap[MAX_MAP_N][MAX_MAP_N])
        :hx(hx), hy(hy), move(0) {
        memcpy(map, omap, MAX_MAP_N * MAX_MAP_N);
    }

    State(const State& another) {
        hx = another.hx;
        hy = another.hy;
        move = another.move;
        memcpy(map, another.map, MAX_MAP_N * MAX_MAP_N);
    }

    void print_self() {
        cout << "print_self start===========" << endl;
        cout << "hx:" << hx << ", hy:" << hy << endl;
        cout << "move:" << move << endl;
        cout << "map:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
        cout << "print_self end===========" << endl;
    }

    bool can_go(int x, int y) {
        if (x < 0 || x >= MAX_MAP_N || y < 0 || y >= MAX_MAP_N)
            return false;
        if (map[x][y] == '@')
            return true;
        if (map[x][y] != '.')
            return false;
        return true;
    }

    void go(int x, int y) {
        if (x == tx && y == ty) is_finish = true;
        hx = x;
        hy = y;
        move++;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] >= '1' && map[i][j] <= '9') {
                    if (map[i][j] - '0' == snake_lenth) {
                        map[i][j] = '.';
                    } else {
                        map[i][j]++;
                    }
                }
            }
        }
        map[x][y] = '1';
    }

};

void input() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char tmp;
            cin >> tmp;
            if (tmp == '@') {
                tx = i;
                ty = j;
            } else if (tmp >= '0' && tmp <= '9') {
                if (tmp == '1') {
                    sx = i;
                    sy = j;
                }
                snake_lenth++;
            }
            map[i][j] = tmp;
        }
    }
}

void output(int move) {
    cout << move << endl;
}



int main() {
    //freopen("./testcase/snake_input.txt", "r", stdin);
    input();
    State start(sx, sy, map);
    queue<State> q;
    q.push(start);
    cout << "start" << endl;
    start.print_self();
    cout << "bfs begin" << endl;
    while(!q.empty()) {
        State cur = q.front(); q.pop();
        cout << "bfs cur$$$$$$$$$$$$$$$$$:" << endl;
        cur.print_self();
        //左右上下
        for (int i = 0; i < 4; i++) {
            int x = cur.hx + dx[i];
            int y = cur.hy + dy[i];
            State next(cur);
            cout << "bfs next x:" << x << ", y:" << y << endl;
            if (cur.can_go(x, y) && !is_visit[x][y][i]) {
                next.go(x, y);
                is_visit[x][y][i] = true;
                cout << "next ok:" << endl;
                next.print_self();
                if (next.is_finish) {
                    cout << "finish!" << endl;
                    next.print_self();
                    output(next.move);
                    return 0;
                }
                q.push(next);
            }
        }
    }
    cout << "Imposible!" << endl;
}
