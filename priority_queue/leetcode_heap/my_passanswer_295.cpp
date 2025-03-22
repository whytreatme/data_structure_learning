/*************************************************************************
    > File Name: mya_passanswer_295.cpp
    > Author: arthur lee
    > Mail: ilovekechunrui@gmail.com
    > Created Time: 2025-03-22 16:45:43
    > Description: 文件的功能描述
************************************************************************/
#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> lp; // 最大堆，存储较小的一半
    std::priority_queue<int, std::vector<int>, std::greater<int>> rp; // 最小堆，存储较大的一半

public:
    MedianFinder() {}

    void addNum(int num) {
        // 将新元素插入到合适的堆
           if(lp.size() == 0) {
            int a,b;
            lp.push(num);
            a = lp.top();
            return;
        }

         if(num < lp.top()) lp.push(num);
       else  rp.push(num);
       /* if (lp.empty() || num < lp.top()) {
            lp.push(num);
        } else {
            rp.push(num);
        }
        */
        // 平衡两个堆的大小
        if (lp.size() > rp.size() + 1) {
            rp.push(lp.top());
            lp.pop();
        } else if (rp.size() > lp.size() + 1) {
            lp.push(rp.top());
            rp.pop();
        }
    }

    double findMedian() {
        if (lp.size() > rp.size()) {
            return lp.top();
        } else if (rp.size() > lp.size()) {
            return rp.top();
        } else {
            return (lp.top() + rp.top()) / 2.0;
        }
    }
};
/*这段代码是我自己思考出来的，核心逻辑和能通过的代码一样，但是就是有一部分的不同
class MedianFinder {
private:
    priority_queue<int, vector<int>> lp;
    priority_queue<int, vector<int>, greater<int>> rp;
    int l_diff, r_diff;
public:
    MedianFinder() {
        this->l_diff = this->r_diff = 0;
        return;
    }
    
    void addNum(int num) {
        if(lp.size() == 0) {
            lp.push(num);
            lp.top();
            return;
        }
        
       if(num < lp.top()) lp.push(num);
       else  rp.push(num);

       this->l_diff = lp.size() - rp.size();
       this->r_diff = rp.size() - lp.size();
       if(this->l_diff > 1){
        rp.push(lp.top());
        lp.pop();
        this->l_diff -=1;
       }
       else if(this->r_diff > 1){
        lp.push( rp.top());
        rp.pop();
        this->r_diff -=1;
       }

    }
    
    double findMedian() {
        if(this->l_diff == 1) return lp.top();
        else if(this->r_diff == 1) return rp.top();
        else return (lp.top() + rp.top()) / 2.0;
    }
};*/