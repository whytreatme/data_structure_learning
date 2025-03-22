## heap_295我的代码问题的思考

**先附上我的代码**
```cpp
class  MedianFinder {

private:

priority_queue<int, vector<int>> lp;

priority_queue<int, vector<int>, greater<int>> rp;

int l_diff, r_diff;

public:

MedianFinder() {

this->l_diff = this->r_diff = 0;

return;

}

void  addNum(int  num) {

if(lp.size() == 0) {

lp.push(num);

lp.top();

return;

}

if(num < lp.top()) lp.push(num);

else  rp.push(num);

/*this->l_diff是我和标准答案中最大的差异，其实l_diff和r_diff互为相反数，实际只需要一个就足够了，我使用l_diff来进行堆的调整以及判断中位数在哪里输出，但这就是问题的所在 */
  
this->l_diff = lp.size() - rp.size();

this->r_diff = rp.size() - lp.size();

if(this->l_diff > 1){

rp.push(lp.top());

lp.pop();

this->l_diff -=1;

}

else  if(this->r_diff > 1){

lp.push( rp.top());

rp.pop();

this->r_diff -=1;

}

  

}

double  findMedian() {

if(this->l_diff == 1) return  lp.top();

else  if(this->r_diff == 1) return  rp.top();

else  return (lp.top() + rp.top()) / 2.0;

}

};
```
**附上运行出现错误的测试用例**
![测试用例1](https://i.imgur.com/yNGHIyP.png)
以上例子是我修改了代码之后才通过的例子，主要问题出在这里
```cpp
if(lp.size() == 0) {
//我的l_diff不是实时变化的，在上述例子中，我插入了一个元素就函数返回了，根本没有更新l_diff，而我的中位数输出函数依赖于l_diff的值，在这里根本没有变化，会默认为取两个堆的平均值进行输出
lp.push(num);

lp.top();

return;

}
```
![测试用例2](https://i.imgur.com/WbrVgOd.png)
这个例子也是一样，问题出在
```cpp
/*在插入-1到左堆后，再插入-2进入左堆，此时需要把-1调整到右堆中去，这时问题就出现了，也许l_diff是调整到正常值了，但是并没有改变r_diff的*/
if(this->l_diff > 1){

rp.push(lp.top());

lp.pop();

this->l_diff -=1;

}

else  if(this->r_diff > 1){

lp.push( rp.top());

rp.pop();

this->r_diff -=1;

}
```
通过以上例子我们知道，设置一个变量存储一个在运行时改变的值是不可取的，这需要大量的精力去维护代码，而且增加了出现bug的几率，所以标准代码使用lp.size() - rp.size()直接作为判断堆是否调整，以及中位数选取的依据

本题的思考过程也有值得回味的地方，其实一开始我没有问deep seek的时候，我就已经考虑过构建两个堆，并且一个最大堆，一个最小堆的问题了，但是我当时不知道怎么处理堆的调整平衡问题，这个思路就没有深入思考，并且在这道题上我花费了大量的时间，大概3个小时左右，这其实已经不符合学习的高效原则了，实际应该应该把时间控制在最多一个小时，而且在有bug耗时间的时候不应该熬夜奋战

#### **问题分析**

在实现  `MedianFinder`  类时，我使用了  `l_diff`  和  `r_diff`  来记录  `lp`  和  `rp`  的大小差，但它们的更新逻辑存在问题。具体问题如下：

1.  **冗余变量**：`l_diff`  和  `r_diff`  的值是相反数，只需要一个变量即可。
    
2.  **更新不及时**：在插入新元素后，`l_diff`  和  `r_diff`  的值没有及时更新，导致堆的平衡逻辑和中位数计算错误。
    
3.  **复杂性增加**：`l_diff`  和  `r_diff`  的维护增加了代码的复杂性，且容易引入 bug。
    

#### **问题根源**

-   **`l_diff`  和  `r_diff`  的更新逻辑不够严谨**：在插入新元素后，`l_diff`  和  `r_diff`  的值没有及时更新，导致堆的平衡逻辑和中位数计算错误。
    
-   **冗余变量**：`l_diff`  和  `r_diff`  的值是相反数，只需要一个变量即可。
    

#### **改进措施**

1.  **移除冗余变量**：直接使用  `lp.size()`  和  `rp.size()`  来判断堆的平衡。
    
2.  **简化代码逻辑**：移除  `l_diff`  和  `r_diff`，直接使用堆的大小来判断平衡。
    
3.  **改进调试方法**：通过更小的测试用例和打印日志来快速定位问题。


你提到的 **打印日志** 和 **使用更小的测试用例** 是非常有效的调试方法，尤其是在解决算法问题时。以下是如何在 LeetCode 题目中实现这些调试方法的详细说明：

---

### 1. **打印日志**
在 LeetCode 中，虽然没有专门的日志功能，但你可以通过 **标准输出（`std::cout` 或 `printf`）** 来打印日志信息。这些输出会在运行代码时显示在控制台中，帮助你跟踪变量的变化和代码的执行流程。

#### （1）**打印日志的步骤**
1. 在代码的关键位置插入 `std::cout` 或 `printf` 语句，输出变量的值或执行状态。
2. 运行代码，观察控制台输出，分析问题。

#### （2）**示例代码**
以下是一个示例，展示如何在 `MedianFinder` 类中打印日志：

```cpp
#include <queue>
#include <vector>
#include <iostream> // 包含 std::cout

class MedianFinder {
private:
    std::priority_queue<int> lp; // 最大堆，存储较小的一半
    std::priority_queue<int, std::vector<int>, std::greater<int>> rp; // 最小堆，存储较大的一半

public:
    MedianFinder() {}

    void addNum(int num) {
        std::cout << "Adding number: " << num << std::endl;

        // 将新元素插入到合适的堆
        if (lp.empty() || num < lp.top()) {
            lp.push(num);
            std::cout << "Pushed to lp. lp.size(): " << lp.size() << ", rp.size(): " << rp.size() << std::endl;
        } else {
            rp.push(num);
            std::cout << "Pushed to rp. lp.size(): " << lp.size() << ", rp.size(): " << rp.size() << std::endl;
        }

        // 平衡两个堆的大小
        if (lp.size() > rp.size() + 1) {
            std::cout << "Moving from lp to rp. lp.top(): " << lp.top() << std::endl;
            rp.push(lp.top());
            lp.pop();
        } else if (rp.size() > lp.size() + 1) {
            std::cout << "Moving from rp to lp. rp.top(): " << rp.top() << std::endl;
            lp.push(rp.top());
            rp.pop();
        }

        std::cout << "After balancing. lp.size(): " << lp.size() << ", rp.size(): " << rp.size() << std::endl;
    }

    double findMedian() {
        std::cout << "Finding median. lp.size(): " << lp.size() << ", rp.size(): " << rp.size() << std::endl;

        if (lp.size() > rp.size()) {
            return lp.top();
        } else if (rp.size() > lp.size()) {
            return rp.top();
        } else {
            return (lp.top() + rp.top()) / 2.0;
        }
    }
};
```

#### （3）**运行结果**
假设输入为 `[1, 2, 3]`，控制台输出可能如下：
```
Adding number: 1
Pushed to lp. lp.size(): 1, rp.size(): 0
After balancing. lp.size(): 1, rp.size(): 0

Adding number: 2
Pushed to rp. lp.size(): 1, rp.size(): 1
After balancing. lp.size(): 1, rp.size(): 1

Adding number: 3
Pushed to rp. lp.size(): 1, rp.size(): 2
Moving from rp to lp. rp.top(): 2
After balancing. lp.size(): 2, rp.size(): 1

Finding median. lp.size(): 2, rp.size(): 1
```

通过日志输出，你可以清楚地看到每次插入新元素后堆的变化，以及堆的平衡逻辑是否正确。
**以下是力扣日志信息输出**
![日志信息](https://i.imgur.com/jyVI6Cx.png)

---

### 2. **使用更小的测试用例**
在调试过程中，使用更小的测试用例可以帮助你快速定位问题。以下是如何设计和使用更小的测试用例：

#### （1）**设计测试用例**
- 从简单的输入开始，逐步增加复杂性。
- 例如：
  1. 输入 `[1]`，检查中位数是否正确。
  2. 输入 `[1, 2]`，检查中位数是否正确。
  3. 输入 `[1, 2, 3]`，检查中位数是否正确。

#### （2）**示例测试用例**
以下是一些简单的测试用例：

```cpp
int main() {
    MedianFinder mf;

    // 测试用例 1
    mf.addNum(1);
    std::cout << "Median after adding 1: " << mf.findMedian() << std::endl;

    // 测试用例 2
    mf.addNum(2);
    std::cout << "Median after adding 2: " << mf.findMedian() << std::endl;

    // 测试用例 3
    mf.addNum(3);
    std::cout << "Median after adding 3: " << mf.findMedian() << std::endl;

    return 0;
}
```

#### （3）**运行结果**
```
Median after adding 1: 1
Median after adding 2: 1.5
Median after adding 3: 2
```

通过更小的测试用例，你可以快速验证代码的正确性，并逐步定位问题。

---

### 3. **总结**
- **打印日志**：通过 `std::cout` 或 `printf` 输出变量的值和执行状态，帮助跟踪代码的执行流程。
- **使用更小的测试用例**：从简单的输入开始，逐步增加复杂性，快速定位问题。


