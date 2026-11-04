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

typedef SqList HeapType;    // 堆排序采用顺序存储

// 大顶堆的调整 -- “下坠”
// 实际上使用交换就不用 r[0] 辅助存储了，循环遍历完 s 就到了插入的位置
void HeapAdjust(HeapType *H, int s, int m) {
    // 调整根节点元素 H.r[s]，调整二叉树 H.r[s..m] 使之重新成为大顶堆(除 H.r[s] 外其他元素均满足大顶堆的特性)
    H->r[0] = H->r[s];      // r[0] 暂存根节点 s
    for (int i = 2 * s; i <= m; i *= 2) {   // 与其左右孩子比较，故而 i = 2*s(左孩子)
        // 找到左右孩子中较大者，判断其是否应该和 s 交换
        if (i < m && H->r[i].key < H->r[i + 1].key) {
            ++i;
        }
        if (H->r[0].key >= H->r[i].key) {   // 根 >= 孩子，不用“下坠”，其位置符合大顶堆特性，直接退出循环
            break;
        } else {
            H->r[s] = H->r[i];              // 将大孩子移到根节点的位置，直接赋值(1次)不用交换(3次复制)
            s = i;                          // 继续 “下坠”
        }
    }
    H->r[s] = H->r[0];                      // 最终插入位置
}

// 构建堆：调整每个元素即为构建堆
void BuildMaxHeap(HeapType *H) {
    // 从最后一个非叶子节点开始，自下而上调整堆
    for (int i = H->length / 2; i > 0; --i) {
        HeapAdjust (H, i, H->length);
    }
}

// 交换
void Swap(RedType *t1, RedType *t2) {
    RedType temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

// 堆排序
void HeapSort(HeapType *H) {
    BuildMaxHeap(H);
    for (int i = H->length; i > 1; --i) {       // 进行 n - 1 次重建堆
        Swap(&H->r[1], &H->r[i]);               // 把堆底元素放到堆顶，当前堆顶最大值交换至末尾，重新建堆，得到新的最大值
        HeapAdjust(H, 1, i - 1);                // 重新调整 r[1..i-1]，因为交换后，只剩 i-1 个元素
    }
}