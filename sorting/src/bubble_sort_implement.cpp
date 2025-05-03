#include<cstdlib>
#include<cstdio>
#include"sort_test.h"

void bubble_sort(int* arr, int l, int r){
    int n = r - l;
    for(int i = 0; i < n - 1; i++){
        int ind = l, cnt = 0;
        for(int j = 1; j < n - i; j++){
            if(arr[ind] > arr[j]){
                swap(arr[ind], arr[j]);
                cnt += 1;
            }
            ind = j;
        }
        if(cnt == 0)break;
    }
    return;
}


void display(int* arr, int n){
    for(int i = 0; i < n ; i++)
        printf("%d " , arr[i]);
    printf("\n");

}

int main(){
    int* arr = getRandData(SMALL_DATA_N);
    TEST(bubble_sort, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}