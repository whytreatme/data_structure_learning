#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

#define SWAP(a,b){\
    __typeof(a)__c = (a);\
    (a) = (b);\
    (b) = __c;\
}
typedef struct Node{
    char* s;
    Node* next;
} Node;

typedef struct HashTable{
    Node* data;
    int cnt,size;
} HashTable;

bool insert(HashTable* h, const char* s);
void clearHashTable(HashTable* h);

Node* getNewNode(const  char* s){
    Node* node = (Node*)malloc(sizeof(Node));
    node->s = strdup(s);
    node->next = NULL;
    return node;
}

HashTable* getNewHashTable(int n){
    HashTable* h = (HashTable*)malloc(sizeof(HashTable));
    h->data = (Node*)malloc(sizeof(Node) * n);
    for(int i = 0 ; i < n; i++)
        h->data[i].next = NULL;
    h->size = n;
    h->cnt = 0;
    return h;
}

int hash_func(const char* s){
    int seed = 131, h = 0;
    for(int i = 0; s[i]; i++){
        h = h * seed + s[i];
    }
    return h & 0x7fffffff;
}

void swapHashTable(HashTable* a, HashTable* b){
    SWAP(a->cnt,  b->cnt);
    SWAP(a->data, b->data);
    SWAP(a->size, b->size);
}

void expand(HashTable* h){
    printf("expand HashTable %d -> %d \n", h->size, h->size * 2);
    HashTable* new_h = getNewHashTable(h->size * 2);
    for(int i = 0; i < h->size; i++){
        Node* p = h->data[i].next;
        while(p){
            insert(new_h, p->s);
            p = p->next;
        }
    }    
    swapHashTable(new_h, h);
    clearHashTable(new_h);
    return;
}

bool insert(HashTable* h, const char* s){
    if(h->cnt >= h->size * 2) 
        expand(h);
    Node* p = getNewNode(s);
    int hcode = hash_func(s), ind = hcode % h->size;
    Node* q = h->data[ind].next;
    p->next = q;
    h->data[ind].next = p;
    h->cnt += 1;
    return true;
}

bool find(HashTable* h, const char* s){
   int ind = hash_func(s) % h->size;
   Node* p = h->data[ind].next;
   while(p){
        if(strcmp(p->s, s) == 0) return true;
        p = p->next;
   } 
   return false;
}

void clearNode(Node* node){
    if(node == NULL) return;
    if(node->s) free(node->s);
    free(node);
    return;
}

void clearHashTable(HashTable* h){
    if(h == NULL) return ;
    for(int i = 0; i < h->size; i++){
        Node* p = h->data[i].next, * q;
        while(p){
            q = p->next;
            clearNode(p);
            p = q;  
        }
    }
    free(h);
}

void output(HashTable* h){
    if(h == NULL) return;
    for(int i = 0; i < h->size; i++){
        printf("%d: ", i);
        Node* p = h->data[i].next;
        while(p){
            printf("%s ", p->s);
            p = p->next;
            if(p) printf("-> ");
        }
        printf("\n");
    }
    printf("\n");
    return;
}

int main(){
    srand(time(0));
#define MAX_NUM 2
    HashTable* h = getNewHashTable(MAX_NUM);
#undef MAX_NUM
    char s[100];
    printf("insert the node: \n");
    while(~scanf("%s", s)){
        if(strcmp(s, "end") == 0) break;
        insert(h, s);
        printf("insert the node: \n");
    }
    output(h);
    while(~scanf("%s", s)){
        if(strcmp(s, "end") == 0) break;
        if(find(h, s)) 
            printf("find %s in HashTable %d / %d\n", s, h->cnt, h->size);
        else
            printf("find NULL\n");
    }

    clearHashTable(h);
    return 0;
}