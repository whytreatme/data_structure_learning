#include<cstdio>
#include<cstdlib>
#include"sort_test.h"

//这段代码已经是正确的了
void quick_sort(int* arr, int l, int r){
    if(l == r) return; //对于边界情况来说只需要等于就行

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
        quick_sort(arr, l, sp);
        quick_sort(arr, bp + 1, r);
        return;
}

void quick_sort_change(int* arr, int l, int r){
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

void quick_sort_v1(int *arr, int l, int r) {
    if (r - l <= 2) {
          if (r - l <= 1) return ;
        if (arr[l] > arr[l + 1]) swap(arr[l], arr[l + 1]);
        return ;
    }
  
    // partition
      /*
        要点有三：1）防止数组越界，hoare分区本质上是没有监督的，并且基准值也是在排序的范畴，
        这点和挖坑法不同，第一步就是把基准值调整到右指针第一次指向小于基准值的位置，
        其后的每一步只是在按基准值消除逆序对个数，但不是完全消除
        2）防止死循环，每交换完一部，就要把两个指针推进下去，不同能重复处理交换过的元素，这会导致死循环
        3）漏排序和重排序，但是我暂时还没遇到
    */
    int x = l, y = r - 1, z = arr[l];
    do {
        while (arr[x] < z) ++x;//不能放过基准值
        while (arr[y] > z) --y;
      // printf("before swap: x = %d, arr[x] = %d, y = %d, arr[y] = %d\n",x, arr[x], y, arr[y]);
        if (x <= y) {
            swap(arr[x], arr[y]);
            ++x, --y;
          // printf("after swap: x = %d, arr[x] = %d, y = %d, arr[y] = %d\n",x, arr[x], y, arr[y]);
        }
    } while (x <= y);    
    quick_sort_v1(arr, l, x);
    quick_sort_v1(arr, x, r);
    return ;
}

void quick_sort_my_hoare(int* arr, int l, int r){ //我的hoare分区版本
        if(r - l <=  2){
           if(r - l <= 1)return;/*边界情况只需要这一句就好了，所有的情况缩到最简
                                  就是这样一种情况，但是不可以r - l <= 1,因为挖坑法和
                                  hoare分区的实现不同，hoare分区要求要交换，它不存在
                                  r - 1,不会缩到 r == l这种情况，除非原数组开始就为空*/
            if(arr[l] > arr[l + 1])swap(arr[l], arr[l + 1]);
            return;
        }
        
        int pivot = arr[l], sp = l - 1, bp = r ;
        while(true){
            do{++sp;}while(arr[sp] < pivot);
            do{--bp;}while(arr[bp] > pivot);
            if(sp > bp)break; 
            swap(arr[sp], arr[bp]);
        } 
        quick_sort_my_hoare(arr, l, sp);
        quick_sort_my_hoare(arr, sp, r);
        return;
}

int three_point_select(int a, int b, int c){
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    return b;
}

void quick_sort_my_hoare_v2(int* arr, int l, int r){ 
    if(r - l <=  2){
       if(r - l <= 1)return;
        if(arr[l] > arr[l + 1])swap(arr[l], arr[l + 1]);
        return;
    }
    
    int  sp = l - 1, bp = r ;
    int pivot =three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
    while(true){
        do{++sp;}while(arr[sp] < pivot);
        do{--bp;}while(arr[bp] > pivot);
        if(sp > bp)break; 
        swap(arr[sp], arr[bp]);
    } 
    quick_sort_my_hoare(arr, l, sp);
    quick_sort_my_hoare(arr, sp, r);
    return;
}

void quick_sort_my_hoare_v3(int* arr, int l, int r){ //我的hoare分区版本
    if(r - l <=  2){
        if(r - l <= 1)return;
         if(arr[l] > arr[l + 1])swap(arr[l], arr[l + 1]);
         return;
     }
     
    while(r > l){
       
         int  sp = l , bp = r - 1;
         int pivot =three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
        // printf("arr[l] = %d, arr[r - 1] = %d, arr[(l + r) / 2] = %d\n",arr[l], arr[r - 1], arr[(l + r) / 2]);
         while( sp <= bp){
            while(arr[sp] < pivot) ++sp;
            while(arr[bp] > pivot) --bp;
             if(sp > bp)break; 
             else{
                swap(arr[sp], arr[bp]);
                ++sp, --bp;
             }
         } 
         quick_sort_my_hoare_v3(arr, l, sp);
         l = sp;
    }
    return;
}

void display(int* arr, int n){
    for(int i = 0; i < n ; i++)
        printf("%d " , arr[i]);
    printf("\n");

}

int main(){
    int* arr_b = getRandData(BIG_DATA_N);
    int* arr_s = getRandData(SMALL_DATA_N);
    //int* arr_test = new int[3]{16, 1, 29};
   // TEST(quick_sort, arr_b, BIG_DATA_N);
    //TEST(quick_sort, arr_s, SMALL_DATA_N);
    //TEST(quick_sort_change, arr_b, BIG_DATA_N);
    //TEST(quick_sort_change, arr_s, SMALL_DATA_N);
   // TEST(quick_sort_huguang, arr_b, BIG_DATA_N);
    //TEST(quick_sort_huguang, arr_s, SMALL_DATA_N);
    //TEST(quick_sort_v1, arr_b, BIG_DATA_N);
    TEST(quick_sort_my_hoare, arr_b, SMALL_DATA_N);
    TEST(quick_sort_my_hoare, arr_b, BIG_DATA_N);
    //TEST(quick_sort_my_hoare_v2, arr_b, BIG_DATA_N);
    //TEST(quick_sort_my_hoare_v3, arr_b, BIG_DATA_N);
    free(arr_b);
    free(arr_s);
   // quick_sort_my_hoare_v3(arr_test, 0, 3);
   // display(arr_test, 3);
   // delete[] arr_test;
    return 0;
}