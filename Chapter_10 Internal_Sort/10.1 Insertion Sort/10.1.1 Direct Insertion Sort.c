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

void InsertSort(SqList *L) {
    // 从第 2 位开始，与第 1 位元素比较
    for (int i = 2; i <= L->length; ++i) {      // 数组容量 MAXSIZE+1：r[0] 做哨兵，r[1..MAXSIZE] 存数据，故 r[length] 不越界
        if (L->r[i].key < L->r[i-1].key) {      // "<"，往前插入合适位置
            L->r[0] = L->r[i];                  // 先复制到哨兵，防止之后移动元素时覆盖，也不用进行比较 j > 0
            L->r[i] = L->r[i-1];                // 已经确定 i-1 > i，所以现将 i-1 后移
            // 循环结束条件可以不用写成 j > 0 &&  L->r[0].key < L->r[j].key，始终会到达哨兵，退出循环，不会出现 j 越界的情况，适当提升效率
            // 且 L->r[0].key < L->r[j].key 只能用 L->r[0].key 不能用 L->r[i].key（L->r[i].key 已经被覆盖了）
            int j;                                  // 定义在循环外，才可以使用
            for (j = i - 2; L->r[0].key < L->r[j].key; --j) {   // 从 i - 2 继续往前看是否需要后移，直至确定最终 i 的位置
                L->r[j+1] = L->r[j];                // 后移
            }
            // 退出循环时，已经有 L->r[0].key >= L->r[j].key，插入位置应为 j + 1
            L->r[j + 1] = L->r[0];                      // 将 i 放到正确位置
        }
    }
}
