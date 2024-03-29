#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

using namespace std;
const int MAXVertexNum = 100;  //  顶点数目最大值
const int infinity = INT_MAX;
typedef char VertexType;  //  顶点的数据类型
typedef int EdgeType;     //  带权图中边上权值的数据类型
typedef struct {
    VertexType Vex[MAXVertexNum];               // 顶点表
    EdgeType Edge[MAXVertexNum][MAXVertexNum];  // 邻接矩阵 边表
    int vexnum, arcnum;  // 图的当前顶点数和弧数
} MGraph;

typedef struct ArcNode {  // 边表结点
    int adjvex;           // 该弧所指向的顶点位置
    struct ArcNode* next;
} ArcNode;

typedef struct VNode {  // 顶点表结点
    VertexType data;    // 顶点信息
    ArcNode* first;     //  指向第一条依附该顶点的弧的指针
} VNode, AdjList[MAXVertexNum];
typedef struct {
    AdjList vertices;    // 邻接表
    int vexnum, arcnum;  // 图的顶点数和弧数
} ALGraph;               // ALGraph是以邻接表存储的图类型

queue<int> Q;
bool visited[MAXVertexNum];
int d[MAXVertexNum];
void BFSTraverse(MGraph G) {
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            BFS(G, i);
        }
    }
}
void BFS(MGraph G, int v) {
    cout << v;
    visited[v] = true;
    Q.push(v);
    while (Q.size() != 0) {
        v = Q.front();
        Q.pop();
        // for (w = FirstNeighbor(G, v); w >= 0; w = NextNeibor(G, v, w)) {
        //     if (!visited[w]) {
        //         cout << w;
        //         visited[w] = true;
        //         Q.push(w);
        //     }
        // }
    }
}
void BFS_Min_Distance(MGraph G, int u) {
    for (int i = 0; i < G.vexnum; i++) {
        d[i] = infinity;
    }
    visited[u] = true;
    d[u] = 0;
    Q.push(u);

    while (Q.size() != 0) {
        u = Q.front();
        Q.pop();
        // for (w = FirstNeighbor(G, v); w >= 0; w = NextNeibor(G, v, w)) {
        //     if (!visited[w]) {
        //         cout << w;
        //         visited[w] = true;
        //         d[w]=d[u]+1;
        //         Q.push(w);
        //     }
        // }
    }
}

void DFSTraverse(MGraph G) {
    for (int v = 0; v < G.vexnum; v++) {
        visited[v] = false;
    }
    for (int v = 0; v < G.vexnum; v++) {
        if (!visited[v]) {
            DFS(G, v);
        }
    }
}

void DFS(MGraph G, int v) {
    cout << v;
    visited[v] = true;
    // for (w = FirstNeighbor(G, v); w >= 0; w = NextNeibor(G, v, w)) {
    //     if (!visited[w]) {
    //         DFS(G,W);
    //     }
    // }
}

bool isTree(MGraph G) {
    for (int i = 1; i < G.vexnum; i++) {
        visited[i] = false;
    }
    int Vnum = 0, Enum = 0;  // 记录顶点数和边数
    DFSTree(G, 1, Vnum, Enum, visited);
    if (Vnum == G.vexnum && Enum == 2 * (G.vexnum - 1)) {
        return true;  // 若一次遍历就能访问到n个顶点和n-1条边，可判定此图是一棵树
    } else {
        return false;
    }
}

void DFSTree(MGraph& G, int v, int& Vnum, int& Enum, bool visited[]) {
    // 深度优先遍历图 统计访问过的顶点数和边数 通过Vnum和Enum返回
    visited[v] = true;
    Vnum++;
    // int w = FirstNeighbor(G, v)
    // while (w != -1) {
    //     Enum++;
    //     if (!visited[w]) {
    //         DFSTree(G, w, Vnum, Enum, visited);
    //     }
    //     w = NextNeighbor(G, v, w);
    // }
}

int NextNeighor(MGraph& G, int x, int y) {
    if (x != -1 && y != -1) {
        for (int col = y + 1; col < G.vexnum; col++) {
            if (G.Edge[x][col] > 0 && G.Edge[x][col] < infinity) {
                return col;
            }
        }
    }
    return -1;
}

int ALGraphNextNeighor(ALGraph& G, int x, int y) {
    if (x != -1) {                         // 顶点x存在
        ArcNode* p = G.vertices[x].first;  // 对应边链表第一个边结点
        while (p != NULL && p->adjvex != y) {  // 寻找邻接顶点y
            p = p->next;
        }
        if (p != NULL && p->next != NULL) {
            return p->next->adjvex;  // 返回下一个邻接顶点
        }
    }
    return -1;
}