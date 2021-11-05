#include "string.h"
#include "ctype.h"

#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000 /* 存储空间初始分配量 */

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char ElemType; /* ElemType类型根据实际情况而定，这里假设为char */

Status visit(ElemType c){
    printf("%c ", c);
    return OK;
}

/* 线性表的静态链表存储结构 */
/* 对于没有指针的语言，用数组描述链表，又叫游标实现法 */
typedef struct 
{
    ElemType data;
    int cur; /* 游标(Cursor) ，为0时表示无指向 */
} Component, StaticLinkList[MAXSIZE];

/* 将一维数组space中各分量链成一个备用链表，space[0].cur存放备用链表第一个结点的下标， 
数组最后一个元素的cur存放第一个有数值的元素的下标，相当于单链表中头结点的作用，整个链表为空时，为0
 */
Status InitList(StaticLinkList space) {
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
        space[i].cur = i + 1;
    space[MAXSIZE - 1].cur = 0; /* 目前静态链表为空，最后一个元素的cur为0 */
    return OK;
}

/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SSL(StaticLinkList space) {
    int i = space[0].cur; /* 当前数组第一个元素的cur存的值 */
                          /* 就是要返回的第一个备用空闲的下标 */
    if (space[0].cur)
        space[0].cur = space[i].cur; /* 由于要拿出一个分量来使用了， */
                                     /* 所以我们就得把它的下一个 */
                                     /* 分量用来做备用 */
    return i;
}

/*  将下标为k的空闲结点回收到备用链表 */
void Free_SSL(StaticLinkList space, int k) {
    space[k].cur = space[0].cur; /* 把第一个元素的cur值赋给要删除的分量cur */
    space[0].cur = k; /* 把要删除的分量下标赋值给第一个元素的cur */
}

/* 初始条件：静态链表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(StaticLinkList L) {
    int j = 0;
    int i = L[MAXSIZE - 1].cur; // 最后一个元素相当于头结点
    while (i) {
        i = L[i].cur;
        j++;
    }
    return j;
}
