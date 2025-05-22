#include<algorithm>//sort方法包含在这个头文件中
#include<cstring>
#include<vector>
#include<iostream>
#include"sort_test.h"

using namespace std;

struct Data{
    int x,y;
};

void output(int* arr, int n, const char* s = "arr");
template<typename T>
void output(vector<T>& arr);

ostream& operator<<(ostream& os, const Data& da){
       return os << "(" << da.x << ", " << da.y << ")";
}

void test1(){
    // sort array
    printf("sort array:\n");
    int* arr = getRandData(10);
    output(arr, 10);
    sort(arr, arr + 10); //[)
    output(arr, 10);
    sort(arr, arr + 10, greater<int>());
    output(arr, 10);
    free(arr);
}

void test2(){
     // sort vector
     printf("sort vector:\n");
     vector<int> arr;
     for(int i = 0; i < 10; i++)arr.push_back(rand() % 10000);
     output(arr);
     sort(arr.begin(), arr.end());
     output(arr);
     sort(arr.begin(), arr.end(), greater<int>());
     output(arr);
     return;
}

bool cmp(const Data& a, const Data& b){
    if(a.x != b.x) return a.x < b.x;
    return a.y > b.y;
}

void test3(){
        printf("\t test my data structure\n");
        vector<Data> arr;
        for(int i = 0; i < 10; i++){
            Data b;
            b.x = rand() % 10, b.y = rand() % 10;
            arr.push_back(b);
        }
        output(arr);
        sort(arr.begin(),arr.end(),cmp);
        output(arr);
        return;
}

void test4(){
    printf("test sort ind: \n");
    int* arr = getRandData(10);
    int* ind = getRandData(10);
    for(int i = 0; i < 10; i++) ind[i] = i;
    output(arr, 10);
    sort(ind, ind + 10, [&](int i, int j) -> bool {
        return arr[i] < arr[j];
    });
    output(arr, 10);
    output(ind, 10, "ind");
    return;
}

int main(){
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void output(int* arr, int n, const char* s){
    printf("%s arr[%d] = ", s, n);
    for(int i = 0; i < n; i++){
            printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

template<typename T>
void output(vector<T>& arr){
    printf("arr[%lu] = ", arr.size());
    for(int i = 0; i < arr.size(); i++){
            cout << arr[i] << " ";
    }
    printf("\n");
    return;
}