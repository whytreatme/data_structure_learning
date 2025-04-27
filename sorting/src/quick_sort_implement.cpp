#include<cstdio>
#include<cstdlib>
#include"sort_test.h"
//这段代码已经是正确的了
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

void quick_sort_change(int* arr, int l, int r){
    if((r - l) <= 2){
        if((r - l) <= 1)return;
        if(arr[l] > arr[l + 1]){
            swap(arr[l], arr[l + 1]);
            return;
        }
    } 

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
        quick_sort_change(arr,l,sp);
        quick_sort_change(arr, bp + 1, r);
        return;
}

void quick_sort_huguang(int *arr, int l, int r) {
    if (r - l <= 2) {
        if (r - l <= 1) return ;
        if (arr[l] > arr[l + 1]) swap(arr[l], arr[l + 1]);
        return ;
    }
    // partition
    int x = l, y = r - 1, z = arr[l];
    while (x < y) {
        while (x < y && z <= arr[y]) --y;
        if (x < y) arr[x++] = arr[y];
        while (x < y && arr[x] <= z) ++x;
        if (x < y) arr[y--] = arr[x];
    }
    arr[x] = z;
    quick_sort_huguang(arr, l, x);
    quick_sort_huguang(arr, x + 1, r);
    return ;
}


int main(){
    int* arr_b = getRandData(BIG_DATA_N);
    int* arr_s = getRandData(SMALL_DATA_N);
    TEST(quick_sort, arr_b, BIG_DATA_N);
    TEST(quick_sort, arr_s, SMALL_DATA_N);
    TEST(quick_sort_change, arr_b, BIG_DATA_N);
    TEST(quick_sort_change, arr_s, SMALL_DATA_N);
    TEST(quick_sort_huguang, arr_b, BIG_DATA_N);
    TEST(quick_sort_huguang, arr_s, SMALL_DATA_N);
    free(arr_b);
    free(arr_s);
    return 0;
}