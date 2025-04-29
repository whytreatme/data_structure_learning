/*************************************************************************
    > File Name: 我的实现算法
    > Author: arthur lee
    > Mail: your_email
    > Created Time: 2025-03-25 13:05:02
    > Description: 以下是我的实现代码
************************************************************************/

 #include <queue>
 #include<ctime>
#include <iostream>
#include <set>
#include <vector>
#include <utility> // 必须包含 pair 的头文件

using namespace std;

typedef pair<int, int> PII;
struct Data{
    Data(int p, int d) : p(p), d(d) {}
    int p, d;
};

int max_profit(int total, vector<Data> para) {
    // 创建一个比较器，按照 'deadline' 升序，若相同则按 'profit' 降序
    auto cmp = [](const PII& a, const PII& b) {
        if (a.second != b.second) {
            return a.second > b.second; // 按 'deadline' 升序，截止日期小顶堆
        } else {
            return a.first < b.first;   // 若 'deadline' 相同，则按 'profit' 降序
        }//日期相同，则利润大顶堆
    };
    
  
    priority_queue<PII, vector<PII>, decltype(cmp)> amount(cmp);

    // 将所有任务放入优先队列
    for (int i = 0; i < total ; i ++) {
        amount.push({para[i].p, para[i].d}); // {profit, deadline}
    }

    long long all = 0; // 改为 long long 来处理大数
    int days = 0;      // 当前商品的卖出顺序
    
    set<int> s;

    // 处理任务
    while (!amount.empty()) {
        // 获取堆顶的任务
      //  cout << "Now the profit is " << amount.top().first 
              //  << "  Now the dealine is " << amount.top().second <<endl;
        if (amount.top().second > days) {
            all += amount.top().first; // 加上当前任务的利润
            s.insert(amount.top().first);
            days++;                    // 增加一天
        }
        else{
                if(amount.top().first > *s.begin()){//如果出现冲突，且新加入元素有利可图
                    all -= *s.begin();//去除当前最小利润
                    all += amount.top().first;//加入新的商品
                    s.erase(s.begin());//去除当前商品
                   
                    s.insert({amount.top().first});//不需要改动days
                } 
        }

        amount.pop(); // 弹出当前任务
    }

    return all; // 返回最大利润
}


int main() {
   /* int num;
    cin >> num; // 输入商品数
    int* pair = new int[num * 2];
    
    // 输入每个商品的利润和截止日期
    for (int i = 0; i < num * 2; ++i) {
        cin >> pair[i];
    }
    
    // 输出最大利润
    cout << max_profit(num, pair) << endl;*/
    srand(time(0));
    #define MAX_NUM 1000
    cout << MAX_NUM << endl;
    vector<Data> arr;
     set<PII> s;
     for (int i = 0, p, d; i < MAX_NUM; i++) {
         p = rand() % 1000 + 1; 
         d = rand() % 1000 + 1;
         cout << p << " " << d <<endl ;
         arr.push_back(Data(p, d));
     }
     int a = max_profit(MAX_NUM,arr);
     cout << "The largest profit is  " << a;
     

    
    // 释放动态分配的内存
    
    return 0;
}
 