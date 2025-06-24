#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<inttypes.h>
#include<cstring>

typedef struct Node{//跳跃表也是由节点构成的
    int key, level;
    struct Node *next, *down, *up;
} Node;


typedef struct Skiplist{//我们需要跳跃表的结构来维护头尾节点
    Node *head, *tail;
    int max_level;//定义跳跃表最大层数
} Skiplist;

Node* getNewNode(int key, int n){
    Node *nodes = (Node*)malloc(sizeof(Node) * n); //直向一层的最下节点
    for(int i = 0; i < n; i++){
         nodes[i].key = key;
         nodes[i].level = i;
         nodes[i].next = NULL;
         nodes[i].up = (i + 1 < n ? nodes + (i + 1) : NULL);
         nodes[i].down = (i ? nodes + (i - 1) : NULL);
    }
    return nodes + n - 1; //返回一个节点的最高层
}

Skiplist* getNewSkiplist(int n){
    Skiplist* s = (Skiplist*)malloc(sizeof(Skiplist));
    s->head = getNewNode(INT32_MIN, n);
    s->tail = getNewNode(INT32_MAX, n);
    Node *p = s->head, *q = s->tail;
    while(p){
        p->next = q;
        p = p->down;
        q = q->down;
    }
    s->max_level = n;//头尾节点一定是层数最多的，其它的节点层数不能比它们多
    return s;
}

Node* find(Skiplist* s, int key){//往下走值变小，往next走，值变大
    Node* p = s->head;
    while(p && p->key != key){
        if(p->next->key <= key) p = p->next;
        else
            p = p->down ;
    }
    return p;
}

double randDouble(){
    double q;
    q = rand()  % 1000 * 1.0 / 1000.0;
    return q;
}

int randLevel(Skiplist* s){
    int level = 1;
    double p = 1.0 / 2.0;
    while(randDouble() < p) level += 1;
    
#define MIN(a, b)  (a) < (b) ? (a) : (b)
    return MIN(s->max_level, level);
#undef MIN
}

void insert(Skiplist* s, int x){
    int level = randLevel (s);
    Node* node = getNewNode(x, level);
    Node* p = s->head, *q = node;
    while(p->level > node->level) p = p->down;
    while(p){
        while(p->next->key < q->key) p = p->next;
        q->next = p->next;
        p->next = q;
        p = p->down;
        q = q->down;
    }
}

void clearNode(Node* p){
    if(p == NULL) return;
    free(p);
    return;
}

void clearSkiplist(Skiplist *s){
    Node* p = s->head, *q;
    while(p->down) p = p->down;
    while(p){
        q = p;
        p = p->next;
        clearNode(q);
    }
    free(s);
    return;
}

void output(Skiplist* s){
    int len = 0;
    Node* p =  s->head;
    while(p->down) p = p->down;
    for(int i = 0; i < s->max_level; i++){
        len += printf("%4d", i);
    }
    printf("\n");
    for(int i = 0; i < len; i++) printf("-");
    printf("\n");
    while(p){
        bool flag = (p->key != INT32_MAX && p->key != INT32_MIN);
        for(Node* q = p; flag && q; q = q->up)
            printf("%4d", q->key);
        printf("\n");
        p = p->next;
    }
}

int main(){
    int x;
#define MAX_LEVEL 32
    Skiplist* s = getNewSkiplist(MAX_LEVEL);
#undef MAX_LEVEL
    while(~scanf("%d", &x)){
        if(x == -1) break;
        insert(s, x);
    }
    output(s);

    
   while(~scanf("%d", &x)){
        if(x == -1) break;
        Node* p = find(s, x);
        printf("find result : ");
        if(p){
            printf("key = %d, level = %d\n", p->key, p->level + 1);
        }else{
            printf("NULL\n");
        }
    }

    clearSkiplist(s);
    return 0;
}