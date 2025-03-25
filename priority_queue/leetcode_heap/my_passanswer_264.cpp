/*************************************************************************
    > File Name: my_passanswer_264.cpp
    > Author: Arthur lee
    > Mail: ilovekechunrui@gmail.com
    > Created Time: 2025-03-24 20:25:16
    > Description: 文件的功能描述
************************************************************************/
//代码是我写的，但是思路不是我的
#include<queue>
#include<vector>


class Solution {
private:
 std::priority_queue<long, vector<long>, std::greater<long>> u_tree;
 int num;
 int k = 0;

public:
    Solution(){
        u_tree.push(1);
    }

    int nthUglyNumber(int n) {
        long n_ug = 0;
        this-> num = n;
        /*船长这段用了switch case*/
        while(this->k < this->num){
            if(u_tree.top() % 5 == 0){
                u_tree.push(u_tree.top()*5);
            } 
            else if(u_tree.top() % 3 == 0){
                u_tree.push(u_tree.top()*3);
                u_tree.push(u_tree.top()*5);
            }
            else {
                u_tree.push(u_tree.top()*3);
                u_tree.push(u_tree.top()*5);
                u_tree.push(u_tree.top()*2);
            }
            n_ug = u_tree.top();
            u_tree.pop();
            this->k++;
        }
        
        return n_ug;
    }
};