#include<cstdlib>
#include<cstdio>
//二分算法重要的不是算法本身，是算法的思想

void output(int* arr, int n, int ind = -1){
    int len = 0;
    for(int i = 0; i < n; i++){
        len += printf("%4d", i);
    }
    printf("\n");
    for(int i = 0; i < len; i++) printf("-");
    printf("\n");
    for(int i = 0; i < n; i++){
        if(i == ind) printf("\033[1;32m");
        printf("%4d", arr[i]);
        if (i == ind) printf("\033[0m");
    }
    printf("\n");
    return;
}

/*   这是一个个人所得税的起征函数，[0,3000]部分征3%的税
     (3000 12000]部分征 10%的税依次类推
*/
#define min(a, b) ((a) < (b) ? (a) : (b))
double f(double x){
    if(x >= 0) x -= min(x, 3000) * 0.03;
    if(x > 3000) x -= (min(x, 12000) - 3000) * 0.1;
    if(x > 12000) x -= (min(x, 25000) - 12000) * 0.2;
    if(x > 25000) x -= (min(x, 35000) - 25000) * 0.25;
    if(x > 35000) x -= (min(x, 55000) - 35000) * 0.3;
    if(x > 55000) x -= (min(x, 80000) - 55000) * 0.35;
    if(x > 80000) x -=  (x - 80000) * 0.45;
    return x;

}
int binary_search(int* arr, int n, int x){
    int head = 0, tail = n - 1, mid;
    while(head <= tail){
        mid = (head + tail) / 2;
        printf("[%d, %d], mid = %d, arr[%d] = %d\n", 
            head, tail, mid,
            mid, arr[mid]
        );
        if(arr[mid] == x) return mid;
        if(arr[mid] > x) tail = mid - 1;
        if(arr[mid] < x) head = mid + 1;
    }
    return -1;
}
#define EXP 1e-4
double binary_algorithm(double y){
    //这个问题可以用二分思想求解，因为：
    //1）征税问题是单调的
    //2) f(x) = y 易求解，但是有y难求解x
    double head = 0, tail = 1000000, mid;
    while(tail - head >= EXP){
        mid = (head + tail) / 2.0 ;
       printf("[%lf, %lf], mid = %lf, f[%lf] = %lf\n", 
            head, tail, mid,
            mid, f(mid) //这里体现数组与函数都体现映射的思路
        );
        if(f(mid) > y) tail = mid ;
        else head = mid ;
    }
    return head;
}

void test_binary_search(int n){
    int* arr = (int*)malloc(sizeof(int) * n);
    arr[0] = rand() % 10;
    for(int i = 1; i < n; i++) arr[i] = arr[i - 1] + rand() % 10;
    output(arr, n);
    
    int x;
    while(~scanf("%d", &x)){
        if(x == -1) break;
        int ind;
        ind = binary_search(arr, n, x);
        output(arr, n, ind);
    }
    free(arr);
    return;
}

void test_binary_algorithm(){
    printf("\ntest binary algorithm:\n");
    double y;
     while(~scanf("%lf", &y)){
        if(y < 0) break;
        double x = binary_algorithm(y);
        printf("f(%.2lf) = %.2lf\n", x, y);
    }
        return;
}

int main(){
#define MAX_N 10

    test_binary_search(MAX_N);
    //已知税后收入求税前收入
    test_binary_algorithm();
    return 0;
}