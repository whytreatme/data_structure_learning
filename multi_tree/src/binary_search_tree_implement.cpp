#include<cstdio>
#include<cstdlib>
#include<ctime>

typedef struct Node{
    int key;
    Node *lchild, *rchild;
}Node;

Node* getNewNode(int key){
    Node* p = (Node*)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node* insert(Node *root, int key){
    if(root == NULL) return getNewNode(key);
    //不需要插入重复元素，实际工作不会用到
    if(root->key == key) return root;
    if(key < root->key) root->lchild = insert(root->lchild, key);
    else if(key > root->key)  root->rchild = insert(root->rchild, key);
    return root;
}

Node* predecessor(Node *root){ 
    //前驱就是左子树的最右节点
    root = root->lchild;
    while(root->rchild) root = root->rchild;
    return root;
}

void clearBST(Node* root){
    if(root == NULL) return ;
    if(root->lchild) clearBST(root->lchild);
    if(root->rchild) clearBST(root->rchild);
    free(root);
    return;
}

Node* erase(Node *root, int key){
    //既可以判断开始的root传入是否为空,又可以是递归到末尾发现找不到返回
    if(root == NULL) return root; 
    if(key < root->key) root->lchild = erase(root->lchild, key);
    else if(key > root->key) root->rchild = erase(root->rchild, key);
    else{
        if(!root->lchild && !root->rchild) {
            free(root);
            return NULL;
        }
        else if(!root->lchild || !root->rchild){
            Node *temp = root->lchild ? root->lchild : root->rchild;
            // clearNode(root); 不能这样用这是清楚以这个为根的整颗子树
            free(root);
            return temp;
        }
        else{
            //它的前驱一定 出度 <= 1，因为它不可能还有右子树
            Node *temp = predecessor(root);
            root->key = temp->key;
            //必须返回给左孩子，如果刚好把左孩子删除，那整个左子树就会不见了
            root->lchild = erase(root->lchild, temp->key); //删除前驱，从根的左子树开始
        }
    }
    return root;
}


#define KEY(a) (a ? a->key : -1)
void output(Node* root){
    if(root == NULL) return ;
    printf("(%d,  %d,  %d)\n",
        KEY(root),
        KEY(root->lchild), 
        KEY(root->rchild));

    output(root->lchild);
    output(root->rchild);
    return;
}

void in_order(Node *root){
    if(root == NULL) return;
    in_order(root->lchild);
    printf("%d  ", root->key);
    in_order(root->rchild);
    return;
}

int main(){
    srand(time(0));
    Node *root = NULL; 
    int x;
#define MAX_OP 10
    for(int i = 0; i < MAX_OP; i++){
        int key = rand() % 100;
        printf("insert %d  to BST\n", key);
        root = insert(root, key);
    }
#undef  MAX_OP
    output(root);
    printf("The inorder of BTS is: \n");
    in_order(root);
    printf("\n");
    printf("Enter the key you wanna erase: ");
    while(~scanf("%d", &x)){
        printf("erase %d in BST\n", x);
        erase(root, x);
        in_order(root); 
        printf("\n");
        printf("Enter the key you wanna erase: ");
    }
    clearBST(root);
    return 0;
}