/*
假设有4个点: 0, 1, 2, 3
它们之间的边权如下:
0------1
|      |
|      |
|      |
2------3

可以写成矩阵：
   0 1 2 3
0  0 1 1 0
1  1 0 0 1
2  1 0 0 1
3  0 1 1 0
*/
#include <iostream>
using namespace std;

int main() {
    const int N = 4;
    int graph[N][N] = {0};

    // undirected graph
    graph[0][1] = 1;
    graph[1][0] = 1;

    graph[0][2] = 1;
    graph[2][0] = 1;

    graph[1][3] = 1;
    graph[3][1] = 1;

    graph[2][3] = 1;
    graph[3][2] = 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}