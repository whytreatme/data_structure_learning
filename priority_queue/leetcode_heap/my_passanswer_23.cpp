/*************************************************************************
    > File Name: my_passanswer_23.cpp
    > Author: arthur lee
    > Mail: ilovekechunrui@gmail.com
    > Created Time: 2025-03-23 11:01:35
    > Description: 文件的功能描述
************************************************************************/

/*在这段代码下面的那段被注释掉的代码是我最开始的做法，思路其实和能通过的代码一致，但是在实现细节上
我做得不是很晚上，我对于C++的使用还是不够熟练，并且存在可以化简的逻辑*/
#include <vector>
#include <queue>

using namespace std;


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;

        // 检查链表是否全部为空
        bool all_empty = true;
        for (auto x : lists) {
            if (x) {
                all_empty = false;
                break;
            }
        }
        if (all_empty) return nullptr;

        // 定义最小堆
        typedef pair<int, int> PII;
        auto cmp = [](const PII& a, const PII& b) { return a.first > b.first; };
        priority_queue<PII, vector<PII>, decltype(cmp)> min_heap(cmp);

        // 将所有链表的头节点插入堆中
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i]) {
                min_heap.push({lists[i]->val, i});
            }
        }

        ListNode* dummy = new ListNode(); // 虚拟头节点
        ListNode* head = dummy;

        // 合并链表
        while (!min_heap.empty()) {
            auto minNode = min_heap.top();
            min_heap.pop();

            int val = minNode.first;
            int idx = minNode.second;

            // 构建结果链表
            head->next = new ListNode(val);
            head = head->next;

            // 将最小值所属链表的下一个节点插入堆中
            if (lists[idx] && lists[idx]->next) {
                lists[idx] = lists[idx]->next;
                min_heap.push({lists[idx]->val, idx});
            }
        }

        return dummy->next;
    }
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 
 /*#include<vector>
 #include<queue>
 using namespace std;
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())return nullptr;
        int flag = 0; //用于标记数组中的链表是否全部为空
        for(auto x:lists)
            if(x != nullptr){
                flag = 1;
                break;
            }
        if(flag == 0) return nullptr;//链表都为空

        ListNode* head = new ListNode();
        ListNode* real_head = head;
        typedef pair<int,int> PII;
        priority_queue<int, std::vector<PII>, std::greater<int>> min_heap;
        //该用优先队列
        do{
            int i = 0;
            for(auto x: lists){
                if(x != nullptr){//如果链表不为空就进入堆中
                   min_heap.push(x->val,i);//对应的值入堆，并记录对应的数组下标
                }
                i++;
            }
            head->val = min_heap.top()->first;
            head->next = new ListNode();//每次头部指针都存当前的最小值
            head = head->next;//构建下一个节点
            lists[min_heap.top()->second] =  lists[min_heap.top()->second]->next;
            min_heap.pop();//将当前最小值所属的链表推到到下一位，并且出堆
        }while(min_heap.size()!= 0);
        
        return real_head;
    }
};*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 
 #include<vector>
 #include<queue>
 #include<iostream>
 using namespace std;
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())return nullptr;
        int flag = 0; //用于标记数组中的链表是否全部为空
        for(auto x:lists)
            if(x != nullptr){
                flag = 1;
                break;
            }
        if(flag == 0) return nullptr;//链表都为空

        ListNode* head = new ListNode();
        ListNode* real_head = head;
        typedef pair<int,int> PII;
        auto cmp = [](const PII& a, const PII& b){return a.first > b.first;};
        priority_queue<PII, std::vector<PII>, decltype(cmp)> min_heap(cmp);
        //该用优先队列
        int i = 0;
         for(auto x: lists){
                if(x != nullptr){//如果链表不为空就进入堆中
                   min_heap.push(std::make_pair(x->val,i));//对应的值入堆，并记录对应的数组下标
                }
                i++;
            }
        while(min_heap.size()!= 0){
            head->val = min_heap.top().first;
            int index = min_heap.top().second;
            cout << "insert " << min_heap.top().first << " , from list[" << index << "]" <<endl;
            head->next = new ListNode();//每次头部指针都存当前的最小值
            head = head->next;//构建下一个节点
            if(lists[index]->next != nullptr){
                lists[index] =  lists[index]->next;
                min_heap.push(std::make_pair(lists[index]->val,index));
            }
            cout << "new item get in heap!"<<endl;
            min_heap.pop();//将当前最小值所属的链表推到到下一位，并且出堆
            cout << "top of the heap out of!" << endl;
            
        }
        
        return real_head;
    }
};
