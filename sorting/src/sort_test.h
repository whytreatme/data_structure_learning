/*************************************************************************
    > File Name: sort_test.h
    > Author: arthur lee
    > Mail: ilovekechunrui@gmail.com
    > Created Time: 2025-04-16 20:42:02
    > Description: 文件的功能描述
************************************************************************/

#ifndef SORT_TEST_H
#define SORT_TEST_H

#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cstdio>

#define SMALL_DATA_N 5000
#define BIG_DATA_N  10000000

void __init_Rand__() {
    printf("init rand\n");
    srand(time(0));
}

bool check(int arr[], int l, int r){
        for(int i = l + 1; i < r ; i++)
            if(arr[i] < arr [i - 1]) return false;
        
        return true;
}

int* getRandData(int n){
    __init_Rand__();
    int* arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        arr[i] = rand() % 10000;
    }
    return arr;
}

#define TEST(func, arr, n){\
    printf("TEST: %s ", #func);\
    int* temp = (int *)malloc(sizeof(int) * n);\
    memcpy(temp, arr, sizeof(int) * n);\
    long long begin = clock();\
    func(temp, 0, n);\
    long long end = clock();\
    if(check(temp, 0, n)){\
        printf(" OK\t");\
    }  else{\
        printf(" failed\t");\
    }\
    printf(" %d items %lld ms\n", n, 1000 * (end - begin) / CLOCKS_PER_SEC);\
    free(temp);\
}

#define swap(a, b){\
    __typeof(a) __c = (a);\
    (a) = (b);\
    (b) = __c;\
}
#endif