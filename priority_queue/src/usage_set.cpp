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


int main(){
    test1();




    return 0;
}