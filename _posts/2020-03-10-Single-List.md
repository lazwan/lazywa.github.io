---
layout: post
title: 『单链表实现』
categories: Code
description: 单链表的简单实现
keywords: Code, Single List
---
实现了一些基本的插入、查找、删除和合并功能。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

/* ===============  定义数据类型 ================= */
typedef struct LNode {
    int data; // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList;

/* =============== 初始化链表 =================== */
void CreatList (LinkList &L, int n) {
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LNode *s, *r;
    r = L;
    int ele;
    cout << "请输入 " << n << " 个数：";
    for (int i =0; i < n; i++) {
        cin >> ele;
        s = (LNode*)malloc(sizeof(LNode));
        s->data = ele;
        r->next = s;
        r = s;
    }
    r->next = NULL;
}

/* ================ 打印链表 ==================== */
void PrintList(LinkList L) {
    LNode *node = L->next;
    cout << "链表元素为：";
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << "\n" << endl;
}

/* ================ 按值查找 ==================== */
int Get_Ele (LinkList L, int find_ele) {
    LNode *node;
    node  = L->next;
    int i = 1;
    while (node != NULL && node->data != find_ele) {
        node = node->next;
        i++;
    }
    return i;
}

/* ================ 按位置查找 =================== */
LNode *Get_Pos (LinkList L, int pos) {
    if (pos == 0) {
        return L;
    } else if (pos < 1) {
        return NULL;
    }
    LNode *node = L;
    int i = 0; 
    while (node && i < pos) {
        node = node->next;
        i++;
    }
    if (node == NULL) {
        cout << "插入位置超出范围" << endl;
        return NULL;
    }
    return node;
}

/* =================== 插入 ==================== */
void InsetEle (LinkList L, int pos, int ele) {
    LNode *node;
    LNode *new_node = (LNode*)malloc(sizeof(LNode));
    new_node->data = ele;
    node = Get_Pos(L, pos-1);
    new_node->next = node->next;
    node->next = new_node;
}

/* =================== 删除 ==================== */
int DeleteEle (LinkList L, int pos) {
    LNode *node, *del_node;
    node = Get_Pos(L, pos-1);
    del_node = node->next;
    node->next = del_node->next;
    int data = del_node->data;
    free(del_node);
    return data;
}

/* =================== 合并 ==================== */
void Merge (LinkList &La, LinkList &Lb) {
    LinkList pa = La->next;
    while (pa->next) {
        pa = pa->next;
    }
    pa->next = Lb->next;
    free(Lb);
}

int main()
{
    LinkList L;
    int inser_ele, del_ele;
    LNode *find_ele, *find_pos;
    int n, ele, pos;

    cout << "初始化链表 L, 请输入长度 n:";
    cin >> n;
    CreatList (L, n); // 初始化链表
    PrintList(L);

    cout << "请输入要查找的元素：";
    cin >> ele;
    pos = Get_Ele (L, ele);
    cout << "所查找的元素的位置为：" << pos << endl;
    PrintList(L);

    cout << "请输入要查找的位置：";
    cin >> pos;
    find_pos = Get_Pos (L, pos);
    cout << "所查找位置的元素为：" << find_pos->data << endl;
    PrintList(L);

    cout << "请输入要插入的元素和位置(空格隔开)：";
    cin >> ele >> pos;
    InsetEle (L, pos , ele);
    PrintList(L);

    cout << "请输入要删除的元素的位置：";
    cin >> pos;
    int data = DeleteEle(L, pos);
    cout << "要删除的元素为：" << data << endl;
    PrintList(L);

    cout << "合并链表 La, Lb：";
    LinkList La, Lb, Lc;
    cout << "初始化链表 La, 请输入长度 n:";
    cin >> n;
    CreatList(La, n);
    cout << "初始化链表 Lb, 请输入长度 n:";
    cin >> n;
    CreatList(Lb, n);
    Merge(La, Lb);
    PrintList(La);
    return 0;
}
```

