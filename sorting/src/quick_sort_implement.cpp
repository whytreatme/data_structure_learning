#include<cstdio>
#include<cstdlib>
#include"sort_test.h"

void quick_sort(int* arr, int l, int r){
    if(l >= r) return;

        int key = arr[l], bp = r - 1, sp = l;
        while(bp != sp){
            if(arr[bp] < key){
                arr[sp] = arr[bp];
                while(sp != bp && arr[sp] <= key){
                    sp++;
                }
                arr[bp] = arr[sp];
            }
            if(bp == sp)break;
            bp--;
        }
        arr[sp] = key;
        quick_sort(arr,l,sp);
        quick_sort(arr, bp + 1, r);
        return;
}


int main(){
    int* arr = getRandData(BIG_DATA_N);
    TEST(quick_sort, arr, BIG_DATA_N);
    free(arr);
    return 0;
}