#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// 交换 -- 该函数也可以放入 BubbleSort 函数内部，但是拿出来更清晰，注意用指针深拷贝
void swap(RedType *t1, RedType *t2) {
    RedType temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

// Bubble Sort：可以大的值沉底(右移)，也可以小的值浮出水面(左移)
void BubbleSort(SqList *L) {
    int m = L->length - 1;      // i 最大取 m，后移访问 r[i+1] 最大到 r[length]，故 m 初值为 length-1
    int flag = true;            // 是否上一趟发生过交换

    // 上一趟没有发生交换时, flag = FALSE，退出循环，上一趟后序列已经有序，可提前结束
    while (m > 0 && flag == true) {         // m 递减到 0 说明所有元素已归位
        // 每次从第一个元素开始扫描，每一趟都有一个大元素沉底
        flag = false;                       // 先假设本轮不发生交换
        for (int i = 1; i <= m; ++i) {       
            if (L->r[i].key > L->r[i + 1].key) {    // 不能等于，即等于时不交换，保证稳定性
                flag = true;
                swap(&L->r[i], &L->r[i + 1]);
            }
        }
        --m;                                // 该趟最大值已沉底，向前更新右边界
    }
}