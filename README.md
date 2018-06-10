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
//阶乘的递归算法
unsigned int factorial(unsigned int n){
  if(n == 0)
    return 1;
  else
    return n*factorial(n-1);
}
//阶乘的非递归算法
unsigned int factorialStack2(unsigned int n){
  Stack S;
  StackInit(S);
  while(n > 0){
    Push(S,n);
    n = n - 1;
  }
  n = 1;
  while(StackLength(S) > 0){
    n = n*Pop(S);
  }
  return n;
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
