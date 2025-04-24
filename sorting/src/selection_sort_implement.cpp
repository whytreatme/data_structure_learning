#include<cstdio>
#include<cstdlib>
#include "sort_test.h"

void selection_sort(int* arr, int l, int r){
    for(int i = l; i < r - 1; i++){
        int ind = i;
        for(int j = ind + 1 ; j < r ; j++)
            if(arr[ind] > arr[j]) ind = j;
        
        swap(arr[ind] , arr[i]);
    }
    return ;
}

int main(){
    int* arr = getRandData(SMALL_DATA_N);
    TEST(selection_sort, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}