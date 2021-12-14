#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/* 用于构造二叉树********************************** */
int index = 1;
typedef char String[24]; /*  0号单元存放串的长度 */
String str;

Status StrAssign(String T, char* chars) {
    int i;
    if (strlen(chars) > MAXSIZE)
        return ERROR;
    else {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
            T[i] = *(chars + i - 1);
        return OK;
    }
}

typedef char TElemType;
TElemType Nil = ' '; /* 字符型以空格符为空 */

Status visit(TElemType e) {
    printf("%c ", e);
    return OK;
}

typedef struct BiTNode /* 结点结构 */
{
    TElemType data;                  /* 结点数据 */
    struct BiTNode *lchild, *rchild; /* 左右孩子指针 */
} BiTNode, *BiTree;

/* 构造空二叉树T */
Status InitBiTree(BiTree* T) {
    *T = NULL;
    return OK;
}

/* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
void DestroyBiTree(BiTree* T) {
    if (*T) {
        if ((*T)->lchild)                 /* 有左孩子 */
            DestroyBiTree(&(*T)->lchild); /* 销毁左孩子子树 */
        if ((*T)->rchild)                 /* 有右孩子 */
            DestroyBiTree(&(*T)->rchild); /* 销毁右孩子子树 */
        free(*T);                         /* 释放根结点 */
        *T = NULL;                        /* 空指针赋0 */
    }
}

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(BiTree* T) {
    TElemType ch;

    /* scanf("%c",&ch); */
    ch = str[index++];

    if (ch == '#')
        *T = NULL;
    else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
            exit(OVERFLOW);
        (*T)->data = ch;             /* 生成根结点 */
        CreateBiTree(&(*T)->lchild); /* 构造左子树 */
        CreateBiTree(&(*T)->rchild); /* 构造右子树 */
    }
}
