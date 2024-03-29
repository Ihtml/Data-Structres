#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
using namespace std;

const int MaxSize = 50;
typedef struct {
    int data[MaxSize];  // 存放队列元素
    // 初始状态（队空条件） Q.front==Q.rear==0
    int front, rear;  // 队头指针和队尾指针
} SqQueue;

// 循环队列
void InitQueue(SqQueue& Q) {
    Q.rear = Q.front = 0;  // 初始化队首、队尾指针
}
// 循环队列判队空
bool isEmpty(SqQueue Q) {
    if (Q.rear == Q.front)
        return true;
    else
        return false;
}
// 循环队列入队
bool EnQueue(SqQueue& Q, int x) {
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;  //  队满则报错
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;  // 队尾指针加1取模
    return true;
}
// 循环队列出队
bool DeQueue(SqQueue& Q, int& x) {
    if (Q.rear == Q.front)
        return false;  // 队空报错
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;  // 队头指针加1
    return true;
}

// 标记法循环队列 增设一个tag整型变量 进队时置tag为1 出队时置为0
// 只有入队操作导致队满、只有出队操作可能导致队空
// 队列Q初始时，置tag=0 front=rear=0
typedef struct {
    int data[MaxSize];  // 存放队列元素
    // 初始状态（队空条件） Q.front==Q.rear==0
    int front, rear;  // 队头指针和队尾指针
    int tag = 0;
} CircleQueue;
void fun(CircleQueue Q, int x) {
    if (Q.front == Q.rear && Q.tag == 0) {
        cout << "队空";
    }
    if (Q.front == Q.rear && Q.tag == 1) {
        cout << "队满";
    }
    // 进队
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    Q.tag = 1;
    // 出队
    x = Q.data[Q.front];
    Q.front = (Q.front - 1) % MaxSize;
    Q.tag = 0;
}

int EnCircleQueue(CircleQueue& Q, int x) {
    if (Q.front == Q.rear && Q.tag == 1) {
        return 0;
    }
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    Q.tag = 1;
    return 1;
}

int DeCircleQueue(CircleQueue& Q, int& x) {
    if (Q.front == Q.rear && Q.tag == 0) {
        return 0;  // 队空
    }
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    Q.tag = 0;
    return 1;
}

// 队列的链式存储结构
typedef struct LinkNode {  // 链式队列结点
    int data;
    struct LinkNode* next;
} LinkNode;
typedef struct {             // 链式队列
    LinkNode *front, *rear;  // 队列的队头和队尾指针
} LinkQueue;

// 链式队列初始化
void InitQueue(LinkQueue& Q) {
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));  // 建立头结点
    Q.front->next = NULL;
}

// 判队空
bool IsEmpty(LinkQueue Q) {
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

// 入队
void EnQueue(LinkQueue& Q, int x) {
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;  // 创建新结点，插入到链尾
    Q.rear->next = s;
    Q.rear = s;
}

// 出队
bool DeQueue(LinkQueue& Q, int& x) {
    if (Q.front = Q.rear)
        return false;  // 空队
    LinkNode* p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;  // 原队列中只有一个结点，删除后变空
    free(p);
    return true;
}

// 将队列中的元素逆置
void Inverser(stack<int>& S, queue<int>& Q) {
    int temp;
    while (Q.size() != 0) {
        temp = Q.front();
        Q.pop();
        S.push(temp);
    }
    while (S.size() != 0) {
        temp = S.top();
        Q.push(temp);
        S.pop();
    }
}

int Fib(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return Fib(n - 1) + Fib(n - 2);
    }
}