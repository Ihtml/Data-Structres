## 1、树的定义 

当根据某个给定元素K，从集合中查找相同元素时，如果集合是连续切有序的，可以使用二分查找算法：

 ```c
int BinarySearch(StaticTable* Tbl, ElementType K) {
  int left, right, mid, NoFound = -1;
  left = 1;
  right = Tbl->Length;
  while (left <= right) {
    mid = (left + right) / 2;
    if (K < Tbl->Element[mid])
      right = mid - 1;
    else if (K > Tbl->Element[mid])
      left = mid + 1;
    else
      return mid;
  }
  return NotFound;
}
 ```

二分查找算法的时间复杂度为O(logN)；

11个元素的二分查找判定树

![](https://raw.githubusercontent.com/Ihtml/images/master/img/20200412162800.png)

- 判定树上每个**结点**需要的查找次数刚好 为该结点所在的**层数**;

- 查找成功时**查找次数**不会超过判定树的**深度**；

- n个结点的判定树的深度 为[log2n]+1.

- 平均查找次数：ASL = (4 * 4+4 * 3+2 * 2+1)/11 = 3

  

**树**(Tree): n(n≥0)个结点构成的有限集合。 当n=0时，称为**空树**;
 对于任一棵**非空树**(n> 0)，它具备以下性质:

- 树中有一个称为“**根(Root)**”的特殊结点，用 r 表示;
- 其余结点可分为m(m>0)个**互不相交的**有限集T1，T2，... ，Tm，其 中每个集合本身又是一棵树，称为原来树的“**子树**(SubTree)”
- 子树是**不相交**的;
- 除了根结点外，**每个结点有且仅有一个父结点**;
- 一棵N个结点的树有**N-1条边**。



树的一些基本术语：

1. **结点的度**(Degree):结点的**子树个数**；

2. **树的度**:树的所有结点中最大的度数；

3. **叶结点**(Leaf):度为0的结点；

4. **父结点**(Parent):有子树的结点是其子树的根结点的父结点；

5. **子结点**(Child):若A结点是B结点的父结点，则称B结点是A结点的子结点;子结点也称孩子结点。

6. **兄弟结点**(Sibling):具有同一父结点的各结点彼此是兄弟结点。

7. **路径和路径长度**:从结点n1到nk的路径为一 个结点序列n1 , n2 ,... , nk , ni是 ni+1的父结 点。路径**所包含边的个数**为路径的长度。

8. **祖先结点**(Ancestor):沿树根到某一结点路径上的所有结点都是这个结点的祖先结点。

9. **子孙结点**(Descendant):某一结点的子树 中的所有结点是这个结点的子孙。

10. **结点的层次**(Level):规定根结点在1层， 其它任一结点的层数是其父结点的层数加1。

11. **树的深度**(Depth):树中所有结点中的**最 大层次**是这棵树的深度。

12. **节点的高度**：对于任意节点n,n的高度为从n到一片树叶的最长路径长，所有**树叶的高度为0**；

13. **节点的深度**：对于任意节点n,n的深度为从根到n的唯一路径长，**根的深度为0；**

   

## 2、二叉树

二叉树是一个**有穷的结点集合**，这个集合可以为空，若不为空，则它是由根结点和称为其左子树TL和右子树TR的，**两个不相交的二叉树组成**。

每个节点都有两个指针，一个指向左边，一个指向右边，每个节点最多有两个儿子(度为2)。

**完美二叉树**(Perfect Binary Tree)又叫**满二叉树**(Full Binary Tree)：每一层的节点数，都是上一层节点数的两倍。

**完全二叉树** (Complete Binary Tree)：有n个结点的二叉树，对树中结点按 从上至下、从左到右顺序进行编号， 编号为i(1 ≤ i ≤ n)结点与满二叉树 中编号为 i 结点在二叉树中位置相同。（完全二叉树可以少掉最后几个叶节点。）



二叉树的几个**重要性质：**

- 一个二叉树第 i 层的最大结点数为:**2 i-1，i >= 1**。
- 深度为k的二叉树有最大结点总数为: **2 k-1，k >=1**。
- 对任何非空二叉树 T，若**n0**表示叶结点的个数、**n2**是度为2的非叶结点个数，那么两者满足关系**n0 = n2 +1**。



二叉树的**链式储存结构**：

```c
typedef struct TNode *Position;
typedef Position BinTree; // 二叉树类型
struct TNode{ // 树节点定义
    ElementType Data;
    BinTree Left; // 指向左树
    BinTree Right; // 指向右树
};
```



**二叉树的遍历**：

核心问题：**二维结构的线性化**
 从一个结点访问其左、右儿子结点时，访问左儿子后，右儿子结点怎么办?

需要**一个存储结构保存暂时不访问的结点**。（存储结构:堆栈、队列）

1. 递归实现

- 先序遍历 先访问根节点，再对左边递归，再对右边递归

  ```c
  void PreOrderTraversal(BinTree BT) {
    if (BT) {
      printf("%d", BT->Data);
      PreOrderTraversal(BT->Left);
      PreOrderTraversal(BT->Right);
    }
  }
  ```

  

- 中序遍历 先递归访问左子树，再访问根节点，再遍历右子树

  ```c
  void InOrderTraversal(BinTree BT) {
    if (BT) {
      PreOrderTraversal(BT->Left);
      printf("%d", BT->Data);
      PreOrderTraversal(BT->Right);
    }
  }
  ```

  

- 后序遍历 先递归遍历左边，再遍历右边，最后根节点

  ```c
  void PostOrderTraversal(BinTree BT) {
    if (BT) {
      PreOrderTraversal(BT->Left);
      PreOrderTraversal(BT->Right);
      printf("%d", BT->Data);
    }
  }
  ```

  

2. **非递归遍历**（使用**堆栈**）：

- 先序

  ```c
  void PreOrderTraversal(BinTree BT) {
    BinTree T = BT;
    Stack S = CreatStack(MaxSize);
    while (T || !IsEmpty(S)) {
      while (T) {
        printf("%5d", T->Data);
        Push(S, T);
        T = T->Left;
      }
      if (!IsEmpty(S)) {
        T = Pop(S);
        T = T->Right;
      }
    }
  }
  ```

  

- 中序

  ```c
  void InorderTraversal(BinTree BT) {
    BinTree T = BT;
    Stack S = CreatStack(MaxSize);
    while (T || !IsEmpty(S)) {
      while (T) {
        Push(S, T);
        T = T->Left;
      }
      if (!IsEmpty(S)) {
        T = Pop(S);
        printf("%5d", T->Data);
        T = T->Right;
      }
    }
  }
  ```

  

- 后序

  ```c
  void PostOrderTraversal(BinTree BT) {
    BinTree T = BT, P = NULL; // P为上一个访问的节点
    Stack S = CreatStack(MaxSize);
    while (T || !IsEmpty(S)) {
      Push(S, T);
      T = T->Left;
    }
    if (!IsEmpty(S)) {
      T = Pop(S);
      if (T->Right == NULL || T->Right == P) {
        // 右节点不存在或右节点已访问，弹出节点
        printf("%5d", T->Data);
        P = T; // P指向当前被访问的节点
        T = NULL;
      } else {
        Push(T); // 如果有右节点，该节点再次入栈
        T = T->Right; // 继续遍历右树
      }
    }
  }
  ```

  

3. 层序遍历（使用队列）

   **队列实现**:遍历从根结点开始，首先将根结点入队，然后开始执行循环:结点出队、访问该结点、其左右儿子入队。

   1. 从队列中取出一个元素;
   2. 访问该元素所指结点;
   3. 若该元素所指结点的左、右孩子结点非空，则将其左右节点的指针顺序入队。

   ```c
   void LevelOrderTraversal(BinTree BT) {
     Queue Q;
     BinTree T;
     if (!BT)
       return;
     Q = CreatQueue(MaxSize);
     AddQ(Q, BT);
     while (!IsEmptyQ(Q)) {
       T = DeleteQ(Q);
       printf("%5d", T->Data);
       if (T->Left) {
         AddQ(Q, T->Left);
       }
       if (T->Right) {
         AddQ(Q, T->Right);
       }
     }
   }
   ```



4. 由两种遍历序列确定二叉树

   必须要有中序遍历，和其他一种遍历才能确定第三种遍历序列

   - 先序和中序遍历序列来确定一棵二叉树
     1. 根据**先序**遍历序列第一个结点确定**根结点;**
     2. 根据根结点在**中序遍历序列**中分割出左右两个子序列
     3. 对**左子树和右子树分别递归**使用相同的方法继续分解
   - 后序和中序遍历序列确定一棵二叉树
     1. 根据**后序**遍历序列最后一个结点确定**根结点**;
     2. 根据根结点在**中序遍历序列**中分割出左右两个子序列
     3. 对**左子树和右子树分别递归**使用相同的方法继续分解



## 3、二插搜索树

**二叉搜索树的定义**:一棵二叉树，可以为空;如果不为空，满足以下性质:

1. 非空**左子树**的所有**键值小于其根结点**的键值。
2. 非空**右子树**的所有**键值大于其根结点**的键值。
3. **左、右子树都是二叉搜索树**。



**二叉搜索树的查找**：

```c
// 二叉搜索树的查找 查找效率决定于树的高度
Position Find(ElementType X, BinTree BST) {
  while (BST) {
    if (X > BST->Data) {
      BST = BST->Right;
    } else if (X < BST->Data) {
      BST = BST->Left;
    } else {
      return BST;
    }
    return NULL;
  }
}
```



**查找最大和最小元素：**

- **最大元素**一定是在树的**最右分枝的端结点**上

- **最小元素**一定是在树的**最左分枝的端结点**上

```c
// 查找最小元素
Position FindMin(BinTree BST) {
  if (!BST) {
    return NULL;
  } else if (!BST->Left) {
    return BST;
  } else {
    return FindMin(BST->Left);
  }
}
// 查找最大元素
Position FindMax(BinTree BST) {
  if (BST) {
    while (BST->Right) {
      BST = BST->Right;
    }
  }
  return BST;
}
```



**二叉搜索树的插入：**

 ```c
BinTree Insert(ElementType X, BinTree BST) {
  if (!BST) { // 原树为空，生成并返回一个节点的二叉树
    BST = malloc(sizeof(struct TNode));
    BST->Data = X;
    BST->Right = NULL;
    BST->Left = NULL;
  } else { // 找要插入的位置
    if (X < BST->Data) {  // 递归插入左子树
      BST->Left = Insert(X, BST->Left);
    } else if (X > BST->Data) { // 递归插入右子树
      BST->Right = Insert(X, BST->Right);
    }
    // 如果 X已经存在，不需要再插入
  }
  return BST;
}
 ```



**二叉树的删除：**

考虑三种情况：

1. 要删除的是**叶结点**:直接删除，并再修改其父结点指针---置为NULL
2. 要删除的结点**只有一个孩子结点**: 将其**父结点**的指针**指向**要删除结点的**孩子结点**
3. 要删除的结点**有左、右两棵子树**: 用另一结点替代被删除结点:**右子树的最小元素** 或者 **左子树的最大元素**

```c
BinTree Delete(ElementType X, BinTree BST) {
  if (!BST) {
    printf("要删除的元素未找到");
  } else if (BST->Data < X) {
    BST->Right = Delete(X, BST->Right);
  } else if (BST->Data > X) {
    BST->Left = Delete(X, BST->Left);
  } else {
    Position Tmp;
    if (BST->Left && BST->Right) { // 被删除的元素有两个节点
      Tmp = FindMin(BST->Right); // 在右子树中找到最小元素填充删除节点
      BST->Data = Tmp->Data;
      BST->Right = Delete(Tmp->Data, BST->Right); // 在删除节点的右子树中删除最小元素
    } else { // 被删除元素有一个或没有节点
      Tmp = BST;
      if (!BST->Left) { // 有右节点或无子节点
        BST = BST->Right;
      } else if (!BST->Right) { // 有左节点
        BST = BST->Left;
      }
      free(Tmp);
    }
  }
  return BST;
}
```



## 4、平衡二叉树

搜索树结点不同插入次序，将导致不同的**深度**和平**均查找长度ASL**

**平衡因子**(Balance Factor，简称BF): **BF(T) = hL-hR**， 其中hL和hR分别为T的左、右子树的高度。

**平衡二叉树**(Balanced Binary Tree)(**AVL树**) 空树，或者**任一结点左、右子树高度差的绝对值不超过1**，即**|BF(T) |≤ 1**

AVL树是最早被发明的**自平衡二叉查找树**。基本操作一般涉及运作同在不平衡的二叉查找树所运作的同样的算法。但是要进行预先或随后做一次或多次所谓的"**AVL旋转"。**

**给定节点数为n的AVL数的最大高度为O(log2n)**

平衡二叉树储存结构：

```c
typedef struct AVLNode* Position;
typedef Position AVLTree;
struct AVLNode {   // AVL树类型
  ElementType Data;  // 节点数据
  AVLTree Left;
  AVLTree Right;
  int Height;
};
```

AVL旋转：

```c
int Max(int a, int b) {
  return a > b ? a : b;
}
int GetHeight(AVLTree root) {
  if (root == NULL) {
    return 0;
  }
  return Max(GetHeight(root->Left), GetHeight(root->Right)) + 1;
}
AVLTree SingleLeftRotation(AVLTree A) {
  AVLTree B = A->Left;  // 这里A必须有个左子节点B
  A->Left = B->Right;   // A与B做左单旋，更新A与B的高度，返回新的根节点B
  B->Right = A;
  A->Height = GetHeight(A);
  B->Height = GetHeight(B);
  return B;
}
AVLTree SingleRightRotation(AVLTree A) {
  AVLTree B = A->Right; 
  A->Right = B->Left;
  B->Left = A;
  A->Height = GetHeight(A);
  B->Height = GetHeight(B);
  return B;
}
AVLTree DoubleLeftRightRotation(AVLTree A) {
    // 这里A必须有个左子节点B，且B必须有个右子节点C
    // B与C做右单旋，返回C
  A->Left = SingleRightRotation(A->Left); 
    // A与C做左单旋，返回C
  return SingleLeftRotation(A);
}
AVLTree DoubleRightLeftRotation(AVLTree A) {
  A->Right = SingleLeftRotation(A->Right);
  return SingleRightRotation(A);
}
```

AVL树插入新节点

```c
AVLTree Insert(AVLTree T, ElementType X) {
  if (!T) {
    T = (AVLTree)malloc(sizeof(struct AVLNode));
    T->Data = X;
    T->Height = 0;
    T->Left = T->Right = NULL;
  } else if (X < T->Data) {
    T->Left = Insert(T->Left, X);
    if (GetHeight(T->Left) - GetHeight(T->Right) == 2) {
      if (X < T->Left->Data) {
        T = SingleLeftRotation(T);
      } else {
        T = DoubleLeftRightRotation(T);
      }
    }
  } else if (X > T->Data) {
    T->Right = Insert(T->Right, X);
    if (GetHeight(T->Right) - GetHeight(T->Left) == 2) {
      if (X > T->Right->Data) {
        T = SingleRightRotation(T);
      } else {
        T = DoubleRightLeftRotation(T);
      }
    }

  } else {
    // X == T->Data 无须插入
  }
  // 每次都要更新树高
  T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
  return T;
}
```



## 5、堆

**优先队列**(Priority Queue):特殊的“队列”，取出元素的顺序是 依照元素的优先权(关键字)大小，而不是元素进入队列的先后顺序。

优先队列用完全二叉树表示就是**堆**。

堆的两个特性：

- 结构性：用**数组表示的完全二叉树**
- 有序性：任一节点的关键字是起子树所有节点的最大值（或最小值）
  - “最大堆(MaxHeap)”,也称“大顶堆”:每个结点的元素值**不小于**其子结点的元素值
  - “最小堆(MinHeap)”,也称“小顶堆” :每个结点的元素值**不大于**其子结点的元素值

堆的结构：

```c
typedef struct HeapStruct* MaxHeap;
struct HeapStruct {
  ElementType* Elements;  // 储存元素的数组
  int Size;               // 堆当前元素的个数
  int Capacity;           // 堆最大容量
};
```

最大堆的创建：

```c
MaxHeap Create(int MaxSize) {
  MaxHeap H = malloc(sizeof(struct HeapStruct));  // 创建容量为MaxSize的空的最大堆
  H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));
  H->Size = 0;
  H->Capacity = MaxSize;
  H->Elements[0] = MaxData;  // 定义“哨兵”为大于堆中所有可能的元素的值，便于以后更快操作
  return H;
}
```

最大堆的插入：

```c
bool isFull(MaxHeap H) {
  return H->Size >= H->Capacity;
}
void Insert(MaxHeap H, ElementType item) {
  if (isFull(H)) {
    printf("最大堆已满");
    return;
  }
  int i = ++H->Size;  // i指向插入后堆中的最后一个元素的位置
  for (; H->Elements[i / 2] < item; i /= 2) {
    H->Elements[i] = H->Elements[i / 2];  // 向下过滤节点
  }
  H->Elements[i] = item;  // 将item 插入
}
```

最大堆的删除：

```c
// 最大堆的删除,从最大堆H中取出键值为最大的元素，并删除一个结点
ElementType DeleteMax(MaxHeap H) {
  int Parent, Child;
  ElementType MaxItem, temp;
  if (isEmpty(H)) {
    printf("最大堆已空");
    return;
  }
  MaxItem = H->Elements[1];  // 取出根节点最大值
  // 用最大堆中最后一个元素从根节点开始向上过滤下层节点
  temp = H->Elements[H->Size--];
  for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
    Child = Parent * 2;
    if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1])) {
      Child++;  // Child指向左右子节点的较大者
    }
    if (temp >= H->Elements[Child]) {
      break;
    } else {
      H->Elements[Parent] = H->Elements[Child];
    }
  }
  H->Elements[Parent] = temp;
  return MaxItem;
}
```



## 6、哈夫曼树

**带权路径长度(WPL):**设二叉树有n个叶子结点，每个叶子结点带

有权值 wk，从根结点到每个叶子结点的长度为 lk，则每个叶子结点的**带权路径长度之和**就是: WPL；

**哈夫曼树**或**最优二叉树**是WPL最小的二叉树；

哈夫曼树解决了：如何根据结点不同的查找频率构造更有效的搜索树的问题。

哈夫曼树的构造：每次把**权值最小的两颗**二叉树合并；

哈夫曼树的特点：

- **没有度为1的节点**（构造的时候每次都是两个节点并在一起，形成一个新的节点）

- n个叶子节点的哈夫曼树共有2n-1个节点

- 哈夫曼树的任意非叶节点的**左右树交换**后仍是哈夫曼树

- 对同一组权值{w1 ,w2 , ...... , wn}，存在WPL相同的、不同构(树的形状不一样)的两棵哈夫曼树，


**哈夫曼编码**：

给定一段字符串，对字符进行**不等长编码**，出现频率高的字符用的编码短些，出现频率低的字符编码长些，可以使得该字符串的编码存储空间最少。

为了避免二义性，要使编码满足**前缀码**，即**任何字符的编码都不是另一字符编码的前缀**。可以用二叉树编码。

二叉树编码：

- 左右分支：0、1
- 字符只在叶节点上（否则一个字符的编码可能是另一个字符的前缀）

使用哈夫曼树进行编码，可以使编码代价最小。

构造哈夫曼树：

```c
typedef struct TreeNode* HuffmanTree;
struct TreeNode {
  int Weight;
  HuffmanTree Left, Right;
};
HuffmanTree Huffman(MinHeap H) {
  // 假设H->Size个权值已经存在H->Elements[]->Weight里
  HuffmanTree T;
  BuildMinHeap(H);  // 将H->Elements[]按权值调整为最小值
  for (int i = 1; i < H->Size; i++) {  // 做H->Size-1次合并，最后堆里只有一棵树
    T = malloc(sizeof(struct TreeNode)); // 建立新结点
    T->Left = DeleteMin(H); // 从最小堆中删除一个结点，作为新T的左子结点
    T->Right = DeleteMin(H); // 从最小堆中删除一个结点，作为新T的右子结点
    T->Weight = T->Left->Weight + T->Right->Weight; // 计算新权值
    Insert(H, T); // 将新T插入最小堆
  }
  T = DeleteMin(H);
  return T;
}
```



## 7、并查集

**并查集**: 集合合并后、查找某元素属于什么集合。

并查集问题中集合存储可以用**树结构**表示，树的每个节点代表一个集合元素,指向其父亲（双亲表示法）。

每个元素类型描述为：

```c
typedef struct {
	ElementType Data;
	int Parent; // 用-N表示。N为集合元素个数
} SetType;
```
查找某个元素所在的集合（用根节点表示）
```c
ElementType Find(SetType S[], ElementType X) {
  int i;
  for (i = 0; i < MAXN && S[i].Data != X; i++)
    ;
  if (i >= MAXN)
    return -1;  // 未找到X元素，返回-1
  for (; S[i].Parent >= 0; i = S[i].Parent)
    ;
  return i; // 找到X所属的集合，返回树根节点在数组S中的下标
}
```

集合并运算

```c
void Union(SetType S[], ElementType Root1, ElementType Root2) {
  ElementType Root1, Root2;
  Root1 = Find(S, Root1);
  Root2 = Find(S, Root2);
  if (S[Root2].Parent < S[Root1].Parent) { // 集合2的元素个数更多
    S[Root2].Parent += S[Root1].Parent;  // 集合1并入集合2
    S[Root1].Parent = Root2;
  } else {
    S[Root1].Parent += S[Root2].Parent;
    S[Root2].Parent = Root1;
  }
}
```

