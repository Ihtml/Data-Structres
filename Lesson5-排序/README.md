## 前提

- 排序算法用**void** **X_Sort ( ElementType A[],** **int** **N )**表示；

- 大多数情况下，为简单起见，讨论从小大的整数排序；

- **N**是正整数；

- 只讨论基于**比较**的排序(**> = <** 有定义)；

- 只讨论**内部**排序；（假设内存空间充分大，所有数据都可以一次性导到内存空间里，排序过程在内存空间里一次性完成）

- 要**稳定性**:任意两个相等的数据，排序前后的相对位置不发生改变；

- 没有一种排序是任何情况下 都表现最好的；

  
  
## 冒泡排序

```c
void Bubble_Sort(ElementType A[], int N) {
  for (int p = N - 1; p >= 0; p--) {
    flag = 0;
    for (i = 0; i < p; i++) {
      if (A[i] > A[i + 1]) {
        Swap(A[i], A[i + 1]);
        flag = 1;
      }
    }
  }
  if (flag == 0)
    break;
}
```
最好情况：顺序 T=O(N)
最坏情况：逆序 T=O(N^2)



## 插入排序

想象打扑克牌摸排

```c
void Insertion_Sort(ElementType A[], int N){
  for	(P=1; P<N; P++){
    Tmp = A[p]; // 取下一位
    for(int i =P; i>0 && Tmp <A[i-1]; i--){
      A[i] = A[i-1]; // 移除空位
    }
    A[i] = Tmp; // 落位
  }
}
```

最好情况：顺序 T=O(N)
最坏情况：逆序 T=O(N^2)



## 时间复杂度下界

- 对于下标**i，如果**A[i]>A[j]**，则称**(i,j)是 一对逆序对(inversion)
- 插入排序：T跟元素个数N和逆序对个数I的关系为：T(N, I) = O(N+1); 如果序列**基本有序**，则插入排序简单且高效；
- 冒泡排序和插入排序，每次循环只能去掉一个逆序对；
- 定理:任意**N**个不同元素组成的序列平均具有 **N** **(** **N** - **1 ) / 4** 个逆序对。
- 定理:任何仅以交换相邻两元素来排序的算法，其平均时间复杂度为  $\Omega$**(** N^2 **)** 。
- 要提高算法效率，必须: 1, 每次消去不止一个逆序对；2，每次交换相隔较远的**2**个元素；



## 希尔排序

定义增量序列Dm > Dm-1 > ... > D1=1,对每个Dk进行“Dk-1”间隔排序(k=m,m-1,...1)

Dk间隔有序的序列，在执行Dk-1间隔排序后，仍然是Dk间隔有序的；

原始希尔排序 Dm = N/2, Dk = (Dk+1) /2

```c
void Shell_Sort(ElementType A[], int N){
  int D, P, tmp, i;
  for( D = N/2; D>0; D/=2){
    for( P = D; P<N; P++){
       tmp = A[p];
      for(i = P; i > D && A[i-D] > tmp; i-=D){
        A[i] = A[i-D]
      }
      A[i] = tmp;
    }
  }
}
```



如果增量元素不互质(没有公约数)，则小增量可能根本不起作用。

**Sedgewick**增量序列：{1,5,9,41,109...}

9✖️4^i - 9✖️2^i + 1 或 4^i -3*2^i + 1

```c
void Shell_Sort(ElementType A[], int N){
  // 用Sedgewick增量序列
  int Si, D, P, i;
  ElementType tmp;
  int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
  for(Si = 0; Sedgewick[Si]>=N; Si++)
    //初始的增量Sedgewick[Si]不能超过待排序列长度
  for(D=Sedgewick[Si]; D>0; D=Sedgewick[++Si]){
    for(P=D; P<N; P++){ // 插入排序
      tmp = A[p];
      for(i=P; i>=D && A[i-D]>tmp; i-=D){
        A[i] = A[i-D];
      }
      A[i] = tmp;
    }
  }
}
```



## 选择排序

```c
void Selection_Sort (ElementType A[], int N){
	for(int i = 0; i < N; i++){
		int MinPostion = ScanForMin(A, i, N-1);
		// 从A[i]到A[N-1]中找最小元，并将其位置赋给MinPosition
		Swap(A[i], A[MinPostion])
		// 将未排序部分最小元换到有序部分的最后位置
	}
}
```

时间复杂度，T=$\theta$(N^2);



## 堆排序

- 算法1

```c
void Heap_Sort(ElementType A[], int N){
	BuildHeap(A); // O(N)  把数组A转换成最小堆
	for(int i = 0; i < N; i++){
		TemA[i] = DeleteMin(A); // O(logN)
	}
  for(int i = 0; i<N; i++){
    A[i] = TmpA[i];
  }
}
```

时间复杂度T(N) = O(N logN)

需要额外O(N)空间，并且复制元素需要时间

- 算法2

```c
void Swap(ElementType *a; ElementType *b){
  ElementType t = *a; *a = *b; *b = t;
}
void PercDown(ElementType A[], int p, int N){
  int Parent, Child;
  ElementType X;
  X = A[p];
  for(Parent=p; (Parent*2+1)<N; Parent=Child){
    Child = Parent*2 +1;
    if( (Child!= N-1) && (A[Child] < A[Child+1]))
      Child++;
    if(X >= A[Child]) break;
    else A[Parent] = A[Child];
  }
  A[Parent] = X;
}
void Heap_Sort (ElementType A[], int N){
	for(int i = N/2; i>=0; i--){
    PercDown(A, i, N) // 向下过滤，建最大堆
  }
  for(int i = N-1; i>0; i--){
    Swap(&A[0], &A[i]); // DeleteMax, A[0]是最大的元素
    PercDown(A, 0, i); // 剩下元素继续调整成最大堆， 0为根节点，i为当前最大堆元素个数
  }
}
```

定理：堆排序处理N个不同元素的随机排列的平均比较次数是：2NlogN - O(N log logN)

虽然堆排序给出最佳平均时间复 杂度，但实际效果不如用 **Sedgewick**增量序列的希尔排序。



## 归并排序

核心：有序子列的归并

```c
// L=左边起始位置 R=右边起始位置 RightEnd=右边终点位置
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd){
  int LeftEnd, NumElements, Tmp;
  LeftEnd = R -1; // 左边终点位置，前提左右两边挨着
  Tmp = L; // 存放结果的数组的初始位置
  NumElements = RightEnd - L + 1;
  while(L <= LeftEnd && R <= RightEnd){
    if(A[L] <= A[R]) TmpA[Tmp++] = A[L++]
    else TmpA[Tmp++] = A[R++]
    while(L <= LeftEnd){ // 直接复制左边剩下的
      TmpA[Tmp++] = A[L++]
    }
    while(R <= RightEnd){ // 复制右边剩下的
      TmpA[Tmp++] = A[R++]
    }
    for(int i = 0; i < NumElements; i++, RightEnd--)
      A[RightEnd] = TmpA[RightEnd]
  }
}
```

递归实现(稳定)：T(N) = O(N logN)

```c
void Msort(Element A[], ElementType TmpA[], int L, int RightEnd){
  int Center;
  if(L < RightEnd){
    Center = (L+RightEnd)/2;
    Msort(A, TmpA, L, Center);
    Msort(A, TmpA, Center+1, RightEnd);
    Merge(A, TmpA, L, Center+1, RightEnd);
  }
}
void MergeSort(ElementType A[], int N){
  ElementType *TmpA;
  TmpA = (ElementType *)malloc(N*sizeof(ElementType));
  if(TmpA != NULL){
    Msort(A, TmpA, 0, N-1);
    free(TmpA);
  }
  else printf("空间不足");
}
```

非递归(循环)实现：

```c
// length = 当前有序子列的长度
void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length){
  // 两两归并相邻有序子列
  int i, j;
  for(i = 0; i <= N-2*lengh; i+= 2*length)
    Merge(A, TmpA, i, i+length, i+ 2*length-1);
  if(i+length < N) // 归并最后两个子列
    Merge(A, TmpA, i, i+length, N-1);
  else // 最后只剩1个子列
    for(j=1; j<N; j++) TmpA[j] = A[j];
}
void Merge_Sort(ElementType A[], int N){
  int length;
  ElementType *TmpA;
  
  length = 1; // 初始化子序列长度
  TmpA = malloc(N * sizeof(ElementType));
  if( TmpA != NULL){
    while(length < N){
      Merge_pass(A, TmpA, N, length);
      length *= 2;
      Merge_pass(TmpA, A, N, length);
    }
    free(TmpA);
  }
  else printf("空间不足");
}
```



## 快速排序

快速排序思想是：分而治之；最好情况下(每次正好中分) T(N) = O(NlogN)

伪码描述：

```c
void Quicksort(ElementType A[], int N){
	if(N < 2) return;
	pivot = 从A[]中选一个主元
	将S = {A[] \ pivot} 分成2个独立子集
    A1 = {a∈S | a <= pivot} 和
    A2 = {a∈S | a >= pivot}
	A[] = Quicksort(A1, N1) ∪ {pivot} ∪ Quicksort(A2, N2)
}
```

快速排序快的主要原因是：主元被选中后，在子集划分完成后，被一次性放到正确的位置上，一直再也不会移动；

子集划分中，如果有元素正好等于pivot，最坏情况下(元素全部相等)，停下来交换的时间复杂度是T(N）= O(NlogN)

而如果不理它，继续移动指针的复杂度是T(N) = O(N^2)

快速排序的**问题**：

因为快速排序是用递归实现的，会占用额外的系统堆栈的空间，每一次调用系统堆栈的时候，会有很多的进栈， 递归调用结束的时候会弹出来，会耗时；对小规模的数据，可能还不如插入排序快；

解决方案：

当递归的数据规模充分小(定义一个Cutoff的阀值)，停止递归，直接调用简单排序（如插入排序）；

```c
// 快速排序，直接调用库排序
#include <stdio.h>
// 简单整数排序
int compare(const void* a, const void* b) {
  // 比较两整数，非降序排序
  return (*(int*)a - *(int*)b);
}
// 调用接口
qsort(A, N, sizeof(int), compare);

// 对结构体Node中的某键值排序
struct Node {
  int key1, key2;
} A[MAXN];
int compare2keys(const void* a, const void* b) {
  // 比较两种键值，按key1非升序排列；如果key1相等，则按key2非降序排列
  int k;
  if (((const struct Node*)a)->key1 < ((const struct Node*)b)->key1) {
    k = 1;
  } else if (((const struct Node*)a)->key1 > ((const struct Node*)b)->key1) {
    k = -1;
  } else {  // 如果key1相等
    if (((const struct Node*)a)->key2 < ((const struct Node*)b)->key2) {
      k = -1;
    } else {
      k = 1;
    }
    return k;
  }
}
```

快速排序，C语言实现

```c
// 快速排序
ElementType Median3(ElementType A[], int Left, int Right) {
  int Center = (Left + Right) / 2;
  if (A[Left] > A[Center]) {
    Swap(&A[Left], &A[Center]);
  }
  if (A[Left] > A[Right]) {
    Swap(&A[Left], A[Right]);
  }
  if (A[Center] > A[Right]) {
    Swap(A[Center], A[Right]);
  }
  // 此时A[Left] <= A[Center] <= A[Right]
  Swap(&A[Center], &A[Right - 1]);  // 将基准Pivot藏到右边
  // 只需要考虑A[Left+1] - A[Right-2]
  return A[Right - 1];  // 返回基准Pivot
}
void Qsort(ElementType A[], int Left, int Right) {
  // 核心递归函数
  int Piovt, Cutoff, Low, High;
  if (Cutoff <= Right - Left) { // 如果元素充分多，进入快排
    Piovt = Median3(A, Left, Right); // 选基准
    Low = Left;
    High = Right;
    while (1) { // 将序列中比基准小的移到基准左边，大的移到右边
      while (A[++Low] < Pivot);
      while (A[--High] > Pivot);
    }
    if (Low < High) {
      Swap(&A[Low], &A[High]);
    } else {
      break;
    }
    Swap(&A[Low], &A[Right - 1]); // 将基准换到正确位置
    Qsort(A, Left, Low - 1); // 递归解决左边
    Qsort(A, Low + 1, Right); // 递归解决右边
  } else {
    InsertionSort(ElementType A[], int N); // 元素太少时，用简单排序
  }
}
void QuickSort(ElementType A[], int N) {
  // 统一接口
  Qsort(A, 0, N - 1);
}
```



## 表排序

排序过程中不需要移动原始数据，移动的只是指向原始数据位置的指针；这种不移动元素本身，而只移动指针的排序方法叫：**间接排序**；

定义一个指针数组作为**“表”**（table）

如果要进行物理排序，可以根据原理：**N个数字的排列有若干个独立的环组成**；判断环的结束：每访问一个空位i后，就令table[i]=i。当发现table[i]==i时，环就结束了。

复杂度分析：

- 最好情况：初始有序
- 最坏情况：有N/2个环，每个环包含2个元素，则需要3N/2次元素移动

T = O(mN), 是每个元素的负责时间。



## 基数排序

**桶排序（Bucket sort）**或所谓的**箱排序**，是一个排序算法，工作的原理是将数组分到有限数量的桶里。每个桶再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序）

假设我们有 **N** 个学生，他们的成绩是**0**到**100**之间 的整数(于是有 **M** **= 101** 个不同的成绩值)。如 何在线性时间内将学生按成绩排序?

```c
void Bucket_Sort(ElementType A[], int N) { 
	count[]初始化;
	while (读入1个学生成绩grade) 
		将该生插入count[grade]链表;
	for ( i=0; i<M; i++ ) { 
		if ( count[i] ){
			输出整个count[i]链表
		}
	}
```

当M很小时，时间复杂度是线性的 T(N,M) = O(M+N)；

假设我们有 **N** **= 10** 个整数，每个整数的值在**0**到 **999**之间(于是有 **M** **= 1000** 个不同的值)。即M >> N，此时再用堆排序就不合适了；

**基数排序**（英语：Radix sort）是一种非比较型[整数](https://zh.wikipedia.org/wiki/整数)[排序算法](https://zh.wikipedia.org/wiki/排序算法)，其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基数排序也不是只能使用于整数。

它是这样实现的：将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后，数列就变成一个有序序列。

基数排序的方式可以采用次位优先LSD（Least significant digital）或主位优先MSD（Most significant digital），LSD的排序方式由键值的最右边开始，而MSD则相反，由键值的最左边开始。

![示例](https://lh3.googleusercontent.com/proxy/vpabvcutHBa2olypWFYS-KAjeHKUXMGnO-R70mkrxMSWlBh0bpm69u3102oLyWfl3Zlx5WgCZOUwNC4Zjtsc1AbK629KKOli5Zn4Oph2PENHBw9zBKtXfysTJkM5fbBZQHivlsE)

时间复杂度为：**T=O(P(N+B))** P为数字位数，B为每位数有几个不同的数字(桶的个数)；假设我们有 **N** **= 20** 个整数，每个整数的值在**0**到 **999**之间；则使用基数排序的事件复杂度为：T=O(3*(20+10))



基数排序-次位优先算法

```c
* 基数排序 - 次位优先 */

/* 假设元素最多有MaxDigit个关键字，基数全是同样的Radix */
#define MaxDigit 4
#define Radix 10

/* 桶元素结点 */
typedef struct Node* PtrToNode;
struct Node {
  int key;
  PtrToNode next;
};

/* 桶头结点 */
struct HeadNode {
  PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];

int GetDigit(int X, int D) { /* 默认次位D=1, 主位D<=MaxDigit */
  int d, i;

  for (i = 1; i <= D; i++) {
    d = X % Radix;
    X /= Radix;
  }
  return d;
}

void LSDRadixSort(ElementType A[], int N) { /* 基数排序 - 次位优先 */
  int D, Di, i;
  Bucket B;
  PtrToNode tmp, p, List = NULL;

  for (i = 0; i < Radix; i++) /* 初始化每个桶为空链表 */
    B[i].head = B[i].tail = NULL;
  for (i = 0; i < N; i++) { /* 将原始序列逆序存入初始链表List */
    tmp = (PtrToNode)malloc(sizeof(struct Node));
    tmp->key = A[i];
    tmp->next = List;
    List = tmp;
  }
  /* 下面开始排序 */
  for (D = 1; D <= MaxDigit; D++) { /* 对数据的每一位循环处理 */
    /* 下面是分配的过程 */
    p = List;
    while (p) {
      Di = GetDigit(p->key, D); /* 获得当前元素的当前位数字 */
      /* 从List中摘除 */
      tmp = p;
      p = p->next;
      /* 插入B[Di]号桶尾 */
      tmp->next = NULL;
      if (B[Di].head == NULL)
        B[Di].head = B[Di].tail = tmp;
      else {
        B[Di].tail->next = tmp;
        B[Di].tail = tmp;
      }
    }
    /* 下面是收集的过程 */
    List = NULL;
    for (Di = Radix - 1; Di >= 0; Di--) { /* 将每个桶的元素顺序收集入List */
      if (B[Di].head) {                   /* 如果桶不为空 */
        /* 整桶插入List表头 */
        B[Di].tail->next = List;
        List = B[Di].head;
        B[Di].head = B[Di].tail = NULL; /* 清空桶 */
      }
    }
  }
  /* 将List倒入A[]并释放空间 */
  for (i = 0; i < N; i++) {
    tmp = List;
    List = List->next;
    A[i] = tmp->key;
    free(tmp);
  }
}
```



基数排序-主位优先

```c
/* 基数排序 - 主位优先 */
 
/* 假设元素最多有MaxDigit个关键字，基数全是同样的Radix */
 
#define MaxDigit 4
#define Radix 10
 
/* 桶元素结点 */
typedef struct Node *PtrToNode;
struct Node{
    int key;
    PtrToNode next;
};
 
/* 桶头结点 */
struct HeadNode {
    PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];
  
int GetDigit ( int X, int D ){ /* 默认次位D=1, 主位D<=MaxDigit */
    int d, i;
     
    for (i=1; i<=D; i++) {
        d = X%Radix;
        X /= Radix;
    }
    return d;
}
 
void MSD( ElementType A[], int L, int R, int D ){ /* 核心递归函数: 对A[L]...A[R]的第D位数进行排序 */
     int Di, i, j;
     Bucket B;
     PtrToNode tmp, p, List = NULL; 
     if (D==0) return; /* 递归终止条件 */
      
     for (i=0; i<Radix; i++) /* 初始化每个桶为空链表 */
         B[i].head = B[i].tail = NULL;
     for (i=L; i<=R; i++) { /* 将原始序列逆序存入初始链表List */
         tmp = (PtrToNode)malloc(sizeof(struct Node));
         tmp->key = A[i];
         tmp->next = List;
         List = tmp;
     }
     /* 下面是分配的过程 */
     p = List;
     while (p) {
         Di = GetDigit(p->key, D); /* 获得当前元素的当前位数字 */
         /* 从List中摘除 */
         tmp = p; p = p->next;
         /* 插入B[Di]号桶 */
         if (B[Di].head == NULL) B[Di].tail = tmp;
         tmp->next = B[Di].head;
         B[Di].head = tmp;
     }
     /* 下面是收集的过程 */
     i = j = L; /* i, j记录当前要处理的A[]的左右端下标 */
     for (Di=0; Di<Radix; Di++) { /* 对于每个桶 */
         if (B[Di].head) { /* 将非空的桶整桶倒入A[], 递归排序 */
             p = B[Di].head;
             while (p) {
                 tmp = p;
                 p = p->next;
                 A[j++] = tmp->key;
                 free(tmp);
             }
             /* 递归对该桶数据排序, 位数减1 */
             MSD(A, i, j-1, D-1);
             i = j; /* 为下一个桶对应的A[]左端 */
         } 
     } 
}
 
void MSDRadixSort( ElementType A[], int N ){ /* 统一接口 */
    MSD(A, 0, N-1, MaxDigit); 
}
```



## 排序算法的比较

#### 时间复杂度

| 排序算法     | 平均时间复杂度         | 最坏时间复杂度 | 额外空间复杂度 | 稳定性 |
| ------------ | ---------------------- | -------------- | -------------- | ------ |
| 简单选择排序 | O(N^2)                 | O(N^2)         | O(1)           | 不稳定 |
| 冒泡排序     | O(N^2)                 | O(N^2)         | O(1)           | 稳定   |
| 直接插入排序 | O(N^2)                 | O(N^2)         | O(1)           | 稳定   |
| 希尔排序     | O(N^d)(跟增量序列有关) | O(N^2)         | O(1)           | 不稳定 |
| 堆排序       | O(NlogN)               | O(NlogN)       | O(1)           | 不稳定 |
| 快速排序     | O(NlogN)               | O(N^2)         | O(logN)        | 不稳定 |
| 归并排序     | O(NlogN)               | O(NlogN)       | O(N)           | 稳定   |
| 基数排序     | O(P(N+B))              | O(P(N+B))      | O(N+B)         | 稳定   |



#### 空间复杂度

1. 直接插入、直接选择、冒泡、希尔和堆排序算法需要的辅助空间为O(1).
2. 快速排序算法需要辅助空间为O(long2N)，最坏情况需求O(n).
3. 归并排序O(N).
4. 基数排序O(N+rd).