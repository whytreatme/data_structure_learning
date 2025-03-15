#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define cmp >
#define ROOT 1
#define FATHER(i) ((i) / 2)
#define LEFT(i)   ((i) * 2)
#define RIGHT(i)  ((i) * 2 + 1)


#define SWAP(a, b){ \
    __typeof(a) __c = (a); \
    (a) = (b) ;\
    (b) = __c;\
}

#define TEST(func, arr, n){ \
    printf_s("TEST %s ", #func); \
    int *temp = (int*)malloc(sizeof(int)* n); \
    memcpy(temp, arr, sizeof(int)* n); \
    long long b = clock(); \
    func(temp, n);\
    long long e = clock(); \
    if(check(temp, n)){ \
        printf_s("OK\t"); \
        printf_s("%lld ms\n", 1000 * (e - b) / CLOCKS_PER_SEC);\
    } \
    else \
        printf_s("FAIL\t");\
    free(temp); \
}//注意在宏定义里面不能有空行，否则识别不了

void output(int* arr, int size){
    for(int i = 0; i < size; i++){
        printf_s("%d\t",arr[i]);
    }
    printf_s("\n");
}

void up_update(int* data, int index){
    if(index == ROOT)return;
    while(FATHER(index) >= ROOT && data[index] cmp data[FATHER(index)]){
        SWAP(data[index], data[FATHER(index)]);
        index = FATHER(index);
    }
    return;
}

/*void down_update(int* data, int index){
    if(index < ROOT)return;
    if(data[index] cmp data[FATHER(index)]){
        SWAP(data[index],data[FATHER(index)]);
    }

    return;
}我的错误实现,这不是向下调整，就倒数第一一层还行，到了倒数第二层会出错*/

void down_update(int* data, int index, int n){//向下调整
        while(LEFT(index) <= n){
            int l,r,i;//这里需要变量i的意义就和指针一样，原索引指向原来位置，i指向待交换位置
            l = LEFT(index); r = RIGHT(index); i =index;
            if(data[l] cmp data[i]) i = l;
            if(r <= n && data[r] cmp data[i]) i = r;
            if(i == index) break;//细节如果两个标记一致，则不再需要交换
            SWAP(data[i],data[index]);
            index = i;
        }
        return;
}
void heap_sort_final(int* data, int n){
    int size = n;
    while(size > ROOT){
        SWAP(data[ROOT],data[size]);
        down_update(data,ROOT,--size);
    }
    return;
}

void normal_heap_build(int* data, int n){
    
    for(int i = 2; i <= n; i++){
        up_update(data, i);
    }    
   return;
}

/*void linear_heap_build(int* data, int n){
    for(int i = n; n >= ROOT; n--){
        down_update(data,n);
    }
} 应该使用i作为参数穿入*/

void linear_heap_build(int* data,int n){
        for(int i = n / 2; i >= ROOT; i--){
            down_update(data,i,n);
        }
        return;
}

void normal_heap(int* arr, int size){
    int* data = arr - 1;
    normal_heap_build(data, size);
    heap_sort_final(data,size);
    
    return;
}

void linear_heap(int* arr,int size){
    int* data = arr - 1;
    linear_heap_build(data,size);
   /* linear_heap_build(data, size); 错误实现*/
   heap_sort_final(data,size);
    return;
}

int* getRandData(int size){
    int* arr = (int*) malloc(sizeof(int)*size);

    for(int i = 0 ; i < size; i++)
        arr[i] = rand() % 10000;

    return arr;
}


bool check(int* arr, int size){
    for(int i = 1; i < size ; i++){
        if(arr[i] < arr[i - 1]) return false;
    }/*从i=1开始读到最后一个，与前一个进行比较，这样做
    比 for(int i = 0; i < size -1; i++){
        if(arr[i] > arr[i + 1]) }要少一步计算*/
    return true;
}

int main(){
#define MAX_NUM 70000000

    srand(time(0));
    int* arr = getRandData(MAX_NUM);
    TEST(normal_heap,arr,MAX_NUM);
    TEST(linear_heap, arr, MAX_NUM);
    free(arr);
    return 0;
}