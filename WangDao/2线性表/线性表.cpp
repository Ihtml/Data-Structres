#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
using namespace std;

const int MaxSize = 50;
// 线性表的顺序存储类型
struct SqList {
    int data[MaxSize];
    int length;
};
// struct SqList list1; // C语言写法
SqList list1;  // C++不用写struct

// 动态分配
const int InitSize = 100;
struct SeqList {
    int *data;  // 指示动态分配数组的指针
    int MaxSize, length;  // 数组最大容量和当前个数
};

// C语言的初始动态分配语句
// struct SeqList SeqList1;
// SeqList1.data = (int*)malloc(sizeof(int) * InitSize);

// C++初始动态分配语句
// SeqList SeqList1;
// SeqList1.data = new int[InitSize];

int main() {
    return 0;
}