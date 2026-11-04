#include <stdio.h>
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

void BInsertSort(SqList *L) {
    for (int i = 2; i <= L->length; ++i) {
        if (L->r[i].key < L->r[i - 1].key) {
            L->r[0] = L->r[i];
            int low = 1, high = i - 1;
            while (low <= high) {       // low == high 时仍需再比较一次，才能确定插入点，故取 <=
                int mid = (low + high) / 2;
                if (L->r[0].key < L->r[mid].key) 
                    high = mid - 1;     // mid 太大了，往左移
                else 
                    low = mid + 1;      // mid 太小了，往右移
            }
            // 循环结束时 low = high + 1，且 r[high].key <= r[0].key < r[high+1].key，即最终插入位置为 high + 1
            for (int j = i - 1; j >= high + 1; --j) {   // 从 i - 1 开始后移，直到空出 high + 1 的位置，避免循环内结算可以写 j > high
                L->r[j + 1] = L->r[j];
            }
            L->r[high + 1] = L->r[0];
        }
    }
}