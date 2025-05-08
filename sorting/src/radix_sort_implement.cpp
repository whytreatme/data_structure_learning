#include<cstdio>
#include<cstdlib>
#include"sort_test.h"

#define K 65536
void radix_sort(int* arr, int l, int r){

    int* cnt = (int*)malloc(sizeof(int) * K);
    int* temp = (int*)malloc(sizeof(int) * (r - l));
    //round 1
    memset(cnt, 0, sizeof(int) * K);
    for(int i = l; i < r; i++) cnt[arr[i] % K] += 1;
    for(int i = 1; i < K; i++) cnt[i] += cnt[i - 1];
    for(int i = r - 1; i >= l; i--) temp[--cnt[arr[i] % K]] = arr[i];
    memcpy(arr + l, temp, sizeof(int) * (r - l));
     //round 2
     memset(cnt, 0, sizeof(int) * K);
    for(int i = l; i < r; i++) cnt[arr[i] / K] += 1;
    for(int i = 1; i < K; i++) cnt[i] += cnt[i - 1];
    for(int i = r - 1; i >= l; i--) temp[--cnt[arr[i] / K]] = arr[i];
    memcpy(arr + l, temp, sizeof(int) * (r - l));
    return;
}

#define K 65536  // 基数 (2^16)

//以下是可以处理负数的版本
void all_radix_sort(int* arr, int l, int r) {
    int* cnt = (int*)malloc(sizeof(int) * K);
    int* temp = (int*)malloc(sizeof(int) * (r - l));

    // === 关键修改1：处理负数 ===
    // 第一轮：对低16位排序（需将负数映射到正数范围）
    memset(cnt, 0, sizeof(int) * K);
    for (int i = l; i < r; i++) {
        // 将负数转换为无符号数后再取模，确保分桶正确
        unsigned int num = (unsigned int)(arr[i] ^ 0x80000000);  // 符号位翻转,按位异或与只翻转符号位
        cnt[num % K]++;
    }
    for (int i = 1; i < K; i++) cnt[i] += cnt[i - 1];
    for (int i = r - 1; i >= l; i--) {
        unsigned int num = (unsigned int)(arr[i] ^ 0x80000000);
        temp[--cnt[num % K]] = arr[i];
    }
    memcpy(arr + l, temp, sizeof(int) * (r - l));

    // 第二轮：对高16位排序（同样处理符号）
    memset(cnt, 0, sizeof(int) * K);
    for (int i = l; i < r; i++) {
        unsigned int num = (unsigned int)(arr[i] ^ 0x80000000);
        cnt[num / K]++;
    }
    for (int i = 1; i < K; i++) cnt[i] += cnt[i - 1];
    for (int i = r - 1; i >= l; i--) {
        unsigned int num = (unsigned int)(arr[i] ^ 0x80000000);
        temp[--cnt[num / K]] = arr[i];
    }
    memcpy(arr + l, temp, sizeof(int) * (r - l));

    free(cnt);
    free(temp);
}
    
int main(){
    int* arr_s = all_getRandData(SMALL_DATA_N);
    int* arr_b = all_getRandData(BIG_DATA_N);
    //TEST(radix_sort, arr_s, SMALL_DATA_N);
    //TEST(radix_sort, arr_b, BIG_DATA_N);
    TEST(all_radix_sort,arr_s,SMALL_DATA_N);
    TEST(all_radix_sort,arr_b,BIG_DATA_N);
    free(arr_s);
    free(arr_b);
    return 0;
}