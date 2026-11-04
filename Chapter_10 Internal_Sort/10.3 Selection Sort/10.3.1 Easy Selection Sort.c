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

// 交换
void Swap(RedType *t1, RedType *t2) {
    RedType temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

// 找出 [i, ..., length] 最小值下标
int SelectMinKey(SqList *L, int i) {
    int k = i;                      // 最小值下标
    KeyType min = L->r[i].key;      // 最小值
    for (int j = i + 1; j <= L->length; ++j) {
        if (L->r[j].key < min) {
            k = j;
            min = L->r[j].key;
        }
    }
    return k;
}

// 简单选择排序
void SelectSort(SqList *L) {
    for (int i = 1; i < L->length; ++i) {   // i = length 时，无序区只剩 r[length] 一个元素，天然有序，无需处理
        int j = SelectMinKey(L, i);
        if (j != i) {
            Swap(&L->r[i], &L->r[j]);
        }
    }
}