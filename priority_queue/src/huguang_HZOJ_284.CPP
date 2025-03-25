/*************************************************************************
	> File Name: 9.HZOJ-284.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

 /*#include <iostream>
 #include <cstdio>
 #include <cstdlib>
 #include <queue>
 #include <stack>
 #include <algorithm>
 #include <string>
 #include <map>
 #include <set>
 #include <vector>
 using namespace std;
 
 struct Data {
     Data(int p, int d) : p(p), d(d) {}
     int p, d;
     bool operator<(const Data &obj) const {
         if (d != obj.d) return d < obj.d;
         return p > obj.p;
     }
 };
 
 typedef pair<int, int> PII;
 
 int main() {
     int n;
     cin >> n;
     vector<Data> arr;
     set<PII> s;
     for (int i = 0, p, d; i < n; i++) {
         cin >> p >> d;
         arr.push_back(Data(p, d));
     }
     sort(arr.begin(), arr.end());//构造一个小顶堆
     for (int i = 0; i < n; i++) {
         cout << "Now i is "<< i <<",  and arr[i].d is " << arr[i].d 
         << ",  arr[i].p is "<<arr[i].p << endl;
         //s.size()实际上是第几个决定卖出
         if (arr[i].d > s.size()) {//把元素一个个插入set中
             s.insert(PII(arr[i].p, i));//合法插入一个就多一天
         } else {
             if (arr[i].p > s.begin()->first) {//如果相等就是冲突了，那就把之前排好的最小利润的给换掉
                 s.erase(s.begin());     //相当于是把之前最小利润的那天给换掉了
                 s.insert(PII(arr[i].p, i));
             }
         }
     }
     int ans = 0;
     for (auto x : s) {
         ans += x.first;
     }
     cout << ans << endl;
     return 0;
 }
/*************************************************************************
    > File Name: 我的实现算法
    > Author: arthur lee
    > Mail: your_email
    > Created Time: 2025-03-25 13:05:02
    > Description: 以下是我的实现代码
************************************************************************/

 #include <queue>
#include <iostream>
#include <set>
#include <vector>
#include <utility> // 必须包含 pair 的头文件

using namespace std;

typedef pair<int, int> PII;

int max_profit(int total, int para[]) {
    // 创建一个比较器，按照 'deadline' 升序，若相同则按 'profit' 降序
    auto cmp = [](const PII& a, const PII& b) {
        if (a.second != b.second) {
            return a.second > b.second; // 按 'deadline' 升序，截止日期小顶堆
        } else {
            return a.first < b.first;   // 若 'deadline' 相同，则按 'profit' 降序
        }//日期相同，则利润大顶堆
    };
    
    // 创建优先队列（最小堆）
    priority_queue<PII, vector<PII>, decltype(cmp)> amount(cmp);

    // 将所有任务放入优先队列
    for (int i = 0; i < total * 2; i += 2) {
        amount.push({para[i], para[i + 1]}); // {profit, deadline}
    }

    long long all = 0; // 改为 long long 来处理大数
    int days = 0;      // 当前商品的卖出顺序
    
    set<int> s;

    // 处理任务
    while (!amount.empty()) {
        // 获取堆顶的任务
        cout << "Now the profit is " << amount.top().first 
                << "  Now the dealine is " << amount.top().second <<endl;
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
    int num;
    cin >> num; // 输入商品数
    int* pair = new int[num * 2];
    
    // 输入每个商品的利润和截止日期
    for (int i = 0; i < num * 2; ++i) {
        cin >> pair[i];
    }
    
    // 输出最大利润
    cout << max_profit(num, pair) << endl;
    
    // 释放动态分配的内存
    delete[] pair;
    return 0;
}
 