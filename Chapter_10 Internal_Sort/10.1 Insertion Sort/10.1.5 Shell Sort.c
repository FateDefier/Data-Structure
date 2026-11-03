#include <stdio.h>
#include <stdlib.h>
#include "../../../Code_Learning/Data Structure/Status.h"

#define MAXSIZE 20
typedef int KeyType;        // 定义关键字类型为整型
typedef char InfoType;       // 其他信息

typedef struct {
    KeyType key;            // 关键字项
    InfoType otherinfo;     // 其他数据类型
} RedType;                  // 记录类型

typedef struct {
    RedType r[MAXSIZE+1];   // r[0] 闲置或用做哨兵单元
    int length;             // 顺序表长度
}SqList;

// 一趟希尔插入排序
void ShellInsert (SqList *L, int dk) {
    for (int i = dk + 1; i <= L->length; ++i) { // 各子序列的第一个元素（r[1..dk]）天然有序，故从 dk + 1 开始
        if (L->r[i].key < L->r[i - dk].key) {
            L->r[0] =  L->r[i];                 // 暂存，不能做哨兵，因为之后 j 每次减 dk，可能为负数，故而明确规定 j > 0
            int j;
            for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk) {
                L->r[j + dk] = L->r[j];
            }
            L->r[j + dk] = L->r[0];
        }          
    }
}

// 希尔排序
void ShellSort (SqList *L, int dlta[], int t) {
    // 按照增量 dlta[0], dlta[1], ..., dlta[t-1] 逐趟进行希尔排序，最终的 dlta[t-1] = 1(必须，可以做检查)
    for (int k = 0; k < t; ++k) {
        ShellInsert(L, dlta[k]);
    }
}