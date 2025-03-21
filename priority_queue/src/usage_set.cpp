#include<iostream>
#include<set>
#include<vector>

using namespace std;
void test1(){
    cout << "set base usage :" << endl;
    set<int> s;
    cout << s.size() << endl;
    s.insert(3);
    cout << s.size() << endl;
    s.insert(4);
    cout << s.size() << endl;
    s.insert(2);
    return;

}

void test2(){
    cout << "set item unique feature: " << endl;
    set<int> s;
    cout << s.size() << endl;
    s.insert(3);
    cout << s.size() << endl;
    s.insert(4);
    cout << "insert 4 : " << s.size() << endl;
    s.insert(4);
    cout << "insert 4 : " << s.size() << endl;
    return;
}

void test3(){
    cout << "set item unique feature2: " << endl;
    typedef pair<int,int> PII;
    set<PII> s;
    int tot = 0;
    cout << s.size() << endl;
    s.insert(PII(3, tot++));
    cout << s.size() << endl;
    s.insert(PII(4, tot++));
    cout << "insert 4 : " << s.size() << endl;
    s.insert(PII(4, tot++));
    cout << "insert 4 : " << s.size() << endl;
    return ;
}

void test4(){
    cout << "foreach set item : " << endl;
    typedef pair<int, int> PII;
    set<PII> s;
    int tot = 0;
    s.insert(PII(4, tot++));
    s.insert(PII(3, tot++));
    s.insert(PII(4, tot++));
    for (auto x : s) {
        cout << "(" << x.first << ", " << x.second << ")" << endl;
    }//输出结果证明是一个小顶堆，按照第一个字段的大小排序
    return ;
}

void test5(){
        cout << "set replace heap : " << endl;
        typedef pair<int, int> PII;
        int tot = 0;
        set<PII> s;
        for (int i = 0; i < 10; i++) {
            s.insert(PII(rand() % 20, tot++)); // push
        }
        for (int i = 0; i < 4; i++) {
            cout << "s.begin() = " << s.begin()->first << endl;
            s.erase(s.begin()); // pop
            cout << "pop heap" << endl;//不断出栈元素的最小值
        }
        return ;
}

int main(){
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}