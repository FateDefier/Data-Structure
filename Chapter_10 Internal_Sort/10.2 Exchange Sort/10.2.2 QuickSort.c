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

// 一次划分(Partition)
int Partition(SqList *L, int low, int high) {
    int pivotkey = L->r[low].key;           // 枢轴
    L->r[0] = L->r[low];                    // 暂存枢轴，这样就不用一直交换枢轴(3次赋值->1次)，可以使用“逻辑空位”
    while (low < high) {
        // 现在 low 的位置为逻辑空位，从high(其右边已确认 >= 枢轴)向左找 <pivotkey 即该放到枢轴左边的元素
        while (low < high && L->r[high].key >= pivotkey) --high;// 仍然要 low<high，因为 high 在移动，while的比较只保证进入时满足 low<high
        L->r[low] = L->r[high];             // “交换” -- 实际为将小于枢轴的元素移动到逻辑空位
        // 现在 high 的位置为逻辑空位，从low(其左边已确认 <= 枢轴)向右找 >pivotkey 即该放到枢轴右边的元素
        while (low < high && L->r[low].key <= pivotkey) ++low;
        L->r[high] = L->r[low];
    }
    // 退出时 low == high，此位置即枢轴的最终位置，将暂存的枢轴填入
    L->r[low] = L->r[0];                    // 枢轴记录到位
    return low;                             // 返回枢轴的位置
}

// 递归快速排序
void QuickSort (SqList *L, int low, int high) {
    if (low < high) {       // 递归终止条件
        int pivotloc = Partition(L, low, high);     // 用枢轴位置 pivotloc 将 [low, high] 一分为二
        QuickSort(L, low, pivotloc - 1);            // 对左子表递归排序
        QuickSort(L, pivotloc + 1, high);           // 对右子表递归排序
    }
}