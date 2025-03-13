#include<stdio.h>
#include<stdlib.h>


#define ROOT 1
#define cmp  >
#define FATHER(i) ((i) / 2) //船长的版本用宏
#define LEFT(i)   ((i) * 2)
#define RIGHT(i)  ((i) * 2 + 1)
#define SWAP(a , b)  { \ 
    printf_s("swap(%d, %d)\n", a, b); \
    __typeof(a) __c = (a); \
    (a) = (b); \
    (b) = __c; \
}//定义一个用于交换的宏函数

typedef struct PriorityQueue{
    int *__data, *data;
    int size, n;  // size:当前能存储元素的最大个数，n:当前存储元素的个数

}PriorityQueue;

PriorityQueue* initPQ(int size){
    PriorityQueue *p = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    p->__data =(int*)malloc(sizeof(int)*size);
    p->data = p->__data - 1;//船长说的小技巧
    p->size = size;
    p->n = 0;
    return p;
}

void clearPQ(PriorityQueue *p){
    if(p ==NULL) return;
    free(p->__data);
    free(p);
    return;
}

int empty(PriorityQueue *p){
    return p->n == 0;
}

int full(PriorityQueue *p){
    return p->n == p->size;
}

int top(PriorityQueue *p){
    return p->data[ROOT];
}

void down_maintain(int p[], int index, int n){ //弹出元素之后的向下调整
    
    while(LEFT(index) <= n){ //判断左子节点是否存在
        int l , r, i;
        l = LEFT(index);
        r = RIGHT(index);
        i = index; //必须要有i,保留index之后要进行比较

        if(p[l] cmp p[i])   i = l;
        if(r <= n && p[r] cmp p[i])  i = r;
        

        if(index == i ) break;
        SWAP(p[i],p[index]);
        index = i; //每一轮交换一次，交换完有新的根节点
    }
     
    printf_s("\n");

    return ;
}

void up_maintain(int p[], int flag){//插入元素的向上调整
    if(flag == ROOT)return;
    while(flag >= ROOT && p[flag] cmp p[FATHER(flag)]){//增加越界检查以防向上超过根节点
        SWAP(p[flag], p[FATHER(flag)]);
        flag = FATHER(flag);
    }

    printf_s("\n");
    return;
}

int push(PriorityQueue *p, int x){
    if(full(p))return 0;
    p->data[++p->n] = x;
    
    up_maintain(p->data, p->n);//传入参数带调整元素的下标
   
    return 1;
}

int pop(PriorityQueue *p){
    if(empty(p)) return 0;
    int top_val = p->data[ROOT];
    p->data[ROOT] = p->data[p->n];
     p->n--;
    down_maintain(p->data, ROOT,p->n);
    return 1;
}



void output(PriorityQueue* p){
    printf("PQ(%d) : ", p->n);
    for (int i = 1; i <= p->n; i++) {
        printf("%d ", p->data[i]);
    }
    printf("\n");
    return ;
}

int main(){
    #define MAX_NUM 100
    int op,x;

    PriorityQueue *p = initPQ(MAX_NUM);
     while(~scanf_s("%d",&op)){ //按位取反，相当于判断是否读到文件结尾
        if(op == 1){
            scanf_s("%d",&x);
            printf_s("Insert %d to priority queue: \n",x);
            push(p,x);
            output(p);
        }
        else{
            printf_s("Pop %d out of priority queue: \n", top(p));
            pop(p);
            output(p);
        }
     }


    clearPQ(p);
    return 0;
}