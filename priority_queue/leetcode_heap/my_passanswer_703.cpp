/*************************************************************************
    > File Name: my_passanswer_703.cpp
    > Author: arthur lee
    > Mail: ilovekechunrui@gmail.com
    > Created Time: 2025-03-20 21:07:06
    > Description: 先构建一个从小到大的小顶堆，保存其中K大往后的部分，如果开始不够K要分情况讨论
************************************************************************/

/*优化建议:直接构建大小为 k 的小顶堆，而不是先排序再选择后 k 个元素 
> 不需要从完全有序，小顶堆足够使用
*/

#define LEFT(i) ((i) * 2 + 1)
#define RIGHT(i) ((i) * 2 + 2)
#define FATHER(i) (((i) - 1) / 2)
#define ROOT 0
#define cmp <
#define swap(a,b){\
   __typeof(a) __c = (a);\
    (a) = (b);\
    (b) = __c;\
}


typedef struct {
    int flag;
    int* data;
    int size;
    
} KthLargest;


void bubbleSortOptimized(int* nums, int numsSize) {
    int swapped;  // 标记是否发生交换
    for (int i = 0; i < numsSize - 1; i++) {
        swapped = 0;  // 每轮开始时重置标记
        for (int j = 0; j < numsSize - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                // 交换两个元素
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
                swapped = 1;  // 标记发生了交换
            }
        }
        if (!swapped) break;  // 如果没有发生交换，说明数组已经有序
    }
}

void down_update(int* data, int index, int n){
    while(LEFT(index) < n){
        int l = LEFT(index), r = RIGHT(index), i = index;
        if(data[l] cmp data[i]) i = l;
        if(r < n && data[r] cmp data[i]) i = r;
        if(i == index) break;
        swap(data[i],data[index]);
        index = i; 
    }
    return;
}


KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    /*KthLargest* Kth = (KthLargest*)malloc(sizeof(KthLargest));
        Kth->__data = (int*)malloc(sizeof(int) * (10000+numsSize));
        Kth->data = Kth->__data - 1;
        Kth->size = numsSize;
        Kth->flag = k;
        for(int i = 0 ; i < numsSize; i++)
            Kth->__data[i] = nums [i];*/



        int root = 0;
        if(k < 1 || k>numsSize+1 || numsSize < 0)return NULL;//判断是否合法输入
        KthLargest* Kth = (KthLargest*)malloc(sizeof(KthLargest));
        Kth->size = numsSize;//复制size信息
        if(k > numsSize) {
            root = ROOT;
        }
        else   root = numsSize - k ;
        bubbleSortOptimized(nums,numsSize);
        
        Kth->data = (int*)malloc(sizeof(int)* (k+1));//维护小顶堆
        
        if(numsSize != 0){
                for(int i = root,j = 0; i < root + k && i < numsSize  ; i++, j++){
                    Kth->data[j] = nums[i];
                }
        }
        Kth->flag = k;
        return Kth;    
}

int kthLargestAdd(KthLargest* obj, int val) {
    if(obj == NULL) return 0;

    if(obj->size < obj->flag) {
        obj->data[obj->size] = val;
        obj->size++;
        down_update(obj->data,ROOT,obj->flag);
        return obj->data[ROOT];
        }

        if(val > obj->data[ROOT]){
            obj->data[ROOT] = val;
        down_update(obj->data,ROOT,obj->flag);
       }

    return obj->data[ROOT];    
}

void kthLargestFree(KthLargest* obj) {
        if(obj == NULL) return;
        free(obj->data);
        free(obj);
        return;
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/