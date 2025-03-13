#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROOT 1
#define cmp  >
#define ocmp <

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

int push(PriorityQueue *p, int x){
    if(full(p))return 0;
    p->data[++p->n] = x;
    
    up_maintain(p->data, p->n);
   
    return 1;
}

int pop(PriorityQueue *p){
    if(empty(p)) return -1;
    int top_val = p->data[ROOT];
    p->data[ROOT] = p->data[p->n];
     p->n--;
    down_maintain(p->data, ROOT);
    return top_val;
}

void down_maintain(int p[], int flag){ //弹出元素之后的向下调整
    
    int min = 0;

    while(p[flag] ocmp p[(min = flag * 2)] || p[flag] ocmp p[(min = flag * 2 + 1)]){
        int temp = p[flag];
        p[flag] = p[min];
        p[min] = temp;
        flag = min;
    }

    return ;
}

void up_maintain(int p[], int flag){//插入元素的向上调整
    if(flag == ROOT)return;
    while(p[flag] cmp p[flag/2]){
        int temp = p[flag];
        p[flag] = p[flag/2];
        p[flag/2] = temp;
        flag = flag / 2;
    }
    return;
}

int main(){



    return 0;
}