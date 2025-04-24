#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"sort_test.h"
#include<cassert>

//我初始的错误版本，有严重的数组越界的问题
/*void insert_sort(int* arr, int l, int r){// l是数组的开头，r是数组的结尾
    for(int i = l; i < r ; i++){ 
        int  j = i + 1;  
        while(arr[j] < arr[j - 1] && j >= l) {
            assert(j - 1 < l || j < l);
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
 }*/

void insert_sort(int* arr, int l, int r){
        for(int i = l + 1; i < r  ; i++){
            int  j = i ;
            while(j > l && arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
                j--;
            }
        }
        return;
}

void unguarder_insert_sort(int* arr, int l, int r){//无监督插入排序优化
    int ind = l;
    for(int i = ind + 1; i < r; i++){
        if(arr[i] < arr[ind]) ind = i;
    }
    while(ind > l){
        swap(arr[ind], arr[ind - 1]);
        ind--;
    }

    for(int i = l + 1; i < r  ; i++){
        int  j = i ;
        while(arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
    return;
}

int main(){
    int* arr=getRandData(SMALL_DATA_N*6);
    TEST(insert_sort,arr,SMALL_DATA_N*6);
    TEST(unguarder_insert_sort,arr,SMALL_DATA_N*6);
    free(arr);
    return 0;
}