---
layout: post
title: 『数据结构学习笔记』
categories: Blog
description: 数据结构
keywords: 数据结构, Notes
---

[中国大学MOOC(慕课) 数据结构(浙江大学)](https://www.icourse163.org/learn/ZJU-93001?tid=1450069451#/learn/announce)

### 0、指针、结构体相关内容

**[C 语言的指针支持]**

1. 函数的地址调用
2. 动态分配内存
3. 数组的地址引用

```c
# include<stdio.h>

int main()
{
    int x, *p;
    x = 55;
    p = &x;
    printf ("%d %u\n", x, *p); // 55 55
    *p = 65;
    printf ("%d %u\n", x, *p); // 65 65
    return 0;
}
```

- 指针必须指向对象后，才能引用;
- & 和 * 为互补运算;

**[五种算数运算]**

```c
p1 ++; // 含义指向 a 后的整型单元
p1 --; // 指向 a 前的整型单元
p1 + n; // 指向 a 后的 n 个整型单元
p1 - n; // 指向 a 前的 n 个整型单元
p2 - p1; // a 和 b 之间差的单元数
p ± n; // p 的实际内容 ±n sizeof(*p);
```

**[指针与数组]**

数组是同类型的变量的集合，各元素按下标的特定顺序占据一段连续的内存，各元素的地址也连续，指针对数组元素非常方便。

通过指针引用数组元素可以分以下三个步骤：

1. 说明指针和数组：`int *p, a[10]`
2. 指针指向数组：`p = a; p = &a[0];`(指向数组的首地址)
3. 过指针引用数组元素：当指针指向数组的首地址时，则下标为 i 的元素地址为`p + i` 或 `a + i`

**[引用数组元素可以有三种方法]**

1. 下标法：`a[i]`
2. 指针法：`*(p+i)`
3. 数组名法：`*(a+i)`

「 注」数组名是常量地址，不能改变！~~a = p~~

**[C语言的动态分配函数(stdlib.h) ]**

- malloc(m): 开辟 m 字节长度的地址空间，并返回这段空间的首地址
- sizeof(x): 计算变量 x 的长度
- free(p): 释放指针 p 所指变量的存储空间，即彻底删除一个变量

**[C++的动态存储分配]**

1. new  类型名 T (初值列表)

   - 功能：申请用于存放T类型对象的内存空间，并依初值列表赋以初值
   - 结果值：
     - 成功：T类型的指针，指向新分配的内存
     - 失败：0 (NULL)

   ```c++
   int *p1 = new int;
   int *p1 = new int(10);
   
   delete p1;
   ```

2. delete 指针 P

   - 功能：释放指针P所指向的内存。P必须是new操作的返回值

   ```c++
   int *p1 = new int[10];
   
   delete []p1;
   ```

**[C++中的参数传递]**

函数调用时传送给形参表的实参必须与形参在类型、个数、顺序上保持一致

参数传递有两种方式

1. 传值方式：参数为整型、实型、字符型等
2. 传地址：参数为指针变量、引用类型、数组名

**「传值方式」**把实参的值传送给函数局部工作区相应的副本中，函数使用这个副本执行必要的功能。函数修改的是副本的值，实参的值不变

```c++
# include<iostream>
using namespace std;

void swap (float m, float n)
{
    float temp;
    temp = m;
    m = n;
    n = temp;
}

int main()
{
    float a, b;
    cin >> a >> b; // 1 2
    swap(a, b);
    cout << a << ' ' << b << endl; // 1 2
    return 0;
}
```

**「传地址方式」**指针变量作参数：形参变化影响实参

```c++
# include<iostream>
using namespace std;

void swap (float *m, float *n)
{
    float temp;
    temp = *m;
    *m = *n;
    *n = temp;
}

int main()
{
    float a, b;
    float *p1, *p2;
    cin >> a >> b; // 1 2
    p1 = &a; p2 = &b;
    swap(p1, p2);
    cout << a << ' ' << b << endl; // 2 1
    return 0;
}
```

**「传地址方式」**引用类型作参数：

```c++
# include<iostream>
using namespace std;

int main()
{
    int i = 5;
    int& j = i; // j 是一个引用类型，代表 i 的一个替代名
    i = 7; // i值改变时，j 值也跟着改变
    cout << "i = " << i << " j = " << j << endl; // i= 7 j = 7
    return 0;
}
```

```c++
# include<iostream>
using namespace std;

void swap(float& m,float& n)
{
    float temp;
    temp=m;
    m=n;
    n=temp;
}

int main()
{
    float a, b;
    cin >> a >> b; // 1 2
    swap(a, b);
    cout << a << ' ' << b << endl; // 2 1
}
```

**「引用类型作形参的三点说明」**

1. 传递引用给函数与传递指针的效果是一样的，形参变化实参也发生变化
2. 引用类型作形参，在内存中并没有产生实参的副本，它 直接对实参操作；而一般变量作参数，形参与实参就占用不同的存储单元，所以形参变量的值是实参变量的副本。因此，当参数传递的数据量较大时，用引用比用一般变量传递参数的时间和空间效率都好
3. 指针参数虽然也能达到与使用引用的效果，但在被调函数中需要重复使用 `*` 指针变量名”的形式进行运算，这很容易产生错误且程序的阅读性较差；另一方面，在主调函数的调用点处，必须用变量的地址作为实参

**[传地址方式]** 数组名作参数：传递的是数组的首地址，对形参数组所做的任何改变都将反映到实参数组中

```c++
# include<iostream>
using namespace std;

void sub(char a[]);

int main()
{
    char a[10] = "hello";
    sub(a);
    cout << a << endl;
    return 0;
}

void sub(char b[])
{
    b[] = "world";
}
```

**「问」**用数组作函数的参数，求10个整数的最大数

```c++
# include<iostream>
using namespace std;
# define N 10

int max(int a[]);

int main()
{
    int a[10];
    int m;
    for (int i = 0; i < N; i++) {
      cin >> a[i];
    } // 1 2 3 4 5 6 7 8 9 10
    m = max(a);
    cout << "The max number is:" << m << endl; // The max number is:10
}

int max(int b[]) {
  int n = b[0];
  for(int i = 1; i < N; i++) {
    if(n < b[i]) n = b[i];
  }
  return n;
}
```

**「练习」**用数组作为函数的参数，将数组中 n 个整数按相反的顺序存放，要求输入和输出在主函数中完成

```c++
# include<iostream>
using namespace std;
# define N 10
void sub(int b[]) {
    int temp;
    int flag = N - 1;
    for (int i = 0; i < N/2; i++) {
        temp = b[i];
        b[i] = b[i+flag];
        b[i+flag] = temp;
        flag -= 2;
    }
    return;
}
int main()
{
    int a[10];
   	for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    sub(a);
    for (int i = 0; i < N; i++) {
      cout << a[i] << ' ';
    }
    cout << endl;
    return 0;
}
```

**[结构体]**

在数据中，经常有一些既有联系，类型又不同的数据，它们又需要一起处理。C 语言允许用户按自己的需要将不同的基本类型构造成一种特殊类型，即结构。

```c
struct 结构体名 { // struct：结构标志
    type 成员 1;
    type 成员 2;
    ...
    type 成员 n; // 结构类型中所含的成员项及其类型
};
```

结构的定义确定了两点：

1. 定义结构类型，确定结构中的成员项的名称及类型。
2. 指明该结构类型的变量在内存中的**组织形式**

```c
struct Book {
    char no[15];
    char name[50];
    float price;
};
Book b[10];

typedef struct {
    char no[15];   
    char name[50]; 
    float price;   
} Book; 
Book b[10];
```

**[结构指针]**

```c
typedef struct LNode {
    ElemType data; // 数据余
    struct LNode *next; // 指针域
} LNode, *LinkList;
// *LinkList 为 Lnide 类型的指针

// 方式一：(*p).成员项名
// 方式二：p->成员项名
// LNode *p <---> LinkList P
```

### 1、序言

#### 1.1.1、关于空间使用

写一个程序实现一个函数 PrintN，似地传入一个正整数为 N 的参数后，能顺序打印从 1 到 N 全部正整数。

- **循环实现( 占用空间小)**

  ```C
  void PrintN(int n)
  {
      fro (int i =1; i <= n; i++) {
          cout << i << ' ';
      }
      return 0;
  }
  ```

- **递归实现(占用空间大)**

  ```C
  void PrintN(int n)
  {
      if (n){
          Print(n - 1);
          cout << n << ' ';
      }
      return 0;
  }
  ```

#### 1.1.2、关于算法效率

写程序计算给定多项式在给定点 x 处的值：
$$
f(x) =a_0 + a_1x + ... + a_{n-1}x^{n-1} + a_nx^n
$$

- **一般算法(效率低)**

  ```C
  double f(int n, double a[], double x) {
      double p = a[0];
      for (int i = 1; i <= n; i++) {
          p += (a[i] * pow(x, i));
      }
      return p;
  }
  ```

- **秦九韶算法(效率高)**
  $$
  f(x) = a_0 + x(a_1 + x(...(a_{n-1} + x(a_n))...))
  $$

  ```C
  double f (int n, double a[], double x) {
      double p = a[n];
      for (int i = n; i > 0; i--) {
          p = a[i -1 ] + x * p;
      }
      return p;
  }
  ```

- **clock():**捕捉从程序开始运行到 clock() 被调用时所耗费的时间。单位是 clock tick，即“时钟打点”

  常数 CLK_TCK：机器时钟每秒所走的时钟打点数。

  ```C
  # include <stdio.h>
  # include <time.h>
  
  clock_t start, stop;
  double duration;
  int main()
  {
      start = clock();
      MyFunction();
      stop = clock();
      duration = (double(stop - start)) / CLK_TCK;
      return 0;
  }
  ```

#### 1.1.3、抽象数据类型

- 数据类型
  - 数据对象集
  - 数据集合相关联的操作集

- 抽象：描述数据类型的方法不依赖于具体实现

  - 与存放数据的机器无关
  - 与数据存储的物理结构无关
  - 与实现操作的算法和编程语言均无关

  只描述数据对象集和相关操作集“是什么”，并不涉及“如何做到”的问题。

- 举例：

  - **类型名称：**矩阵(Matrix)
  - **数据对象集：**一个 MxN 的矩阵![image](/images/blog/数据结构/Matrix.png)由MxN个三元组 <a, i, j> 构成，其中 a 是矩阵元素的值，i 是元素所在的行号，j 是元素所在的列号。
  - **操作集：**对于任意矩阵 A、B、C 属于 Matrix，以及整数 i、j、k、M、N
    - Matrix Creat(int M, int N)：返回一个 MxN 的空矩阵;
    - int GetMaxRow(Matrix A)：返回矩阵 A 的总行数;
    - ElementType GetEntry(Matrix A, int i, int j): 返回矩阵 A 的第 i 行、第 j 列的元素;
    - Matrix Add(Matrix A, Matrux B): 如果 A 和 B 的行、列数一致，则返回矩阵 C = A + B，否则返回错误标志;
    - Matrix Multiply(Matrix A, Matrix B): 如果 A 的列数等于 B 夫人行数，则返回矩阵 C = AB，否则返回错误标志;
    - ......

#### 1.2.1、算法(Algorithm)

- 一个有限指令集
- 接受一些输入（有些情况下不需要输入）
- 产生输出
- 一定在有限步骤之后停止
- 每一条指令必须：
  - 有明确的目标，不可以有歧义
  - 计算机能处理的范围内
  - 描述应不以来于任何一门计算机语言以及具体的实现手段

**举例：选择排序算法的伪代码描述**

```C
void SelectionSort(int List[], int N) {
    /*将 N 个List[0]...List[N-1] 进行非递减排序*/
    for(i = 0; i < N; i++) {
        MinPosition = ScanForMin(List, i, N-1);
        /*从 List[i] 到 List[N-1] 中找最小元，并将其位置赋给 MinPosition*/
        Swap(List[i], List[MinPosition]);
        /*将未排序的部分的最小元换到有序部分的最后位置*/
    }
}
```

- 空间复杂度S(n)：根据算法写成的程序在执行时**占用储存元的长度**。
- 时间复杂度T(n)：根据算法写成的程序在执行时**耗费时间的长度**。

举例1：

```C
void PrintN(int N) {
    if(N) {
        Print(N - 1);
        print("%d\n", N);
    }
}
```

举例2：

```C
double f(int n, double a[], double x) {
    double p = a[0];
    for (int i = 1; i <= n; i++) {
        p += (a[i] * pow(x, i));
    }
    return p;
}

double f (int n, double a[], double x) {
    double p = a[n];
    for (int i = n; i > 0; i--) {
        p = a[i -1 ] + x * p;
    }
    return p;
}
```

#### 1.2.1、应用实例

**最大子列和问题：**
$$
给定 N 个着呢个书的序列 {A1, A2, ..., An}，求函数f(i, j)=max(0, \sum_{k=i}^jA_k)的最大值：
$$

- 算法1：

  ```C
  int MaxSubseqSum(int A[], int N) {
      int ThisSum, MaxSum = 0;
      int i, j, k;
      for(i = 0; i < N; i++) { // i 是子列左端位置
          for(j = i; j < N; j++) { // j是子列右端位置
              ThisSum = 0; // ThisSum 是从 A[i] 到 A[j] 的子列和
              for(k = i; k <= j; k++)
                  ThisSum += A[k];
             	if(ThisSum > MaxSum) // if True
                  MaxSum = ThisSum;// 更新结果
          }
      }
      return MaxSum;
  }
  ```

  $$
  复杂度：T(N)=O(N^3)
  $$

- 算法2：

  ```c
  int MaxSubseqSum(int A[], int N) {
      int ThisSum, MaxSum = 0;
      int i, j;
      for(i = 0; i < N; i++) { // i 是子列左端位置
          ThisSum = 0; // ThisSum 是从 A[i] 到 A[j] 的子列和
          for(j = i; j < N; j++) { // j是子列右端位置
              ThisSum += A[j];
          if(ThisSum > MaxSum) // if True
              MaxSum = ThisSum; // 更新结果
          }
      }
      return MaxSum;
  }
  ```

  
  $$
  复杂度：T(N)=O(N^2)
  $$

- 算法3：分治

  ![image](/images/blog/数据结构/分治.png)

  ```c
  static int Find_Max_Crossing_SubArray(int * nums, int start, int mid, int end) {
      int left = -65533, right = -65533;
      int sum;
      int i, j;
  
      sum = 0;
      for(i = mid; i >= start; i--) {
          sum += *(nums + i);
          if(sum > left) {
              left = sum;
          }
      }
  
      sum = 0;
      for(j = mid + 1; j < end; j++) {
          sum += *(nums + j);
          if(sum > right) {
              right = sum;
          }
      }
  
      return left + right;
  }
  
  int Find_Maximum_Subarray(int * nums, int start, int end) {
      int left;
      int right;
      int cross;
      int mid;
  
      if(start == end)
          return * nums;
      else
      {
          mid = (start + end)/2;
          left = Find_Maximum_Subarray(nums, start, mid);
          right = Find_Maximum_Subarray(nums, mid + 1, end);
          cross = Find_Max_Crossing_SubArray(nums, start, mid, end);
           
          if(left >= right && left >= cross)
              return left;
          else if(right >= left && right >= cross)
              return right;
          else
              return cross;
      }
  }
  
  int main()
  {
      int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7}, * nums = arr;
      int val;
  
      val = Find_Maximum_Subarray(nums, 0, sizeof(arr)/sizeof(int));
      printf("MaxSubarraySum = %d.\n", val);
      return 0;
  }
  ```

  $$
  复杂度：T(N)=O(NlogN)
  $$

- 算法4：在线处理

  ```C
  int MaxSubSum(int A[], int N) {
      int ThisSum, MaxSum, i;
      ThisSum = MaxSum = 0;
      for(i = 0; i < N; i++) {
          ThisSum += A[i]; //每次循环则累加
          if(ThisSum > MaxSum) //每次循环，如果成立则MaxSum的值就会变为ThisSum
              MaxSum = ThisSum;
          else if(ThisSum < 0) //每次循环，如果成立则ThisSum重新置为0
              ThisSum = 0;
      }
      return MaxSum;
  }
  ```

  $$
  复杂度：T(N)=O(N)
  $$

### 2、线性结构

#### 2.1.1、多项式表示

**[例]：一元多项式及其计算**

**一元多项式**:![image](/images/blog/数据结构/fx.png)

**主要运算**：多项式相加、相减、相乘等

**[分析]：如何表示多项式**

- 关键数据：
  - 多项式项数 n
  - 各项系数![image](/images/blog/数据结构/ai.png)及指数 i

- 表示方法：

  - **方法1：顺序存储结构直接表示(虽然方便，但是空间浪费)**

    ![image](/images/blog/数据结构/2.1.1_1.png)

  - **方法2：顺序储存结构表示非零项**

    ![image](/images/blog/数据结构/2.1.1_2.png)

    ![image](/images/blog/数据结构/2.1.1_3.png)

  - **方法3：链表结构存储非零项**

    ![image](/images/blog/数据结构/2.1.1_4.png)

**[启示]：**

1. 同一个问题可以有不同的表示（存储）方法
2. 有一类共性问题：有序线性序列的组织和管理

#### 2.1.2、线性表

**“线性表(Linear List)”**：由同类型**数据元素**构成**有序序列**的线性结构

1. 表中元素个数称为线性表的**长度**
2. 线性表没有元素时，称为**空表**
3. 表的起始位置称为**表头**，结束位置称为**表尾**

**[线性表的抽象数据类型描述]**

- **类型名称：**线性表（List）
- **数据对象集：**线性表是 n(>=0) 个元素构成的有序序列 (a1, a2, ..., an)
- **操作集：**线性表 L 属于 List，整数 i 表示位置，元素 X 属于 ElementType，线性表基本操作主要有：
  1. List MarkEmpty()：初始化一个空线性表 L;
  2. ElementType FindKth(int K, List L)：根据位序 K，返回相应元素;
  3. int Find(ElementType X, List L)：在线性表 L 中查找 X 的第一次出现位置;
  4. void insert(ElementType X, int i, List L)：在位序 i 前插入一个新元素 X;
  5. void Delete(int i, List L)：删除指定位序 i 的元素;
  6. int Length(List L)：返回线性表 L 的长度素 n;

**[线性表的顺序存储实现]**

利用数组的**连续存储空间顺序存放**线性表的各元素

![image](/images/blog/数据结构/2.1.2_1.png)

注：数组：Data	最后一个元素位置：Last

**「主要操作实现」**

1. 初始化（建立空的顺序表）

   ```c
   list MakeEmpty () {
       List PtrL;
       PtrL = (List)malloc(sizeof(struct LNode));
       PtrL->List = -1;
       return PtrL;
   }
   ```

2. 查找

   ```c
   int Find (ElementType X, List PtrL) {
       int i = 0;
       while (i <= PtrL->List && PtrL->Data[i] != X)
           i ++;
       if (i > PtrL->List) return -1; // 没找到返回 -1
       else return i; // 找到返回存储的位置 i
   }
   ```

3. 插入（第 i (1 <= i <= n+1) 个位置上插入一个值为 X 的新元素）

   ![image](/images/blog/数据结构/2.1.2_2.png)

   ```c
   void Insert (ElementType X, int i, List PtrL) {
       int j;
       if (PtrL->Last == MAXSIZ-1) { // 表空间已满，不能插入
           printf("表满");
           return;
       }
       if (i < 1 || i > PtrL->List+2) { // 检查插入位置的合法性
           printf("位置不合法");
           return;
       }
       for (j = PtrL > Last; j >= i-1; j--) {
           PtrL->Data[j+1] = PtrL->Data[j];
       } // 将 ai ～ an 倒序向后移动
       PtrL->Data[i-1] = X; // 插入 X
       PtrL->Last++; // Last 仍指向最后元素
       return;
   }
   ```

4. 删除（删除表的第 i (1 <= i <= n+1) 个位置上的元素 ）

   ![imag](/images/blog/数据结构/2.1.2_3.png)

   ```c
   void Delete (int i, List PtrL) {
       int j;
       if (i < 1 || i > PtrL->Last+1) {
           printf("不存在第%d个元素", i);
           return;
       }
       for (j = i; j <= PtrL->Last; j++) { // 检查插入位置的合法性
           PtrL->Data[j-1] = PtrL->Data[j];
       }// 将 ai ～ an 顺序向前移动
       PtrL->Last--; // Last 仍指向最后元素
       return;
   }
   ```

#### 2.1.3、广义表

**「例」二元多项式该如何表示？比如，给定二元多项式：**
$$
P(x,y)=9x^{13}y^2+4x^{12}+15x^8y^3-x^8y+3x^2
$$
**「分析」**可将上述二元多项式看成关于 x 的一元多项式：
$$
P(x,y)=(9y^2+4)x^{12}+(15y^3-y)x^8+3x^2
$$

$$
\implies ax^{12}+bx^8+cx^2
$$

所以，上述二元多项式可以用**“复杂”链表**表示为：

  ![image](/images/blog/数据结构/2.1.3_1.png)

**广义表(Generalized List)**

1. 广义表是**线性表的推广**;
2. 对于线性表而言，n 个元素都是基本的**单元素**;
3. 广义表中，这些元素不仅可以是单元素也可以是**另一个广义表**;

```c
typedef struct GNode *GList;
struct GNode [
    int Tag; // 标志域：0 表示结点是单元素，1 表示结点是广义表
    union { // 联合，子表指针域 Sublist 与单元素数据域 Data 复用，即共用储存空间
        ElementType Data;
        GList SubList;
    } URegion;
    GList Next; // 指向后继结点
];
```

![image](/images/blog/数据结构/2.1.3_2.png)

#### 2.1.4、多重链表

**多重链表：**链表中的节点可能同时隶属于多个链

1. 多重链表中结点的**指针域会有多个**，如前面例子包含了 Next 和 SubList 两个指针域;
2. 但包含两个指针域的链表并不一定是多重链表，比如在**双向链表不是多重链表**;

3.  多重链表有广泛的用途：基本上如**数、图**这样相对复杂的数据结构都**可以采用多重链表**方式实现存储;

**「例」矩阵可以用二维数组表示，但二维数组表示有两个缺陷：**

1. 一是数组的**大小需要事先确定**;
2. 对于**“稀疏矩阵”**，将造成大量的**存储空间浪费**;

![image](/images/blog/数据结构/2.1.3_3.png)

**「分析」采用一种典型的多重链表——十字链表来存储稀疏矩阵**

- **只存储矩阵非 0 元素项**

  结点的数据域：行坐标 Row、列坐标 Col、数值 Value

- **每个结点通过两个指针域，吧同行、同列串起来;**

  - 行指针(向  右指针) Right
  - 列指针(向下指针) Down

![image](/images/blog/数据结构/2.1.3_4.png)

- 左上角 Term 结点：稀疏矩阵的入口结点，可以了解到矩阵的有关信息：矩阵有 4 行 5 列，非零项有 7 项;

- 图中间的 Term 结点：两个指针分别指向同一行和同一列，同一行同一列都设计为循环链表，每个 Term 既属于同一行，也属于同一列，称为十字链表;
- Head 结点：做为行链表和列链表的头结点;

用一个表示域 Tag 来区分头结点和非 0 元素的结点;

头结点的表示为“Head”，矩阵非 0  元素结点的标识值wei“Term”;

![image](/images/blog/数据结构/2.1.3_5.png)

#### 2.2.1、堆栈

**[什么是堆栈]**

计算机如何进行表达式求值？

「例」算数表达式 5+6/2-3×4，正确理解：
$$
5+6/2-3*4=5+3-3*4=8-3*4=8-12=-4
$$

- 由两类对象构成的：
  1. 运算数：2、3、4
  2. 运算符号：+、-、*、/
- 不同运算符号优先级不一样

**[后缀表达式]**

- 中缀表达式：运算符号位于两个运算数之间：`a + b * c - d / e`

- 后缀表达式：运算符号位于两个运算数之后：`a b c * + d e / -`

  **「例」6 2 / 3 - 4 2 * + = ?**

  ```
  6 2 / 3 - 4 2 * +
  -->	 3 3 - 4 2 * +
  -->  0 4 2 * +
  -->  0 8 +
  -->  8
  ```

  后缀表达式求值策略：从左向右”扫描“，逐个处理运算数和操作符号

**[堆栈的抽象数据类型描述]**

堆栈(Stack)：具有一定操作约束的线性表，只在一端(栈顶，Top)做**插入、删除**

- 插入数据：入栈(Push)
- 删除数据：出栈(Pop)
- 后入先出：Last In First Out

**类型名称：**堆栈(Stack)

**数据对相集：**一个有 0 个或者多个元素的有穷线性表

**操作集：**长度为 MaxSize 的堆栈 S 属于 Stark，堆栈元素 itrm 属于 ElementType

1. Stack CreateStack (int MaxSize)：生成空堆栈，其最大长度为 MaxSize;
2. int IsFull (Stack S, int MaxSize)：判断堆栈 S 是否已满;
3. void Push (Stack S, ElementType item)：将元素 item 压入堆栈;
4. int IsEmply (Stack S)：判断堆栈 S 是否为空;
5. ElementType Pop (Stack S)：删除并返回栈顶元素;

![image](/images/blog/数据结构/2.2.1_1.png)

Push 和 Pop 可以穿插交替进行：

按照操作系列

1.  Push(S, A), Push(S, B), Push(S, C), Pop(S), Pop(S), Pop(S) 堆栈输出的是C B A;

2.  Push(S, A), Pop(S), Push(S, B), Push(S, C), Pop(S), Pop(S) 堆栈输出的是A C B;

 #### 2.2.2、栈的顺序存储实现

栈的顺序存储结构通常又一个一维数组可一个记录栈顶元素位置的变量组成。

```c
# define MaxSize <存储数据元素的最大个数>
typedef struct SNode *Stack;
struct SNode {
    ElementType Data[MaxSize];
    int Top;
};
```

**(1) 入栈**

```c
void Push (Stack PtrS, ElementType item) {
    if (PtrS->Top == MaxSize-1) {
        printf("堆栈满");
        return;
    } else {
        PtrS->Data[++(PtrS->Top)] = item;
        return;
    }
}
```

 **(2)出栈**

```c
ElementType Pop (Stack PtrtS) {
    if (PtrS->Top == -1) {
        printf("堆栈空");
        return ERROR; // ERROR shi Elementtype 的特殊值，标志错误
    } else {
        return (PtrS->Data[(PtrS->Top)--]);
    }
}
```

**「例」**请用一个数组实现两个堆栈，要求最大地利用数组空间，使数组只要有空间入栈操作就可以成功。

**[分析]** 一种比较聪明的方法是使这两个栈分别从数组的**两个开始向中间生长**; 当两个栈的**栈顶指针相遇**时，表示两个栈都满了。

```c
# define MaxSize <存储数据元素的最大个数>
struct DStack {
    ElementType Data[MaxSize];
    int Top1; // 堆栈 1 的栈顶指针
    int Top2; // 堆栈 2 的栈顶指针
} S;
S.Top1 = -1;
S.Top2 = MaxSize;
```

```c
void Push (struct DStack *PtrS, ElementType item, int Tag) {
    // Tag 作为区分两个堆栈的标志，取值为 1 和 2
    if (PtrS->Top2 - PtrS->Top1 == 1) { // 堆栈满条件
        printf("堆栈满");
        return;
    } 
    if (Tag == 1) {
        PtrS->Data[++(PtrS->Top1)] = item;
    } else {
        PrtS->Data[--(PtrS-?Top2)] = item;
    }
}
```

```c
ElementType Pop (struct DStack *PtrS, int Tag) {
    // Tag 作为区分两个堆栈的标志，取值为 1 和 2
    if (Tag == 1) {
        if (PtrS->Top1 == -1) {
            printf("堆栈 1 空");
            return;
        } else
            return Ptrs->Data[(PtrS->Top1)--];
    } else {
        if (PtrS->Top2 == MaxSize) {
            printf("堆栈 2 空");
            return;
        } else
            return Ptrs->Data[(PtrS->Top2)++];
    }
}
```

#### 2.2.3、堆栈的链式存储结构

栈的链式存储结构实际上就是一个**单链表**，叫**链栈**。插入和删除操作只能在链栈的栈顶进行。

**「问」**栈顶指针 Top 应该在链表的那一头？

**「答」**Top  一定是在链表的头上，如果放在尾上则不能实现删除的操作。

```c
typedef struct SNode * Stack;
struct SNode {
    ElementType Data;
    struct SNode *Next;
};
```

```c
Stack CreateStack() {
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
} // 堆栈初始化(建立空栈)

int IsEmpty(Stack S) {
    return (S->Next -- NULL);
} // 判断堆栈 S 是否为空
```

```c
void Push (ElementType item, Stack S) {
    struct SNode *TmpCell;
    TmpCell = (struct SNode *)malloc(sizeof(styct Snode));
    TmpCell->Element = item;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
}
```

```c
ElementTypre Pop(Stack S) {
    struct SNode *FistCell;
    ElementType TopElem;
    if (IsEmpty(S)) {
        printf("堆栈空");
        return NULL;
    } else {
        FirstCell =S->Next;
        S->Next = FirstCell->Next;
        TopElem = FirstCell->Element;
        free(FirstCell);
        return TopElem;
    }
}
```

#### 2.2.4、堆栈应用：表达式求值

之前应用堆栈实现后缀表达式求值的基本过程，从左到右读入后缀表达式的各项(运算符或运算数)：

1. 运算数：入栈;
2. 运算符：从堆栈中弹出适当数量的运算数，计算并将结果入栈;
3. 最后，堆栈顶上的元素就是表达式的结果值;

**[中缀表达式求值]**

**基本策略：**将中缀表达式转换为后缀表达式，然后求值

**「问」**如何将中缀表达式转换为后缀表达式？

**「例」**`2 + 9 / 3 - 5 = 2 9 3 / + 5 -`

1. 运算数相对顺序不变
2. 运算符号顺序发生改变
   - 需要存储”等待中“的运算符号
   - 要将当前运算符号与”等待中“的子后一个运算符号比较

**「问」**有括号怎么办？

**「例」**`a * (b + c) / d = a b c + * d /`

1. 运算数相对顺序不变
2. 运算符号顺序发生改变
   - 遇到`(`压入堆栈
   - 遇到`)`将栈顶的运算符弹出并输出，知道遇到` (`(出栈，不输出)

**[总结] 中缀表达式如何转换为后缀表达式**

从头到尾读取**中缀表达式的每个对象**，对不同对象按不同的情况处理。

1. **运算数**：直接输出
2. **左括号**：压入堆栈
3. **右括号**：将**栈顶的运算符弹出**并**输出**，**直到遇到左括号**(出栈，不输出)
4. **运算符**：
   - 若优先级大于栈顶运算符时，把它压栈;
   - 若**优先级小于等于栈顶运算符**时，将**栈顶运算符弹出并输出**; 再比较信的栈顶运算符，直到该运算符大于栈顶运算符优先级为止，然后将该**运算符压栈**;
5. 若各对象**处理完毕**，则把堆栈中存留的运算符**一并输出**

中缀转后缀示例：`2 * (9 + 6 / 3 - 5) + 4`

| 步骤 |      待处理表达式       | 堆栈状态(底<—>顶) |       输出状态        |
| :--: | :---------------------: | :---------------: | :-------------------: |
|  1   | 2 * (9 + 6 / 3 - 5) + 4 |                   |                       |
|  2   |  * (9 + 6 / 3 - 5) + 4  |                   |           2           |
|  3   |   (9 + 6 / 3 - 5) + 4   |         *         |           2           |
|  4   |   9 + 6 / 3 - 5) + 4    |        * (        |           2           |
|  5   |    + 6 / 3 - 5) + 4     |        * (        |          2 9          |
|  6   |     6 / 3 - 5) + 4      |       * ( +       |          2 9          |
|  7   |      / 3 - 5) + 4       |       * ( +       |         2 9 6         |
|  8   |       3 - 5) + 4        |      * ( + /      |         2 9 6         |
|  9   |        - 5) + 4         |      * ( + /      |        2 9 6 3        |
|  10  |         5) + 4          |       * ( -       |      2 9 6 3 / +      |
|  11  |          ) + 4          |       * ( -       |     2 9 6 3 / + 5     |
|  12  |           + 4           |         *         |    2 9 6 3 / + 5 -    |
|  13  |            4            |         +         |   2 9 6 3 / + 5 - *   |
|  14  |                         |         +         |  2 9 6 3 / + 5 - * 4  |
|  15  |                         |                   | 2 9 6 3 / + 5 - * 4 + |

**[实现代码]**[https://github.com/ZhWing/zhwing.github.io/blob/master/Code/Data_Structure/Stack.cpp](https://github.com/ZhWing/zhwing.github.io/blob/master/Code/Data_Structure/stack.cpp)

```c++
#include <bits/stdc++.h>
using namespace std;

// 判断优先级
int fl (char str) {
    int tmp;
    switch (str) {
        // case '(': tmp = 0; break;
        case '+': tmp = 1; break;
        case '-': tmp = 1; break;
        case '*': tmp = 2; break;
        case '/': tmp = 2; break;
    }
    return tmp;
}

int main()
{
    stack<char> s;
    string str; // = "2*(9+6/3-5)+4";
    cin >> str;
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')) {
            cout << str[i] << ' ';
        } else if (str[i] == '+' || str[i]== '-' || str[i] == '*' || str[i] == '/') {
            while (true) {
                if (s.empty() || s.top() == '(') {
                    s.push(str[i]);
                    break;
                } else if (fl(str[i]) > fl(s.top())) {
                    s.push(str[i]);
                    break;
                } 
                else {
                    // while (fl(str[i]) <= fl(s.top())) {
                    //     cout << s.top() << ' ';
                    //     s.pop();
                    // }
                    cout << s.top() << ' ';
                    s.pop();
                    // s.push(str[i]);
                }
            }

        } else if (str[i] == '(') {
            s.push(str[i]);
        } else if (str[i] == ')') {
            while (s.top() != '(') {
                cout << s.top() << ' ';
                s.pop();
            }
            s.pop();
        }
    }
    while (!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }
    cout << endl;
    return 0;
}
```



**[堆栈的其他应用]**

- 函数调用及递归实现
- 深度优先搜索
- 回溯算法
- ......