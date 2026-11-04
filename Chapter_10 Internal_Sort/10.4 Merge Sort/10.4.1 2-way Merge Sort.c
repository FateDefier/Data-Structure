#include <stdlib.h>

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

// 2路归并严书逻辑感觉没有太清晰，有点麻烦，这里结合王道两个函数写

// 辅助数组
RedType auxArray[MAXSIZE+1];  

void Merge(SqList *L, int low, int mid, int high) {
    // r[low..mid] 和 r[mid+1..high] 各自有序，合并二者为新的有序表
    // 为保证原地，复制到辅助数组操作
    int i, j, k;
    for (i = low; i <= high; ++i) {
        auxArray[i] = L->r[i];
    }
    // 合并 -- 类似两个单链表合并
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; ++k) {
        if (auxArray[i].key <= auxArray[j].key) {               // 取等于保证稳定，注意比较的是辅助数组的元素
            L->r[k] = auxArray[i++];
        } else {
            L->r[k] = auxArray[j++];
        }
    }
    // 下面两个循环只会执行一个 -- 还有一边的元素有剩余
    while (i <= mid) L->r[k++] = auxArray[i++];
    while (j <= high) L->r[k++] = auxArray[j++];
}

// 归并排序 -- 递归
void MergeSort(SqList *L, int low, int high) {
    if (low < high) {                   // 递归终止时自动退出，即 low == high 只有一个元素
        int mid = (low + high) / 2;
        MergeSort(L, low, mid);         // 左侧子序列递归归并
        MergeSort(L, mid + 1, high);    // 右侧子序列递归归并
        Merge(L, low, mid, high);       // 左右侧合并
    }
} 