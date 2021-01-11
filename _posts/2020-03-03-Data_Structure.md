---
layout: post
title: 数据结构学习笔记
categories: 数据结构学习笔记
author: ZhW
header-style: text
mathjax: true
tags: 
    - 数据结构
    - Notes
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

**「传值方式」** 把实参的值传送给函数局部工作区相应的副本中，函数使用这个副本执行必要的功能。函数修改的是副本的值，实参的值不变

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

**「传地址方式」** 指针变量作参数：形参变化影响实参

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

**「传地址方式」** 引用类型作参数：

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

**「问」** 用数组作函数的参数，求10个整数的最大数

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

**「练习」** 用数组作为函数的参数，将数组中 n 个整数按相反的顺序存放，要求输入和输出在主函数中完成

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

- **clock():** 捕捉从程序开始运行到 clock() 被调用时所耗费的时间。单位是 clock tick，即“时钟打点”

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

  - **类型名称：** 矩阵(Matrix)
  - **数据对象集：** 一个 MxN 的矩阵![image](/img/blog/数据结构/Matrix.png)由MxN个三元组 <a, i, j> 构成，其中 a 是矩阵元素的值，i 是元素所在的行号，j 是元素所在的列号。
  - **操作集：** 对于任意矩阵 A、B、C 属于 Matrix，以及整数 i、j、k、M、N
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

  ![image](/img/blog/数据结构/分治.png)

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

**一元多项式**:![image](/img/blog/数据结构/fx.png)

**主要运算**：多项式相加、相减、相乘等

**[分析]：如何表示多项式**

- 关键数据：
  - 多项式项数 n
  - 各项系数![image](/img/blog/数据结构/ai.png)及指数 i

- 表示方法：

  - **方法1：顺序存储结构直接表示(虽然方便，但是空间浪费)**

    ![image](/img/blog/数据结构/2.1.1_1.png)

  - **方法2：顺序储存结构表示非零项**

    ![image](/img/blog/数据结构/2.1.1_2.png)

    ![image](/img/blog/数据结构/2.1.1_3.png)

  - **方法3：链表结构存储非零项**

    ![image](/img/blog/数据结构/2.1.1_4.png)

**[启示]：**

1. 同一个问题可以有不同的表示（存储）方法
2. 有一类共性问题：有序线性序列的组织和管理

#### 2.1.2、线性表

**“线性表(Linear List)”**：由同类型**数据元素**构成**有序序列**的线性结构

1. 表中元素个数称为线性表的**长度**
2. 线性表没有元素时，称为**空表**
3. 表的起始位置称为**表头**，结束位置称为**表尾**

**[线性表的抽象数据类型描述]**

- **类型名称：** 线性表（List）
- **数据对象集：** 线性表是 n(>=0) 个元素构成的有序序列 (a1, a2, ..., an)
- **操作集：** 线性表 L 属于 List，整数 i 表示位置，元素 X 属于 ElementType，线性表基本操作主要有：
  1. List MarkEmpty()：初始化一个空线性表 L;
  2. ElementType FindKth(int K, List L)：根据位序 K，返回相应元素;
  3. int Find(ElementType X, List L)：在线性表 L 中查找 X 的第一次出现位置;
  4. void insert(ElementType X, int i, List L)：在位序 i 前插入一个新元素 X;
  5. void Delete(int i, List L)：删除指定位序 i 的元素;
  6. int Length(List L)：返回线性表 L 的长度素 n;

**[线性表的顺序存储实现]**

利用数组的**连续存储空间顺序存放**线性表的各元素

![image](/img/blog/数据结构/2.1.2_1.png)

注：数组：Data    最后一个元素位置：Last

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

   ![image](/img/blog/数据结构/2.1.2_2.png)

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

   ![imag](/img/blog/数据结构/2.1.2_3.png)

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

**「分析」** 可将上述二元多项式看成关于 x 的一元多项式：

$$
P(x,y)=(9y^2+4)x^{12}+(15y^3-y)x^8+3x^2
$$

$$
\implies ax^{12}+bx^8+cx^2
$$

所以，上述二元多项式可以用**“复杂”链表**表示为：

  ![image](/img/blog/数据结构/2.1.3_1.png)

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

![image](/img/blog/数据结构/2.1.3_2.png)

#### 2.1.4、多重链表

**多重链表：** 链表中的节点可能同时隶属于多个链

1. 多重链表中结点的**指针域会有多个**，如前面例子包含了 Next 和 SubList 两个指针域;
2. 但包含两个指针域的链表并不一定是多重链表，比如在**双向链表不是多重链表**;

3.  多重链表有广泛的用途：基本上如**数、图**这样相对复杂的数据结构都**可以采用多重链表**方式实现存储;

**「例」矩阵可以用二维数组表示，但二维数组表示有两个缺陷：**

1. 一是数组的**大小需要事先确定**;
2. 对于“稀疏矩阵”，将造成大量的 **存储空间浪费**;

![image](/img/blog/数据结构/2.1.3_3.png)

**「分析」采用一种典型的多重链表——十字链表来存储稀疏矩阵**

- **只存储矩阵非 0 元素项**

  结点的数据域：行坐标 Row、列坐标 Col、数值 Value

- **每个结点通过两个指针域，吧同行、同列串起来;**

  - 行指针(向  右指针) Right
  - 列指针(向下指针) Down

![image](/img/blog/数据结构/2.1.3_4.png)

- 左上角 Term 结点：稀疏矩阵的入口结点，可以了解到矩阵的有关信息：矩阵有 4 行 5 列，非零项有 7 项;

- 图中间的 Term 结点：两个指针分别指向同一行和同一列，同一行同一列都设计为循环链表，每个 Term 既属于同一行，也属于同一列，称为十字链表;
- Head 结点：做为行链表和列链表的头结点;

用一个表示域 Tag 来区分头结点和非 0 元素的结点;

头结点的表示为“Head”，矩阵非 0  元素结点的标识值wei“Term”;

![image](/img/blog/数据结构/2.1.3_5.png)

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
  -->     3 3 - 4 2 * +
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

**类型名称：** 堆栈(Stack)

**数据对相集：** 一个有 0 个或者多个元素的有穷线性表

**操作集：** 长度为 MaxSize 的堆栈 S 属于 Stark，堆栈元素 itrm 属于 ElementType

1. Stack CreateStack (int MaxSize)：生成空堆栈，其最大长度为 MaxSize;
2. int IsFull (Stack S, int MaxSize)：判断堆栈 S 是否已满;
3. void Push (Stack S, ElementType item)：将元素 item 压入堆栈;
4. int IsEmply (Stack S)：判断堆栈 S 是否为空;
5. ElementType Pop (Stack S)：删除并返回栈顶元素;

![image](/img/blog/数据结构/2.2.1_1.png)

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

**「例」** 请用一个数组实现两个堆栈，要求最大地利用数组空间，使数组只要有空间入栈操作就可以成功。

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

**「问」** 栈顶指针 Top 应该在链表的那一头？

**「答」** Top  一定是在链表的头上，如果放在尾上则不能实现删除的操作。

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

**基本策略：** 将中缀表达式转换为后缀表达式，然后求值

**「问」** 如何将中缀表达式转换为后缀表达式？

**「例」** `2 + 9 / 3 - 5 = 2 9 3 / + 5 -`

1. 运算数相对顺序不变
2. 运算符号顺序发生改变
   - 需要存储”等待中“的运算符号
   - 要将当前运算符号与”等待中“的子后一个运算符号比较

**「问」** 有括号怎么办？

**「例」** `a * (b + c) / d = a b c + * d /`

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

**[实现代码]**

[https://github.com/ZhWing/zhwing.github.io/blob/master/Code/Data_Structure/Stack.cpp](https://github.com/ZhWing/zhwing.github.io/blob/master/Code/Data_Structure/Stack.cpp)

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

#### 2.3.1、队列及顺序结构存储实现

队列(Queue)：具有一定操作约束的线性表

插入和删除操作：只能在一段插入，在另一端删除;

- 数据插入：入队列(AddQ)
- 数据删除：出队列(DeleteQ)

先进先出：FIFO

**[队列的抽象数据类型描述]**

类型名称：队列(Queue)

数据对象集：一个有 0 个或者多个元素的有穷线性表

操作集：长度 MaxSize 的队列 Q 属于 Queue，队列元素 item 属于 ElementType

1. Queue CreatQueue(int MaxSize)：生成长度为 MaxSize 的空队列;
2. int IsFullQ(Queue Q, int MaxSize)：判断队列 Q 是否已满;
3. void AddQ(Queue Q, ElementType item)：将数据元素 item 插入队列 Q 中;
4. int IsEmptyQ(Queue Q)：判断队列 Q 是否为空;
5. ElementType DeleteQ(Queue Q)：将队头元素从队列中删除并返回;

**[队列的顺序存储实现]**( 循环队列)

顺序结构存储通常由一个**一维数组**和一个记录队列头元素的变量 front 以及一个记录队尾元素的变量 rear 组成。

```c
#define MaxSize < 存储数据元素的最大个数>

struct QNode {
    ElementType Data[MaxSize];
    int rear;
    int front;
};
typedef struct QNode *Queue;
```

**[入队列]**

```c
void AddQ(Queue PtrQ, Elementtype item) {
    if ((PtrQ->rear+1) % MaxSize == PtrQ->front) {
        printf("队列满");
        return;
    }
    PtrQ->rear=(PtrQ->rear+1) % MaxSize;
    PtrQ->Data[PtrtQ->rear] = item;
}
```

**[出队列]**

```c
ElementType DeleteQ(Queue PtrQ) {
    if (PtrQ->front == PtrQ->rear) {
        printf("队列空");
        return ERROR
    } else {
        PtrQ->front = (PtrQ->front+1) % MaxSize;
        return PtrQ->Data[PtrQ->front];
    }
}
```

#### 2.3.2、队列的链式存储实现

链式存储结构也可以用一个单链表实现。插入和删除操作分别在链表的两头进行。

```c
struct Node {
    ElementType Data;
    struct Node *Next;
};
struct QNode {
    struct Node *rear; // 指向队尾节点
    struct Node *front; // 指向队头节点
};
typedef struct QNode *Queue;
Queue PtrQ;
```

![image](/img/blog/数据结构/2.3.2_1.png)

**[入队列]**

```c
void AddQ(Queue PtrQ, Elementtype item) {
    if ((PtrQ->rear+1) % MaxSize == PtrQ->front) {
        printf("队列满");
        return;
    }
    struct Node *RearCell = (Node*)malloc(sizeof(Node));
    RearCell->Data = item;
    RearCell->Next = NULL;
    PtrQ->rear->Next = RearCell;
    PtrQ->rear = RearCell;
}
```

**[出队列]**(不带头节点的链式队列)

```c
ElementType DeleteQ(Queue PtrQ) {
    struct Node *FrontCell;
    ElementType FrontElem;
    if (PtrQ->front == NULL) {
        print("队列空");
        return ERROR;
    }
    FrontCell = PtrQ->front;
    if (PtrQ->front = PtrQ->rear) {
        PtrQ->front = PtrQ->rear = NULL:
    } else {
        PtrQ->front = PtrQ->rear->Data;
    }
    FrontElem = FrontCell->Data;
    free (FrontCell);
    return FrontElem;
}
```

#### 2.4、多项式的加减运算实现

![image](/img/blog/数据结构/2.4_1.png)

主要思路：相同指数的项系数相加，其余部分进行拷贝。

**「实现」**

采用不带头结点的单向链表，按照指数递减的顺序排列各项。

![image](/img/blog/数据结构/2.4_2.png)

```c
struct PloyNode {
    int coef; // 系数
    int expon; // 指数
    struct PloyNode *link; // 指向下一个节点的指针
};
typedef struct PolyNode *Ploynomial;
Polynomial P1, P2;
```

**算法思路：** 两个指针 P1 和 P2 分别指向两个多项式第一个结点，不断循环：

- P1->expon == P2->expon：系数相加。若结果不为 0,则作为结果多项式对应项的系数。同时，P1 和 P2 都分别指向下一项;
- P1->expon > P2->expon：将 P1 的当前项存入结果多项式，并使 P1 指向下一项;
- P1->expon < P2->expon：将 P2 的当前项存入结果多项式，并使 P2 指向下一项;

- 当某一多项式处理完时，将另一个多项式的所有结点依次复制到结果多项式中去。

```c
void Attach(int c, int e, Polynomial *pRear) {
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P;
    *pRear = P;
}

Polynomial PolyAdd(Polynomial P1, Polynomial P2) {
    Polynomial front, rear, temp;
    int sum;
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    front = rear;
    while (P1 && P2) {
        switch (Compare(P1->expon, P2->expon)) {
            case 1:
                Attach(P1->coef, P1->expon, &rear);
                P1 = P1->link;
                break;
            case -1:
                Attach(P2->coef, P2->expon, &rear);
                P2 = P2->link;
                break;
            case 0:
                sum = P1->coef = P2->coef;
                if (sum) Attach(sum, P1->expon, &rear);
                P1 = P1->link;
                P2 = P2->link;
                break;
        }
    }
    // 将未处理完的另一个多项式所有节点依次复制到结果多项式中去
    for (; P1; P1 = P1->link) Attach(P1->coef, P1->expon, &rear);
    for (; P2, P2 = P2->link) Attach(P2->coef, P2->expon, &rear);
    rear->link = NULL;
    temp = front;
    front = front->link; // 让 front 指向多项式的第一个非零项
    free(temp);
    return front;
}
```

### 3、树 (Tree)

#### 3.1、树的定义

**树的定义**：n(n >= 0) 个结点构成的有限集合

当 n= 0 时，称为空树

对于任意棵非空树(n > 0)，它具备一下性质：

1. 树中有一个称为“根(root)”的特殊结点，用 r 表示；
2. 其余结点可分为 m (m > 0) 个互不相交的有限集T1, T2, ..., Tm，其中每个集合本身又是一棵树，称为原来树的“子树 (SubTree)”

**树与非树：**

- 子树是不相交的
- 除了子根结点外，每个结点有且仅有一个父结点
- 一颗 N 个结点的树有 N-1 条边

#### 3.2、树的一些基础术语

- **节点的度(Degree)**：结点的子树个数
- **树的度**：树的所有结点中最大的度
- **叶结点(Leaf)**：度为 0 的结点
- **父结点(Parent)**：有子树的结点时其他子树的根结点的父结点
- **子结点(Child)**：若 A 结点是 B 结点的父结点，则称 B 结点是 A 结点的子结点；子结点也称为孩子节点
- **兄弟结点(Sibling)**：具有同一父结点的各结点彼此是兄弟结点
- **路径和路径的长度**：从结点 n1 到 nk 的路径为一个结点序列 n1, n2, ... , nk, ni，是 n(i+1) 的父结点。路径所包含边的个数为路径的长度
- **祖先结点(Ancestor)**：沿树根到某一结点路径的所有结点都是这个结点的祖先结点
- **子孙结点(Descendant)**：某一结点的子树中所有的结点时这个结点的子孙
- **结点的层次(Level)**：规定根结点在 1 层，其它任一结点的层数时其父结点的层数加 1
- **树的深度(Depth)**：树中所有结点中最大层次的时这个这棵树的深度

#### 3.3、树的表示

- 儿子兄弟表示法

- 旋转45° -> 二叉树

#### 3.4、二叉树

- 二叉树的定义

  **二叉树 T**：一个有穷的结点集合

  这个集合可以为空

  若不为空，则它是由根结点和称为其左子树 TL 和右子树 TR 的两个不相交的二叉树组成。

- 二叉树具有五种基本形态
  1. 为空
  2. 只有一个根结点
  3. 有一个根结点和一个左子树
  4. 有一个根结点和一个右子树
  5. 有一个根结点和一个左子树和一个右子树
- 二叉树的子树有左右顺序之分
- 特殊二叉树
  1. 斜二叉树(Skewed Binary Tree)
  2. 完美二叉树(Perfect Binary Tree)[满二叉树(Full Binary Tree)]
  3. 完全二叉树(Complete Binary Tree)：从 n 个结点的二叉树，对树中结点按从上至下、从左到右顺序进行编号，编号为 i (1 <= i <= n) 结点与满二叉树中编号为 i 结点在二叉树中位置相同

- 二叉树的几个重要性质
  1. 一个二叉树第 i 层的最大结点数为：2^(i-1), i >=1
  2. 深度为 k 的二叉树有最大结点数为：2^k-1, k>=1
  3. 对任何非空二叉树 T，若 n0 表示叶结点的个数、n2是度为 2 的非叶结点个数，那么两者满足关系n0 = n2 + 1


#### 3.5、二叉树的抽象数据类型定义

- **类型名称**：二叉树

- **数据对象集**：一个有穷的结点集合

  若不为空，则由根结点和其左、右二叉子树组成

- **操作集**：BT ∈ BinTree, Item ∈ ElementType，重要操作有：

  1. Boolean IsEmpty(BinTree BT)：判别 BT 是否为空
  2. void Traversal(BinTree BT)：遍历，按某顺序访问每个结点
  3. BinTree CreatBinTree()：创建一个二叉树

- **常用的遍历方法**：

  - void PreOrderTraversal(BinTree BT)：先序 --> 根、左子树、右子树
  - void InOrderTraversal(BinTree BT)：中序 --> 左子树、根、右子树
  - void PostOrderTraversal(BinTree BT)：后序 --> 左子树、右子树、根
  - void LevelOrderTraversal(BinTree BT)：层次遍历，从上到下、从左到右

#### 3.6、二叉树的存储结构

- 顺序存储结构

  **完全二叉树**：按从上到下、从左到右顺序存储 n 个结点的完全二叉树的结点父子关系:

  ![image-20201109165349888](/img/blog/tree/image-20201109165349888.png)

  | 结点 |  A   |  B   |  O   |  C   |  S   |  M   |  Q   |  W   |  K   |
  | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
  | 序号 |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |

  1. 非根结点的父结点的序号是 i / 2
  2. 结点的左孩子的序号是 2i (若 2i <= n，否则没有左孩子)
  3. 结点的右孩子的序号是 2i + 1 (若 2i + 1 <= n，否则没有右孩子)

  **一般二叉树**也可以采用这种结构，但是会造成空间浪费

  ![image-20201109170742034](/img/blog/tree/image-20201109170742034.png)

- 链表存储

  ```c
  typedef struct TreeNode *BinTree;
  typedef BinTree Position;
  struct TreeNode {
      ElementType data;
      BinTree Left;
      BinTree Right;
  };
  ```

  ![image-20201109171327944](/img/blog/tree/image-20201109171327944.png)

#### 3.7、二叉树的遍历

1. 先序遍历:

   遍历过程：

   1. 访问根结点

     2. 先序遍历其左子树
     3. 先序遍历其右子树

   ```c++
   void PreOrderTraversal(BinTree BT) {
       if (BT) {
           cout << BT->data << " ";
           PreOrderTraversal(BT->left);
           PreOrderTraversal(BT->right);
       }
   }
   ```

2. 中序遍历

   遍历过程：

   1. 中序遍历其左子树
   2. 访问根结点
   3. 中序遍历其右子树

   ```c++
   void InOrderTraversal(BinTree BT) {
       if (BT) {
           PreOrderTraversal(BT->left);
           cout << BT->data << " ";
           PreOrderTraversal(BT->right);
       }
   }
   ```

3. 后续遍历

   遍历过程：

   1. 后序遍历其左子树
   2. 后序遍历其右子树
   3. 访问根结点

   ```c++
   void PostOrderTraversal(BinTree BT) {
       if (BT) {
           PreOrderTraversal(BT->left);
           PreOrderTraversal(BT->right);
           cout << BT->data << " ";
       }  
   }
   ```

4. 层序遍历

   二叉树遍历的核心问题：**二维结构的线性化**

   --> 从结点访问其左、右儿子结点

   --> 访问左儿子后，右儿子结点怎么办？

   - 需要一个存储结构保存暂时不访问的结点
   - 存储结构：堆栈、队列

   **队列实现**：遍历从根结点开始。首先讲根结点入队，然后开始执行循环：结点出队、访问该节点、其左右儿子入队

   ```c++
   void LevelOrderTraversal(BinTree BT) {
       Queue Q; BinTree T;
       if (!BT) return; // 若是空树直接返回
       Q = CreatQueue(MaxSize); // 创建并初始化队列 Q
       AddQ(Q, BT);
       while (!IsEmptyQ(Q)) {
           T = DeleteQ(Q);
           cout << T->data << " "; // 访问取出队列的结点
           if (T->left) AddQ(Q, T->left);
           if (T->right) AddQ(Q, T->right);
       }
   }
   ```


- 示例

  1. **【例】** 遍历二叉树的应用：输出二叉树的叶子结点

     ```c++
     void PreOrderTraversal(BinTree BT) {
         if (BT) {
             if (!BT->left && !BT->right)
                 cout << BT->data << " ";
             PreOrderTraversal(BT->left);
             PreOrderTraversal(BT->right);
         }
     }
     ```

  2. **【例】** 求二叉树的高度

     ```c++
     int PostOrderTraversal(BinTree BT) {
         int HL, HR, MaxH;
         if (BT) {
             HL = PreOrderTraversal(BT->left); // 求左子树的深度
             HR = PreOrderTraversal(BT->right); // 求右子树的深度
             MaxH = (HL > HR) ? HL : HR;
             return (MaxH + 1);
         } else {
             return 0;
         }
     }
     ```

  3. **【例】** 二元运算表达式树及其遍历

     ![image-20201110181430313](/img/blog/tree/image-20201110181430313.png)

     三种遍历可以得到三种不同的访问结果：

     1. 先序遍历得到前缀表达式：`+ + a * b c * + * d e f g`
     2. 中序遍历得到中缀表达式：`a + b * c + d * e + f * g` (中缀表达式会受到**运算符优先级**的影响)
     3. 后序遍历得到后缀表达式：`a b c * + d e * f + g * +`

  4. **【例】** 由两种遍历序列确定二叉树

     **必须要有一个是中序遍历才行**

     **【例】** 先序和中序遍历序列来确定一颗二叉树

     - 根据先序遍历序列第一个结点确定根结点
     - 根据根结点在中序遍历序列中分割出左右两个子序列
     - 对左子树和右子树分别递归使用相同的方法继续分解

  5. **【例】** 树的同构问题

     给定两棵树 T1 和 T2。如果 T1 可以通过若干次左右孩子互换就变成 T2，则我们称两棵树是“同构”的。

     输入格式：输入两棵树的信息：

     - 现在先在一行中给出该树的结点数，随后 N 行
     - 第 i 行对应编号第 i 个结点，给出该节点中存储的字母、其左孩子结点的编号、右孩子结点的编号
     - 如果孩子结点为空，则在相应位置上给出”-“

     ```
     8
     A 1 2
     B 3 4
     C 5 -
     D - -
     E 6 -
     G 7 -
     F - -
     H - -
     8
     G - 4
     B 7 6
     F - -
     A 5 1
     H - -
     C 0 -
     D - -
     E 2 -
     ```

     **【二叉树表示】**

     结构数组表示二叉树：静态链表

     ![image-20201111160708909](/img/blog/tree/image-20201111160708909.png)

     | 存储内容 | A    | B    | C    | D    |
     | -------- | ---- | ---- | ---- | ---- |
     | left     | -1   | 2    | -1   | -1   |
     | right    | 1    | 3    | -1   | -1   |
     | 下标     | 0    | 1    | 2    | 3    |

     ```c++
     #define MaxTree 10
     #define ElementType char
     #define Tree int
     #define Null -1
     
     struct TreeNode {
         ElementType Element;
         Tree left;
         Tree right;
     } T1[MaxTree], T2[MaxTree];
     ```

     **【程序框架搭建】**

     ```c++
     int main() {
         Tree R1, R2;
         R1 = BuildTree(T1);
         R2 = BuildTree(T2);
         if (Isomorphic(R1, R2)) cout << "Yes" << endl;
         else cout << "No" << endl;
         return 0;
     }
     
     Tree BuildTree(struct TreeNode T[]) {
              int i, check[MaxSize] = {0};
              char cl, cr;
              cin >> N;
              if(N) {
                  for (i = 0; i < N; i++) chech[i] = 0;
                  for (i = 0; i < N; i++) {
                      cin >> T[i].Element >> cl >> cr;
                      if (cl != '-') {
                          T[i].left = cl - '0';
                          check[T[i].left] = 1;
                      } else {
                          T[i].left = Null;
                      }
                      if (cr != '-') {
                      T[i].right = cr - '0';
                      check[T[i].right] = 1;
                  } else {
                      T[i].right = Null;
                  }
              }
              for (i = 0; i < N; i++)
                  if (!check[i]) break;
              Root = i;
          }
          return Root;
      }
      
      int Isomorphic (Tree R1, Tree R2) {
          if ((R1 == R2) && (R2 == Null)) return 1;
          if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null))) return 0;
          if (T1[R1].Element != T2[R2].Element) return 0;
          if ((T1[R1].left == Null) && (T2[R2].left == Null))
              return Isomorphic(T1[R1].right, T2[R2].right);
          
          if (((T1[R1].left != Null) && (T2[R2].left != Null)) && ((T1[T1[R1].left].Element) == (T2[T2[R2].left].Element)))
              return (Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right));
          else 
              return (Isomorphic(T1[R1].left, T2[R2].right) && Isomorphic(T1[R1].right, T2[R2].left));
      }
     ```

#### 3.8、二叉搜索树 (BST, Binary Search Tree)

一颗二叉树，可以为空；如果不为空，满足一下==以下性质：

1. 非空**左子树**的所有**键值小于其根结点**的键值
2. 非空**右子树**的所有**键值大于其根结点**的键值
3. **左、右子树都是二叉搜索树**

**二叉搜索树操作的特别函数：**

- `Position Find(ElementType X, BinTree BST)`：从二叉搜索树 BST 中查找元素 X，返回其所在结点的地址；
- `Position FindMin(BinTree BST)`：从二叉搜索树 BST 中查找并返回最小元素所在的结点地址；
- `Position FindMax(BinTree BST)`：从二叉搜索树 BST 中查找并返回最大元素所在的结点地址；
- `BinTree Insert(ElementType X, BinTree BST)`
- `BinTree Delete(ElementType X, BinTree BST)`

**二叉搜索树的查找操作：**

- 查找从根结点开始，如果树为空，返回NULL

- 若搜索树非空，则根结点关键字和 X 进行比较，并进行不同处理：

  1. 若 X 小于根结点键值，只需要在左子树中继续搜索；
  2. 若 X 大于根结点键值，在右子树中进行继续搜索；
  3. 若两者比较结果相等，搜索完成，返回指向此节点的指针；

  ```c++
  Position Find(ElementType X, BinTree BST) {
      if (!BST) // 查找失败
          return NULL;
      if (X > BST->data) 
          return Find(X, BST->right); // 在左子树继续查找
      else if (X < BST->data) 
          return Find(X, BST->left); // 在右子树继续查找
      else 
          return BST; // 查找成功，返回结点的地址
  }
  ```

  ```c++
  Position Find(ElementType X, BinTree BST) {
      while (BST) {
          if (X > BST->data)
              BST = BST->right;
          else if (X < BST->data)
              BST = BST->left;
          else
              return BST;
      }
      return NULL;
  }
  ```

- 查找最大值和最小值

  - 最大元素一点是在树的最右分枝的端结点上
  - 最小元素一定是在树的最左分枝的端结点上

  ```c++
  Position FindMin(BinTree BST) {
      if (!BST)
          return NULL;
      else if (!BST->left)
          return BST;
      else
          return FindMin(BST->left);
  }
  ```

  ```c++
  Position FindMax(BinTree BST) {
      if (BST)
          while (BST-right) BST = BST->right;
      return BST;
  }
  ```

**二叉搜索树的插入**

关键是要找到元素应该插入的位置，可采用与 Find 类似的方法

```c++
BinTree Insert(ElementType X, BinTree BST) {
    if (!BST) {
        BST = malloc(sizeof(struct TreeNode));
        BST->data = X;
        BST->left = BST->right = NULL;
    } else {
        if (X < BST->data)
            BST->left = Insert(X, BST->left);
        else if (X > BST->dats)
            BST->right = Insert(X, BST->right);
    }
    return BST;
}
```

**二叉搜索树的删除**

三种情况：

1. 要删除的是叶结点：直接删除，并再修改其父结点指针 -> 置为 NULL

2. 要删除的结点只有一个孩子结点：将其父亲结点的指针指向要删除的系欸但那的孩子结点

3. 要删除的结点有左、右两颗子树：

   用另一结点代替被删除结点：**右子树的最小元素**或者**左子树的最大元素**

```c++
BinTree Delete (ElementType X, BinTree BST) {
    Position Tmp;
    if (!BST) cout << "要删除的元素找不到" << endl;
    else if (X < BST->data) // 左子树递归删除
        BST->left = Delete(X, BST->left);
    else if (X > BST->data) // 右子树递归删除
        BST->right = Delete(X, BST->right);
    else { // 找到要删除的结点
        if (BST->left && BST->right) { // 被删除结点有左右两个子结点
            Tmp = FindMin(BST->right); // 在右子树中找最小的元素填充删除的结点
            BST->data = Tmp->data;
            BST->right = Delete(BST->data, BST->right); // 在删除结点的右子树中删除最小元素
        } else { // 被删除结点有一个或无子结点
            Tmp = BST;
            if (!BST->left) // 有右孩子或无子结点
                BST = BST->right;
            else if(!BST->right) // 有左孩子或无子结点
                BST = BST->left;
            free(Tmp);
        }
    }
    return BST;
}
```

#### 3.9、平衡二叉树

**【例】** 搜索树结点不同插入次序，将导致不同的深度和平均查找长度 ASL

![image-20201115141353096](/img/blog/tree/image-20201115141353096.png)

**平衡因子 **(Balance Factor, 简称 BF)：**BF(T) = h_L - h_R**

其中 h_L 和 h_R 分别为 T 的左、右子树的高度

**平衡二叉树(Balanced Binary Tree) (AVL树)**：空树，或者任一结点左、右子树高度差的绝对值不超过 1，即 `|BF(T)| <= 1`

**平衡二叉树的调整**

“麻烦结点” 在不平衡的“发现者”右子树的右子树：RR 插入，需要 RR 旋转(右单旋)

![image-20201115170804281](/img/blog/tree/image-20201115170804281.png)

“麻烦结点” 在不平衡的“发现者”左子树的左子树：LL 插入，需要 LL 旋转(左单旋)

![image-20201115170903525](/img/blog/tree/image-20201115170903525.png)

“麻烦结点” 在不平衡的“发现者”左子树的右子树：LR 插入，需要 LR 旋转

![image-20201115171117839](/img/blog/tree/image-20201115171117839.png)

“麻烦结点” 在不平衡的“发现者”右子树的左子树：RL 插入，需要 RL 旋转

![image-20201117151523311](/img/blog/tree/image-20201117151523311.png)


- **判别是否是同一颗二叉搜索树**

  给定一个插入序列就可以唯一确定一颗二叉搜索树，然而一颗给定的二叉搜索树却可以有多种不同的插入序列得到。

  **【例】** 按照序列 {2, 1, 3} 和 {2, 3, 1} 插入初始为空的二叉搜索树，都得到一样的结果。

  **问题：对于输入的各种插入序列，你需要判断他们是否能生成一样的二叉搜索树？**

  **[INPUT]**

  ```
  4 2 // 结点个数、需要比较的树的个数
  3 1 4 2
  3 4 1 2
  3 2 4 1
  
  2 1
  2 1
  1 2
  0
  ```

  **[OUTPUT]**

  ```
  Yes
  No
  No
  ```

  **求解思路**

  两个序列是否对应相同搜索树的判别

  1. 分别建两棵搜索树的判别方法：根据两个序列反别建树，再判别树是否一样

  2. 不建树的判别方法：递归判断左右子树是否相同

     ![image-20201118160809603](/img/blog/tree/image-20201118160809603.png)

  3. 建一棵树，再判别其他序列是否与该树一致

     **求解思路**

     1. 搜索树表示
     2. 建搜索树 T
     3. 判别一序列是否与搜索树 T 一致

     ```c++
     typedef struct TreeNode *Tree;
     struct TreeNode {
         int v;
         Tree left, right;
         int flag;
     };
     ```

     ```c++
     int main(void) {
         int N, L;
         Tree T;
         
         cin >> N;
         while(N) {
             cin >> L;
             T = MakeTree(N);
             for (int i = 0; i < L; i++) {
                 if (Judge(T, N)) cout << "Yes" << endl;
                 else cout << "No" << endl;
                 ResetT(T); // 清除 T 中的标记 flag
             }
             FreeTree(T);
             cin >> N;
         }
         return 0;
     }
     ```

     ```C++
     Tree NewNode(int V) {
         Tree T = (Tree)malloc(sizeof(struct TreeNode));
         T->v = V;
         T->left = T->right = NULL;
         T->flag = 0;
         return T;
     }
     
     Tree Insert(Tree T, int V) {
         if(!T) T = NewNode(V);
         else {
             if(V > T->v)
                 T->right = Insert(T->right, V);
                else
                 T->left = Insert(T->left, V);
         }
         return T;
     }
     
     Tree MakeTree(int N) {
         Tree T;
         int V;
         cin >> V;
         T = NewNode(V);
         for (int i = 1; i < N; i++) {
             cin >> V;
             T = Insert(T, V);
         }
         return T;
     }
     ```

     ```c++
     // 在树 T 中按顺序搜索序列2中的每一个数
     // 如果每次搜索经过的结点再前面均出现过，则一致，否则不一致
     int check(Tree T, int V) {
         if (T->flag){
             if(V < T->v)
                 return check(T->left, V);
             else if(V > T->v)
                 return check(T->right, V);
             else
                 return 0;
         } else {
             if(V == T->v) {
                 T->flag = 1;
                 return 1;
             } else {
                 return 0;
             }
         }
     }
     ```

     ```c++
     int Judge(Tree T, int N) {
         int V, flag = 0;
         cin >> V;
         if (V != T->v) flag = 1;
         else T->flag = 1;
         
         for (int i = 1; i < N; i++) {
             cin >> V;
             if((!flag) && (!check(T, V))) flag = 1;
         }
         if(flag) return 0;
         else return 1;
     }
     ```

     ```c++
     void ResetT(Tree T) { // 清除 T 中各个结点的 flag 标记
         if(T->left) ResetT(T->left);
         if(T->right) ResetT(T->right);
         T->flag = 0;
     }
     
     void FreeTree(Tree T) { // 释放 T 的空间
         if(T->left) FreeTree(T->left);
         if(T->right) FreeTree(T->right);
         free(T);
     }
     ```

#### 3.10、堆
- 优先队列 (Priority Queue)：特殊的**队列**，取出元素的顺序是依照元素的**优先权(关键字)大小**，而不是元素进入队列的先后顺序

  **若采用数组或链表实现优先队列**

  1. 数组：
     - 插入：元素总是插入尾部 ( O(1) )
     - 删除：查找最大(或最小)关键字 + 从数组中删去需要移动元素 (O(n) + O(n))

  2. 链表：
     - 插入：元素总插汝链表的头部 ( O(1) )
     - 删除：查找最大(或最小)关键字 + 删去结点 (O(n) + O(1))

  3. 有序数组：
     - 插入：找到合适的位置 + 移动元素并插入 ((O(n) 或 O(log2(n) ) + O(n))
     - 删除：删去最后一个元素(O(1))

  4. 有序链表：
     - 插入：找到合适的位置 + 插入元素(O(n) + O(1))
     - 删除：删除首元素或者最后元素(O(1))

  **是否可以采用二叉树存储结构？**

   优先队列的**完全二叉树**表示

  ![image-20201120202502027](/img/blog/tree/image-20201120202502027.png)

- 堆的两个特性
  1. 结构性：用数组表示的完全二叉树
  2. 有序性：任一结点的很关键字是其子树所有结点的最大值(或最小值)
     - "最大堆(MaxHeap)"，也称"大顶堆"：最大值
     - "最小堆(MinHeap)"，也称"小顶堆"：最小值

- 堆的抽象数据类型描述
  - 堆的名称：最大堆(MaxHeap)
  - 数据对象集：完全二叉树，每个结点的元素值不小于其子结点的元素值
  - 操作集：最大堆`H ∈ MaxHeap`，元素 `item ∈ ElementType`，主要操作有：
    - `MaxHeap Create(int MaxSElements)`：创建一个空的最大堆
    - `Boolean IsFull(MaxHeap H)`：判断最大堆 H 是否已满
    - `void Insert(MaxHeap H, ElementTpye item)`：将元素 item 插入最大堆 H
    - `Boolean IsEmpty(MaxHeap H)`：判断最大堆 H 是否为空
    - `ElementType DeleteMax(MaxHeap H)`：返回 H 中最大元素(高优先级)

- 最大堆的操作
  - 最大堆的创建
    
    ```c++
    typedef struct HeapStruct *MaxHeap;
    struct HeapStruct {
        ElementType *Elements; // 存储堆元素的数组
        int size; // 堆的当前元素个数
        int capacity; // 堆的最大容量
    };
    typedef Heap MaxHeap; // 最大堆
    typedef Heap MinHeap; // 最小堆
    
    #define MaxData 1000  // 该值应根据具体情况定义为大于堆中所有可能元素的值
    MaxHeap Create(int MaxSize) { // 创建容量为 MaxSsize 的最大堆
        MaxHeap H = malloc(sizeof(struct HeapStruct));
        H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));
        H->size = 0;
        H->capacity = MaxSize;
        H->Elements[0] = MaxData;
        // 定义"哨兵"为大于对堆中所有可能元素的值，便于以后更快操作
        return H;
    }
    ```
  
  - 最大堆的插入

    将新增结点插入到从父结点到根结点的有序序列中
  
    ```c++
    bool IsFull(MaxHeap H) {
        return (H->size == H->capacity);
    }
    
    void Insert(MaxHeap H, ElementTpye item) {
        // 将元素 item 插入最大堆 H，其中 H->Elements[0] 已经定义为哨兵
        if(IsFull(H)) {
            cout << "最大堆已满" << endl;
            return;
        }
        int i = ++H->ssize;
        for ( ; H->Elements[i/2] < item; i /= 2) {
            H->Elements[i] = H->Elements[i/2];
        }
        H->Elements[i] = item;
    }
    ```
  
  $$
  T(N)=O(logN)
  $$
  
  - 最大堆的删除
  
    取出根结点(最大值)元素，同时删除堆的一个结点

    ```c++
    bool IsEmpty(MaxHeap H) {
          return (H->size == 0);
    }
      
    ElementType DeleteMax(MAxHeap H) {
        // 从最大堆 H 中取出键值为最大的元素，并删除一个结点
        int parent, child;
        ElementType MaxItem, temp;
        if(IsEmpty(H)) {
            cout << "最大堆已为空" << endl;
            return;
        }
        MaxItem = H->Elements[1]; // 取出根结点最大值
        // 用最大堆中最后一个元素从根结点开始向上过滤下层结点
        temp = H->Elements[H->size--]; // 最后一个元素
        for(parent = 1; parent * 2 <= H->size; parent = child) {
            child = parent * 2;
            if((child != H->size) && // 判断有无右儿子
               (H->Elements[child] < H->Elements[child + 1]))
                child++; // child 指向左右子结点的较大者
            
            if(temp >= H->Elements[child])
                break;
            else // 移动 temp 元素到下一层
                H->Elements[parent] = H->Elemnets[child];
        }
        H->Elements[parent] = temp;
        reruen MaxItem;
    }
    ```
  
  - 最大堆的建立
  
    建立最大堆：将已经存在的 N 个元素按最大堆的要求存放在一个以为数组中
  
    - 方法一：通过插入操作，将 N 个元素一个个相继插入到一个初始为空的堆中去，其时间代价最大为 `O(NlogN)`
    - 方法二：在线性时间复杂度下建立最大堆
      1. 将 N 个元素按输入顺序存入，先满足完全二叉树的结构特性
      2. 调整各个结点位置，以满足最大堆的有序特性
  
    ![image-20201121140323596](/img/blog/tree/image-20201121140323596.png)
  
      ```c++
      void PercDown(MaxHeap H, int p) { 
          // 下滤：将 H 中以 H->Elements[p] 为根的子堆调整为最大堆
        int parent, child;
          ElementType X;
      
          X = H->Elements[p]; // 取出根结点存放的值
          for(parent = p; parent * 2 <= H->size; parent = child) {
              child = parent * 2;
              if((child != H->size) && 
                (H->Elements[child] < H->Elements[child + 1]))
                  child++;  // child 指向左右子结点的较大者
      
              if( X >= H->Elements[child] ) 
                  break; // 找到了合适位置
              else  // 下滤 X
                  H->Elements[parent] = H->Elements[child];
          }
          H->Elements[parent] = X;
      }
      
      void BuildMaxHeap(MaxHeap H) {
          // 调整 H->Elements[] 中的元素，使满足最大堆的有序性
          // 这里假设所有 H->size 个元素已经存在 H->Elements[] 中
      
          int i;
          // 从最后一个结点的父节点开始，到根结点 1
          for(i = H->size/2; i > 0; i--)
              PercDown(H, i);
      }
      ```

#### 3.11、哈夫曼树与哈夫曼编码

**什么是哈夫曼树(Huffman Tree)**

【例】将百分制的考试成绩转换为五分制的成绩

```c++
if(score < 60) grade = 1;
else if(score < 70) grade = 2;
else if(score < 80) grade = 3;
else if(score < 90) grade = 4;
else grade = 5;
```

判定树：

![image-20201121152254478](/img/blog/tree/image-20201121152254478.png)

如果考虑学生成绩的分布概率

| 分数段 | 0 - 59 | 60 -69 | 70 - 79 | 80 - 89 | 90 - 100 |
| ------ | ------ | ------ | ------- | ------- | -------- |
| 比例   | 0.05   | 0.15   | 0.40    | 0.30    | 0.10     |

查找效率 = `0.05 x 1 + 0.15 x 2 + 0.4 x 3 + 0.3 * 4 + 0.1 * 4 = 3.15`

修改判定树：

![image-20201121152943434](/img/blog/tree/image-20201121152943434.png)

```c++
if(score < 80) {
    if(score < 70) {
        if(score < 60)
            grade = 1;
        else
            grade = 2;
    } else
        grade = 3;
} else if(score < 90)
    grade = 4;
else
    grade = 5;
```

查找效率 = `0.05 x 3 + 0.15 x 3 + 0.4 x 2 + 0.3 * 2 + 0.1 * 2 = 2.2`

**【问】** 如何根据结点不同的查找频率构造更有效的搜索树？

- 哈夫曼树的定义

  **带权路径长度(WPL)**：设二叉树有 n 个叶子结点，每个叶子结点带有权值W_k，从根结点到每个叶子结点的长度为L_k，则每个叶子结点的带权路径长度之和就是:
  $$
  WPL = \sum_{k=1}^{n}W_kl_k
  $$
  最优二叉树或**哈夫曼树**：WPL 最小的二叉树

- 哈夫曼树的构造

  每次把**权值最小的两棵**二叉树合并

  ![image-20201122165603401](/img/blog/tree/image-20201122165603401.png)

```c++
typedef struct TreeNode *HuffmanTree;
struct TreeNode {
    int weight;
    HuffmanTree left, right;
}

HuffmanTree Huffman(MinHesp H) {
    // 假设 H->size 个权值已经存在 H->Elements[]->weight 里
    HuffmanTree T;
    BuildMinHeap(H); // 将 ->Elements[] 按权值调整为最小堆
    for (int i = 1; i < H->sizel i++) { // 做 H->size - 1 次合并
        T = malloc(sizeof(struct TreeNode)); // 建立新节点
        T->left = DeleteMin(H); // 从最小堆中删除一个结点，作为新 T 的左子结点
        T->right = DeleteMin(H); // 从最小堆中删除一个结点，作为新 T 的右子节点
        T->weight = T->left->weight + T->right->weight; // 计算新权值
        Insert(H, T); // 将新 T 插入最小堆
    }
    T = DeleteMin(H);
    return T;
}
```

$$
整体复杂度O(NlogN)
$$

- 哈夫曼树的特点
  1. 没有度为 1 的结点
  2. n 个叶子节点的哈夫曼树共有 2n - 1 个结点
  3. 哈夫曼树的任意非叶结点的左右子树交换后任是哈夫曼树
  4. 对于同一组权值，存在不同构的两棵哈夫曼树，但是他们的 WPL 值是一样的
     **eg：**对于一组权值 {1， 2， 3，3}，不同构的两棵哈夫曼树

     ![image-20201122163102981](/img/blog/tree/image-20201122163102981.png)

- 哈夫曼编码

  **【问】**给定一段字符串，如何对字符进行编码，可以使得该字符串的编码存储空间少？

  **【例】**假设有一段文本，包含 58 个字符，并由以下 7 个字符构成：`a, e, i, s, t, 空格(sp), 换行(nl)` 。这 7 个字符出现的次数不同。如何对这 7 个字符进行编码，使得总编码空间最少?

  **【分析】**

  1. 用等长 ASCII 编码：58 * 8 = 464 位
  2. 用等长 3 位编码：58 * 3 = 174 位
  3. 不等长编码：出现频率高的字符用的编码短些，出现频率低的字符则可以长些

     用二叉树进行编码：保证对象在叶结点上即可

     ![image-20201122164616483](/img/blog/tree/image-20201122164616483.png)

     使用哈夫曼树进行构造可使总编码空间最少

  **eg：**

  | Ci   | a    | e    | i    | s    | t    | sp   | nl   |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  | Fi   | 10   | 15   | 12   | 3    | 4    | 13   | 1    |

![image-20201122165119740](/img/blog/tree/image-20201122165119740.png)

#### 3.12、集合

- 集合的表示
  - 集合运算：**交、并、补、差**，判定一个元素是否属于某一集合
  - 并查集：集合**并、查**某元素属于什么集合
  - 并查集问题中集合存储如何实现？
    1. 可以用树结构表示集合，树的每个结点代表一个集合
    2. 采用数组存储形式

       数组中每个元素的类型描述为：

       ```c++
       typedef struct {
       	ElementType data;
           int parent;
       } SetType;
       ```

       | 下标 | data | parent |
       | :--: | :--: | :----: |
       |  0   |  1   |   -1   |
       |  1   |  2   |   0    |
       |  2   |  3   |   -1   |
       |  3   |  4   |   0    |
       |  4   |  5   |   2    |
       |  5   |  6   |   -1   |
       |  6   |  7   |   0    |
       |  7   |  8   |   2    |
       |  8   |  9   |   5    |
       |  9   |  10  |   5    |

  - 集合运算

    1. 查找某个元素所在的集合(用根结点表示)

       ```c++
       int Find(SetType S[], ElementType X) {
           // 在数组 S 中查找值为 X 的元素所属的集合
           // MaxSize 是全局变量，为数组 S 的最大长度
           int i;
           for(i = 0; i < MaxSize && S[i].data != X; i++);
           if(i >= MaxSize) return -1; // 未找到 X，返回 -1
           for( ; S[i].parent >= 0; i = S[i].parent);
           return i; // 找到 X 所属集合，返回树根结点在数组 S 中的下标
       }
       ```

    2. 集合的并运算

       - 分别找到 X1 和 X2 两个元素所在的集合树的**根结点**
       - 如果他们不同根，则将其中**一个根结点的父结点指针设置成另一个根结点**的数组下标

       ```c++
       void Union(SetType S[], ElementType X1, ElementType X2) {
           int root1 = Find(S, X1);
           int root2 = Find(S, X2);
           if(root1 != root2) S[root2].parent = root1;
       }
       ```

       为了改善合并以后的查找性能，可以采用小的集合合并到相对大的集合中(修改 Union 含糊)
       
       ```c++
       void Union(SetType S[], int root1, int root2) { 
           // 这里默认 root1 和 root2 是不同集合的根结点
           // 保证小集合并入大集合
           if (S[root2] < S[root1]) { // 如果集合 2 比较大
               S[root2] += S[root1]; // 集合 1 并入集合 2
               S[root1] = root2;
           } else { // 如果集合 1 比较大
               S[root1] += S[root2]; // 集合 2 并入集合 1
               S[root2] = root1;
           }
       }
       
       int Find(SetType S, ElementType X) { 
           // 默认集合元素全部初始化为 -1
           if ( S[X] < 0 ) // 找到集合的根
               return X;
           else
               return S[X] = Find(S, S[X]); // 路径压缩
       }
       ```

#### 3.13、堆中的路径

题目理解：

将一系列给定数字插入一个初始为空的小顶堆 H[]。随后对任意给定的下标 i，打印从 H[i] 到根结点的路径

**输入样例：**

```
5 3
46 23 26 24 10
5 4 3
```

**输出样例：**

```
24 23 10
46 23 10
26 10
```

```c++
typedef struct HeapStruct *MaxHeap;
struct HeapStruct {
    ElementType *Elements; // 存储堆元素的数组
    int size; // 堆的当前元素个数
    int capacity; // 堆的最大容量
};
typedef Heap MaxHeap; // 最大堆
typedef Heap MinHeap; // 最小堆

#define MAXN 1001
#define MINH -10001

int H[MAXN], size;

void Create() {
    size = 0;
    H[0] = MINH; // 设置哨兵
}

void Insert(int X) {
    // 将 X 插入H
    int i;
    for(i = ++size; H[i/2] > X; i /= 2)
        H[i] = H[i/2];
    H[i] = X;
}

int main() {
    int n, m, x, j;
    cin >> n >> m;
    Create(); // 堆初始化
    for(int i = 0; i < n; i++) {
        // 逐个插入方式建堆
        cin >> x; 
        Insert(x);
    }
    for(int i = 0; i < m; i++) {
        cin >> j;
        cout << H[j];
        while(j > 1) {
            // 沿根方向输出各结点
            j /= 2;
            cout << " " << H[j];
        }
        cout << "\n";
    }
    return 0;
}
```