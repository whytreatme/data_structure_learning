/*************************************************************************
    > File Name: test_703.cpp
    > Author: Arthur lee
    > Mail: ilovekechunrui@gmail.com
    > Created Time: 2025-03-20 20:18:37
    > Description: 这代码是我没办法在leetcode调试写得测试代码，其中还有很多边界检查的bug
************************************************************************/



#include<cstdio>
#include<cstdlib>

#define LEFT(i) ((i) * 2)
#define RIGHT(i) ((i) * 2 + 1)
#define FATHER(i) ((i) / 2)
#define root 1
#define cmp >
#define swap(a,b){\
   __typeof(a) __c = (a);\
    (a) = (b);\
    (b) = __c;\
}


typedef struct {
    int flag;
    int* __data;
    int* data;
    int  ROOT;
    
} KthLargest;


void down_update(int* data, int index, int n){
    while(LEFT(index) <= n){
        int l = LEFT(index), r = RIGHT(index), i = index;
        if(data[l] cmp data[i]) i = l;
        if(r <= n && data[r] cmp data[i]) i = r;
        if(i == index) break;
        swap(data[i],data[index]);
        index = i; 
    }
    return;
}

void heap_sort_final(int* data ,int n){
         int size = n;
    while(size > root){
        swap(data[root],data[size]);
        down_update(data,root,--size);
    }
    return;
}

void linear_heap_bulid(int* data,int size){
        for(int i = size /2; i >= root; i--)
            down_update(data, i, size);
            return;
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    if(k < 1 || numsSize <= 0)return NULL;
        /*KthLargest* Kth = (KthLargest*)malloc(sizeof(KthLargest));
        Kth->__data = (int*)malloc(sizeof(int) * (10000+numsSize));
        Kth->data = Kth->__data - 1;
        Kth->size = numsSize;
        Kth->flag = k;
        for(int i = 0 ; i < numsSize; i++)
            Kth->__data[i] = nums [i];*/
        KthLargest* Kth = (KthLargest*)malloc(sizeof(KthLargest));
        int* my_num = nums - 1;
        linear_heap_bulid(my_num,numsSize);
        heap_sort_final(my_num, numsSize);
        if(k > numsSize)  Kth->ROOT = 1;
        else    Kth->ROOT = numsSize - k + 1;
        Kth->__data = (int*)malloc(sizeof(int)* (k+1));
        Kth->data   =  Kth->__data - 1;
        int j = 1;
        for(int i = Kth->ROOT; i < Kth->ROOT + k ; i++, j++){
            Kth->data[j] = my_num[i];
        }
        Kth->flag = k; 
        return Kth;    
}

int kthLargestAdd(KthLargest* obj, int val) {
    if(obj == NULL) return 0;
       if(val > obj->data[obj->ROOT]){
        swap(val,obj->data[obj->ROOT]);
        down_update(obj->data,1,obj->flag);
       }

    return obj->data[1];    
}

void kthLargestFree(KthLargest* obj) {
        if(obj == NULL) return;
        free(obj->__data);
        free(obj);
        return;
}

int main(){
    int* nums = (int*)malloc(sizeof(int)*6);
    int k;
    printf("请输入一个 K:\n");
    scanf("%d",&k);
    printf("请输入一个数组:\n");
    for(int i = 0; i < 6; i++)
        scanf("%d",&nums[i]);

    KthLargest* ka = kthLargestCreate(k,nums,6);
    free(nums);
    kthLargestFree(ka);
    return 0;
}
/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/