#include<cstdio>
#include<cstdlib>
#include"sort_test.h"

int* buff;
void merge_sort(int* arr, int l, int r){
    if(r - l <= 1)return;
    int mid = (l + r) / 2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid, r);
    int k = 0, p1 = l, p2 = mid;
    while(p1 < mid || p2 < r){
        if((p1 < mid) && (p2 >= r || arr[p1] <= arr[p2])){
            buff[k++] = arr[p1++];
        }else{
            buff[k++] = arr[p2++];
        }
    }
    for(int i = l; i < r; i++){
        arr[i] = buff[i - l];
    }
    return;
}

int main(){
    buff = (int*)malloc(sizeof(int) *  BIG_DATA_N);
    int* arr_s = getRandData(SMALL_DATA_N);
    int* arr_b = getRandData(BIG_DATA_N);
    TEST(merge_sort, arr_s, SMALL_DATA_N);
    TEST(merge_sort, arr_b, BIG_DATA_N);
    free(arr_b);
    free(arr_s);
    free(buff);
    return 0;
}