# DSA Review
This repository is to place on file notes on data structure and algorithm.

### Stack Application
> symbol balance
>
> expression calculation
>
>> posfix expression calculation
>>
>> convert infix expression to posfix expression
>>
> function call
>
>> the implementation mechanism of recursion
>>
>> use stack to eliminate recursion
```C
//由于上一个算法会产生过多冗余的递归实例，从而导致计算速度过慢，需要采取一些优化

//Solution A(memoization)：将已计算过的结果制表备查，在程序入口处添加一个对表格的查询语句，只有在没有查询到结果的情况下，才会执行实质的计算。有效地克服刚才的缺点。
//In computing, memoization or memoisation is an optimization technique used primarily to speed up computer programs by storing the results of expensive function calls and returning the cached result when the same inputs occur again

//Solution B：Reverse the direction of calculation: from recursive descent to iterative ascent
//颠倒计算方向：由自顶而下递归，为自底而上迭代
/*            g---⧈
                  ⎮
             ⧈--g~f
             ⎮
             f~g--⧈
                  ⎮
             ⧈--g~f
             ⎮
             f
用f和g分别记忆当前所处的相邻的两级台阶*/
int fib_ascent_cal(int n){
    int f = 0, g = 1; //fib(0), fib(1)
    while (0 < n--){ //复杂度由n控制，与n成线性关系
        g = g + f;
        f = g - f;
    }
    return g;
}
```
>>

### Queue Application
> 排队问题
>
>> 解决主机与外部设备之间速度不匹配的问题(设置数据缓冲区)
>>
>> 解决由多用户引起的资源竞争问题(对提出占用CPU请求的进程按时间先后顺序排成队列)
>>
> 非排队问题
>
>> 使用链式队列打印杨辉三角形
>>
