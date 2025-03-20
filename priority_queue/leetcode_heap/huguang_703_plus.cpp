/*************************************************************************
    > File Name: huguang_703_plus.cpp
    > Author: athur lee
    > Mail: ilovekechunrui@gmail.com
    > Created Time: 2025-03-20 21:35:11
    > Description: 胡光解法的更加简化版
************************************************************************/

class KthLargest {
    typedef pair<int,int> PII;
    int tot, k;
    set<PII> s;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for(auto x: nums)
        add(x);

        return ;
    }
    
    int add(int val) {
     
         s.insert(PII(val,tot++));
        
        if(s.size() > this->k) s.erase(s.begin());

        return s.begin()->first;
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */