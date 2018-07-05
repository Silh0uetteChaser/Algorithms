/******************************************************************
 ****************** Author:  atjohore@gmail.com  ******************
 ****************** Date:    2018-2-12           ******************
 ******************************************************************/

#include <iostream>
#define MAXSIZE 10
#define MaxSize 10
using namespace std;

//DSA@Tsinghua
//Strategies: Decrease_and_conquer, Divide_and_conquer
//Paradigms: Iteration, Recursion
//Analysis: Recursion Trace, Recurrence
/*********************************************************************************************************/
//减而治之--Decrease-and-conquer: 为求解一个大规模问题，可以将其划分为两个子问题:其一平凡(退化)，另一规模缩减(单调性)，分别求解子问题，由子问题的解得到原问题的解
//数组求和--linear recursion,每一个递归实例只会产生一个递归实例，递归实例按线性次序排列，因此也叫线性递归。
//Time Complexity T(n) = O(1)*(n+1) = O(n) 单个递归实例自身只需要O(1)时间
//Recurrence: T(n) = T(n-1) + O(1), Base: T(0) = O(1)
int arr_sum_linear_recursion(int A[], int n){
    return
        (n < 1) ?
            0 : arr_sum_linear_recursion(A, n-1) + A[n-1];
}
/*********************************************************************************************************/
//数组倒置，任给数组A[0, n), 将其前后颠倒
void arr_reverse_recursion(int* A, int lo, int hi){
    if(lo < hi)  //问题规模的奇偶性不变，需要两个递归基
    { swap(A[lo], A[hi]); arr_reverse_recursion(A, lo+1, hi-1); }
    else
        return; //base case
}

void arr_reverse_nonrecursion(int* A, int lo, int hi){
    while(lo < hi)
    {swap(A[lo++], A[hi--]);}
}//迭代精简版
/*********************************************************************************************************/
//分而治之--Divide-and-conquer: 为求解一个大规模问题，规模大体相当，分别求解子问题，由子问题的解，得到原问题的解
//数组求和--二分递归法
int arr_sum_binary_recursion(int A[], int lo, int hi){ //区间范围A[lo, hi]
    if(hi == lo)
        return A[lo];
    int mid = (hi + lo) >> 1;
    return arr_sum_binary_recursion(A, lo, mid) + arr_sum_binary_recursion(A, mid+1, hi);
}
//入口形式为sum(A,0,n-1)
//从递推的角度看，为求解sum(A,lo,hi),需递归求解sum(A,lo,mi)和sum(A,mi+1,hi) //2*T(n/2)
//进而将子问题的解累加 O(1) //递归基：sum(A,lo,lo) O(1)
//T(n) = 2*T(n/2) + O(1), T(1) = O(1)
/*********************************************************************************************************/
//Max2:iteration1: find the two biggest elements A[x1] and A[x2] // A[x1] >= A[x2]
//元素比较的次数要尽可能少
void max2(int A[], int lo, int hi, int &x1, int &x2){ //1 < n = hi - lo
    for(int i = lo + 1, x1 = lo; i < hi; i++){ //x1在数组[lo,hi)中扫描, 找出A[x1]
        if (A[x1] < A[i]) x1 = i; //使得x1始终指向数组中最大的元素，确定x1的位置
    }//比较次数 hi - lo - 1 = n - 1
    for(int i = lo + 1, x2 = lo; i < x1; i++){
        if (A[x2] < A[i]) x2 = i; //扫描A[lo,x1)
    }//x1 - lo - 1
    for(int i = x1 + 1; i < hi; i++){
        if (A[x2] < A[i]) x2 = i; //扫描A(x1,hi),找出A[x2]
    }//hi - x1 - 1
}//无论如何，比较次数总是2n-3次

//Max2:改进 维护两个指针，x1,x2分别指向当前最大的元素和次大的元素,在扫描到第i个元素时，将i与x2做比较进而跟x1做比较。
void max2_improved(int A[], int lo, int hi, int &x1, int &x2){
    if (A[x1 = lo] < A[x2 = lo + 1])
        swap(x1,x2);
    for(int i = lo + 2; i < hi; i++)
        if(A[x2] < A[i])
            if(A[x1] < A[x2 = i])
                swap(x1,x2);
}
//best case: 1 + (n-2)*1 = n-1, worst case: 1 + (n-2)*2 = 2n-3

//Max2:递归+分治
//将序列划分为左侧和右侧两部分，递归地求解两个子问题，分别求出左边的最大元素和次大元素以及右边的最大元素和次大元素
void max2_recursion_div_and_conq(int A[], int lo, int hi, int &x1, int &x2){
    if(lo + 3 >= hi){
        return;
    } //T(3) <= 3
    int mi = (lo + hi)/2;
    int x1L, x2L;
    max2_recursion_div_and_conq(A, lo, mi, x1L, x2L);
    int x1R, x2R;
    max2_recursion_div_and_conq(A, mi, hi, x1R, x2R);
    if(A[x1L] > A[x1R]){
        x1 = x1L;
        x2 = (A[x2L] > A[x1R]) ? x2L : x1R;
    }
    else{
        x1 = x1R;
        x2 = (A[x1L] > A[x2R]) ? x1L : x2R;
    }//1 + 1 = 2
} //T(n) = 2*T(n/2) +2 <= 5n/3 - 2 系数从2下降为5/3，保证在最坏情况下
/*********************************************************************************************************/
//动态规划：Dynamic Planning, 通过递归找出算法的本质并给出初步的解后, 再将其等效地转化为迭代的形式
//fib():递归 fib(n) = fib(n-1) + fib(n-2):{0,1,1,2,3,5,8,...}
int fib(int n){
    return (2>n) ? n/*若达到递归基，直接取值*/ : fib(n-1) + fib(n-2);
}
/*********************************************************************************************************/
//迭代
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
/*The time and space complexities for computing fib(n) with dynamic programming are T(n) = O(n), O(1) respectively.
 Subseqence子序列(由序列中若干字符，按原相对次序构成). LCS(Longest Common Subsequence): 最长公共子序列是指两个序列公共子序列中的最长者. 可能同时存在多个LCS，也可能存在二义性(ambiguity)
 The length of the LCS between "program" and "algorithm" is 3.
假设我们的LCS算法返回的是最长公共子序列的长度。
现在考虑一个简单的版本，按照Kent Back的工作流程，首先to make it work.
使用递归：LCS: 递归, 对于序列A[0,n] (长度n+1) 和 B[0,m] (长度m+1), LCS(A, B)无非三种情况
0) 若n = -1，或n = -1，则取作空序列("") //一般当作递归基。
1) 若A[n] = 'X' = B[m], 则取作LCS(A[0, n), B[0, m)) + 'X' //decrease_and_conquer
2) A[n] != B[m], 则在LCS(A[0, n), B[0, m])与LCS(A[0, n], B[0, m))中取最长者 //divide_and_conquer
 
单调性: 无论如何, 每经过一次比对，原问题的规模必可减小，具体地，作为输入的两个序列，至少其一的长度缩短一个单位。最好情况下（不出现第2种情况）下，只需要O(n+m)的时间。但问题在于，（在第2种情况）原问题将分解为两个子问题，更糟糕的是，它们在随后进一步导出的子问题，可能雷同。
 和fib()类似，这里存在大量重复的递归实例(子问题), best case: O(n+m), worst case:C(n, n+m)=C(m, n+m), m=n时，为𝝮(2^n).先后共计出现O(2^n)个
 各子问题，分别对应于A和B的某个前缀组合，因此总共不过O(n*m)种
 
 现在考虑动态规划的策略: 只需要O(n*m)时间即可计算出所有子问题
 为此，只需：
 0)将所有子问题(假想的)列成一张表
 1)颠倒计算方向，从LCS(A[0],B[0])出发，依次计算出所有项。
 */

//有序向量:二分查找

//DSA@UESTC
/*********************************************************************************************************/
/*
 1.1 线性表 Linear List
 //线性表的保序合并操作
*/
//1.1.0 顺序存储结构 Sequential List
struct node{
    int data[MAXSIZE];
    int length;
};
typedef struct node SeqList;
//1.1.1 顺序表的初始化
void SeqListInit(SeqList L){
    L.length = 0;
} //O(1)

//1.1.2 顺序表的求长操作
int SeqListLength(SeqList L){
    return L.length;
} //O(1)

//1.1.3 顺序表的取元素操作
int SeqListGet(SeqList L, int i){
    if(( i >= 0) && (i < L.length)){
        return L.data[i];
    }
    else{
        cout << "invalid value of i" << endl;
        exit(0);
    }
}//O(1)

//1.1.4 顺序表的定位操作(在L中找到第一个和e值相同的元素, 返回索引)
int SeqListLocate(SeqList L, int e){
    int i = 0;
    while((i < L.length) && (L.data[i] != e)){
        i ++;
    }
    if(i < L.length){
        return i;
    }
    else{
        cout << "the value e does not exist in the list" << endl;
        return 0;
    }
    
}//O(n)

//1.1.5 顺序表的求前驱操作 (首先判断e是否为第一个元素，如果不是则返回e的前一个元素；否则返回NULL)
int SeqListPrior(SeqList L, int e){
    int i = SeqListLocate(L,e);
    if(i == 0){
        cout << "The e is the first element and has no predecessor" << endl;
        return NULL;
    }
    else
        return L.data[i-1];
}//O(1)

//1.1.6 顺序表的求后继操作
int SeqListNext(SeqList L, int e){
    int i = SeqListLocate(L, e);
    if(i == L.length - 1){
        cout << "The e is the last element and has no successor" << endl;
        return NULL;
    }
    else
        return L.data[i+1];
}//O(1)

//1.1.7 顺序表的前插操作 （在索引i的位置插入元素e）
void SeqListInsert(SeqList L, int i, int e){
    if(L.length == MAXSIZE){
        cout << "the list is full" << endl;
        exit(0);
    }
    if((i < 0) || (i >= MAXSIZE)){
        cout << "invalid index" << endl;
        exit(0);
    }
    for(int j = L.length - 1; j >= i; j--){
        L.data[j + 1] = L.data[j];
    }
    L.data[i] = e;
    L.length ++;
}//O(n)

//1.1.8 顺序表的删除操作 (删除索引i位置的元素)
void SeqListDel(SeqList L, int i){
    if((i < 0) || (i > L.length - 1)){
        cout << "invalid value of i" << endl;
        exit(0);
    }
    for(int j = i; j <= L.length - 1; j++){
        L.data[j-1] = L.data[j];
    }
    L.length --;
    
}

//1.1.9 顺序表的判空操作
bool IsSeqListEmpty(SeqList L){
    return !L.length;
}

//1.1.10 顺序表的遍历操作
void SeqListTraverse(SeqList L){
    if(IsSeqListEmpty(L)){
        cout << "This is an empty list" << endl;
    }
    else{
        for(int i = 0; i < L.length; i++){
            cout << L.data[i-1] << endl;
        }
    }
}
/*********************************************************************************************************/
//1.2 链式存储结构 Linked List
//Head 指针是单链表头指针 头指针唯一确定一个单链表，习惯上使用头指针代表单链表的名字。链表中的最后一个结点的指针域定义为空指针(NULL)。
//1.2.0 单链表 Linked List(带头节点)
struct Node{
    int data;
    struct Node *next;
};
typedef struct Node LNode;
typedef struct Node *LinkedList; //LinkedList变量类型是指向链表结点的指针类型

//1.2.1 单链表的初始化操作(带头节点) //a->b的含义是 (*a).b
void LinkedListInit(LinkedList L){
    L = (LNode*)malloc(sizeof(LNode));
    if(L == NULL){
        cout << "fail to allocate memory" << endl;
        exit(0);
    }
    L->next = NULL; //对于带头节点的单链表，需要先用malloc函数分配一个类型为LNode的结点空间，并且分配完以后还需要查看空间是否分配成功。
}

//1.2.2 单链表的求长操作(带头结点)
int LinkedListLength(LinkedList L/*L为头指针*/){
    LNode* p; //p是一个当前指针, 初始时p指向链表中的第一个结点，p每向下移动一个结点时，j就+1，直到到达p链表的尾部。注意：对于带头节点的链表，链表的长度不包含头结点。
    p = L->next;
    int j = 0; //j是计数器
    while(p != NULL){
        j ++;
        p = p->next;
    }
    return j;
}
//1.2.3 单链表的取元素操作(带头结点)
LinkedList LinkedListGet(LinkedList L, int i){
    //查找链表中的第i个元素，设定p为当前结点，初始时p指向链表的第一个结点，然后向下移动i次，此时p所指向的元素就是需要查找的第i个元素。
    LNode *p;
    p = L->next;
    while((p != NULL) && (p->data != i)){
        p = p->next;
    }
    return p;
}

//1.2.4 单链表的插入操作，在结点p之前插入一个结点q，插入的结点数据域为e. 对于不带头结点的单链表，p的位置有所不同，插入操作有下面两种情况。
void LinkedListInsert(LinkedList L, LinkedList p, int e){
    //在表头插入: 1）创建了一个新的结点q, 2)将此新结点的数据域赋值为e，并将它的next指针指向第一个结点, 即L, 3）将L修改为指向新的结点q
    //在链表中间插入: 1)创建了一个新的结点q, 2)将此新结点的数据域赋值为e, 并将它的next指针指向p, 3)查找到p的前驱结点pre, 4)将pre的next指针指向新创建的结点q
    LNode* q = (LNode*)malloc(sizeof(LNode)); //创建一个新结点q
    if(q == NULL){
        cout << "memory allocation failed" << endl;
        exit(0);
    }
    
    q->data = e;
    //在表头插入(仅适用于不带头结点的单链表，对于带头结点的单链表，在表头插入和在表的中间插入是一页的)
    if(p == L){ //p指向要插入的结点，p=L说明要插入的结点在表头
        q->next = L;
        L = q;
        exit(0);
    }
    
    //在表的中间插入
    LNode* pre = L;
    while((pre != NULL)&&(pre->next != p)){ //从表头L开始，寻找p的前驱
        pre = pre->next;
    }
    if(pre != NULL){
        q->next = pre->next;
        pre->next = q;
    }
}

//1.2.5 单链表的删除操作，删除链表中的某个元素e，如果出现多次仅删除第一个
void LinkedListDel(LinkedList L, LinkedList p, int e){
    //1)若p是链表中的第一个结点: 删除表中的第一个结点时，需要执行下面两个步骤: 1）将L指向p->next, 2)释放p
    //2)若p是链表中的其他结点: 需要执行下面三个步骤：1) 找到p的前驱结点pre, 2)将pre->next指向p->next, 3)释放p
    LNode* pre = L;
    while((pre != NULL) && (pre->next->data != e)){//寻找p的前驱结点pre{
        pre = pre->next;
    }
    if(p != NULL){//找到需要删除的结点
        if(p == L){//需要删除的是第一个结点
            L = p->next;
        }
        else{//删除的是中间的结点
            pre->next = p->next;
        }
        free(p);
    }
}
//1.2.6 单链表的创建(尾插法)
void LinkedListCreate(LinkedList L, int* a){
    L = (LNode*) malloc(sizeof(LNode));
    if(L == NULL){
        cout << "memory allocation failed" << endl;
        exit(0);
    }
    L->next = NULL;
    LNode* tail = L; //设置一个尾指针，方便插入
    for(int i = 0; i < sizeof(a)/sizeof(int); i++){
        LNode* p = (LNode*) malloc(sizeof(LNode));
        if(p == NULL){
            cout << "memory allocation failed" << endl;
            exit(0);
        }
        p->data = a[i];
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
}
//1.3 广义表 Generalized List
//广义表是线性表的推广
//对于线性表而言，n个元素都是基本的单元素
//广义表中，这些元素不仅可以是单元素也可以是另一个广义表
//例如我们可以将上述的一个二元多项式看成关于x的一元多项式
//P(x, y) = 9x^12y^2 + 4x^12 + 15x^8y^3 - x^8y + 3x^2
//P(x, y) = (9y^2+4)x^12 + (15y^3-y)x^8 + 3x^2
//1.3.0 广义表的结构
typedef struct GNode* GList;
struct GNode{
    int Tag; //可以把这个空间理解成一种类型，也可以理解为另一种类型，区分办法是添加一个标志域: 0表示结点是单元素，1表示结点是广义表
    union{
        int data;
        GList SubList; //子表指针域Sublist与单元素数据域Data复用，即共用存储空间
    }URegion;
    GList Next;
};
/***************************************/
/*        *       Data       *         */
/*  Tag   ********************   Next  */
/*        *      SubList     *         */
/***************************************/

//Remarks: 回顾下Union...Union在C中本质上是一个结构体，用法和struct相似...但多个成员共用一块内存，这个空间的类型可以理解为成员中的某一种...在编译时会选取成员中长度最长的来声明...
union a {
//声明了三个成员，但是长度不一（后面sizeof的结果不同机器结果不同，但double肯定是最长的），于是编译器会选取double的长的作为union a的长度
    int a1;    // sizeof(int) = 4
    float a2;  // sizeof(float) = 8
    double a3; // sizeof(double) = 16
};//在对union成员进行赋值后，要注意使用时一定要调用赋值过的成员
//在调用时用后缀表达式expression.identifier的形式来调用成员:
//a.a1 = xxx; p->a1 = xxx (a是union, p是union的指针)
//多重链表是指链表中的结点可能同时隶属于多个链(多重链表中结点的指针域会有多个，如前面例子包含了Next和SubList两个指针域；但包含两个指针域的链表并不一定是多重链表，比如双向链表不是多重链表。
//Matrix 矩阵 可以用二维数组来表示，但用二维数组表示存在缺陷: 1）数组大小需要事先确定 2）对于稀疏矩阵，将造成大量的存储空间浪费
//采用一种典型的多重链表——十字链表来存储稀疏矩阵 (只存储矩阵非0元素项，结点的数据域: 行坐标Row，列坐标Col，数值Value)，(i,j,aij)，每个结点通过两个指针域，把同行、同列串起来;(行指针(或向右指针)Right);(列指针(或称为向下指针)Down)
typedef struct OLNode{
    int row,  col;
    int value;
    struct OLNode* right,*down;
}OLNode;

typedef struct OLNode *OLink;

typedef struct
{
    OLink  * row_head,  *col_head;
    int     m,  n,  len;
}CrossList;
/*********************************************************************************************************/
//2. 栈 Stack
//插入数据: 入栈(Push), 删除数据: 出栈(Pop), 先进后出，后进先出(FILO/LIFO)

//2.1.0 Stack 栈的顺序存储结构
typedef struct StackNode *Stack;
//栈的顺序存储结构通常由一个一维数组和一个记录栈顶元素位置的变量组成
struct StackNode{
    int data[MaxSize];
    int Top;//指示栈顶的位置，不是指针变量，是栈顶元素的下标
};
//2.1.1 Push 入栈操作
void PushStack(Stack StackPtr, int item){
    if(StackPtr->Top == MaxSize - 1){
        cout << "The stack is full" << endl;
    }
    else{
        StackPtr->data[++(StackPtr->Top)] = item;//equivalent to (StackPtr->Top)++; StackPtr->data[StackPtr->Top] = item;
        return;
    }//Top = -1 代表栈空
}
//2.1.2 Pop 出栈操作
int PopStack(Stack StackPtr){
    if(StackPtr->Top == -1){
        cout << "The stack is empty" << endl;
        exit(0);
    }
    else{
        return StackPtr->data[(StackPtr->Top)--];
    }
}
//2.1.3 使用一个数组实现两个堆栈
//一种比较聪明的方式是使这两个栈分别从数组的两头开始向中间生长；当两个栈的栈顶指针相遇时，表示两个栈都满了。
struct DoubleStack{
    int Data[MaxSize];
    int Top1;//堆栈1的栈顶指针
    int Top2;//堆栈2的栈顶指针
}S;
//initial value: S.Top1 = -1; S.Top2 = MaxSize;

void Push(struct DoubleStack *PtrS, int item, int Tag){
    //Tag作为区分两个堆栈的标志，取值为1和2
    if(PtrS->Top2 - PtrS->Top1 == 1){
        cout << "The stack is full" << endl;
    }
    if(Tag == 1){//对第一个堆栈操作
        PtrS->Data[++(PtrS->Top1)] = item;
    }
    if(Tag == 2){//对第二个堆栈操作
        PtrS->Data[--(PtrS->Top2)] = item;
    }
}

int Pop(struct DoubleStack *PtrS, int Tag){//Tag作为区分两个堆栈的标志，取值为1和2
    if(Tag == 1){//对第一个堆栈操作
        if(PtrS->Top1 == -1){//堆栈1空
            cout << "The stack1 is empty" << endl;
            return NULL;
        }
        else{
            return PtrS->Data[(PtrS->Top1)--];
        }
    }
    else{//对第二个堆栈操作
        if(PtrS->Top2 == MaxSize){//堆栈2空
            cout << "The stack2 is empty" << endl;
        }
        return PtrS->Data[(PtrS->Top2)++];
    }
}
//2.2.0 Linked Stack堆栈的链式存储
//栈的链式存储结构实际上就是一个单链表，叫做链栈。插入和删除操作只能在链栈的栈顶进行。
//栈顶指针Top应该在链表的哪一头？显然，插入删除操作只能在单向链表中链表的表头才方便同时进行，因此Top指针应该指向链表的表头
typedef struct LinkedStackNode* LinkedStack;
struct LinkedStackNode{
    int data;
    struct LinkedStackNode *next;
};
//2.2.1 创建一个一个链栈
//构建一个堆栈的头节点，返回它的头指针 S是头指针 //注意 头节点不属于链栈的元素
LinkedStack CreateLinkedStack(){
    LinkedStack S;
    S = (LinkedStack)malloc(sizeof(LinkedStackNode));
    S->next = NULL;
    return S;
}
//2.2.2 链栈判空
int IsEmpty(LinkedStack S){
    //判断堆栈S是否为空，若为空函数返回整数1，否则返回0
    return (S->next == NULL);
}
//2.2.3 链栈入栈
void Push(int item, LinkedStack S){
    struct LinkedStackNode *temp;
    temp = (LinkedStack)malloc(sizeof(LinkedStack));
    temp->data = item;
    temp->next = S->next;//如果temp是第一个插入的结点，那么此时对应的S->next为空
    S->next = temp;
}
//2.2.4 链栈出栈
int Pop(int item, LinkedStack S){//删除并返回堆栈S的栈顶元素
    struct LinkedStackNode *FirstCell;
    int topelement;
    if(IsEmpty(S)){
        cout << "The LinkedStack is empty" << endl;
        return NULL;
    }
    else{
        FirstCell = S->next;
        topelement = FirstCell->data;
        S->next = FirstCell->next;
        free(FirstCell);
        return topelement;
    }
}
//2.3.0 堆栈应用: 表达式求值
//a+b*c-d/e的前缀表达式是:-+a*bc/de, 后缀表达式是:abc*+de/-
//过程2 Then 使用堆栈对已得到的后缀表达式进行求值(放进堆栈内的是运算数)
//后缀表达式求值策略: 从左向右“扫描”，逐个处理运算数和运算符号
//从左到右读入后缀表达式的各项(运算符或运算数)
//遇到运算数：入栈；遇到运算符：从栈顶中弹出适当数量的运算数，计算将结果入栈；最终栈顶上剩余的一个元素就是表达式的值
/*
 PosfixCompute(formula){
    设置一个空栈S；
    从后缀式中读取一个字符ch；
    while(formula未结束){
        if ch是一个数
            Push(S,ch);
        else{
            num1 = Pop(S)；
            num2 = Pop(S);
            num = num1 ch num2;
            Push(S, num);
        }
        从formula中读入下一个字符ch;
    }
    return Pop(S);
 } T(n) = O(n)
 */

//过程1 First 使用堆栈将中缀表达式转换为后缀表达式(放进堆栈内的是运算符)
//中缀表达式求值-->如何把中缀表达式转换为后缀？ 2 + 9 / 3 - 5 --> 2 9 3 / + 5 -
//1.运算数相对顺序不变，2.运算符号顺序发生改变(2.1 需要存储“等待中”运算符号 2.2要将当前运算符号与“等待中”的最后一个运算符号比较，如果前面一个运算符号优先级更高，即可将前面的运算符号放置在运算数后，如果前面一个运算符号优先级更低，则仍需要向后看算符号)
//a*(b+c)/d --> abc+*d/ NOTICE:1.左括号优先级比乘号高，但左括号一旦进栈后就必须把括号内的内容计算完，也就是说左括号不能立刻拿出来参与计算，因此左括号一旦进入堆栈，优先级可以看作降为最低, 注意括号只弹出不输出。 2.两个优先级相同的运算符相遇时，前一个可以抛出
//主要步骤：1，设置空栈S，2，依次读入中缀表达式中的元素。如果读入的是操作数，则将其直接输出，如果读入的是“）”，则将其与栈S中的栈顶元素相比较，如果它的优先级高于栈顶元素，则将其压入栈S中，否则从栈中弹出并输出栈元素，之道发现优先级更低的元素为止，再将其压入栈S中。3.直至读到输入的表达式的末尾，然后将栈元素弹出并输出，直到栈S变空。
/*
 InfixToPosfix(formula){
    设置一个空栈S;
    从中缀式formula中读取一个字符ch;
    while(formula未结束){
        if(ch是一个数)
            输出ch;
        else if(ch == ')'){
            ch1 = Pop(S);
            while(ch!='('){
                输出 ch1;
                ch1 = Pop(S);
            }
        }//end ch 是 ‘)'
        else{
            ch1 = GetTop(S);
            if(ch的优先级大于ch1)
                Push(S,ch);
            else{
                if(GetTop(S) != '('){
                    ch1 = Pop(S);
                    while(ch的优先级小于ch1{
                        输出ch1；
                        ch1 = Pop(S);
                    }
                }
                Push(S,ch);
            }//end ch的优先级小于栈顶元素
        }//end ch是其他操作符
        从formula中读入下一个字符ch;
    }
    while(S非空){
        输出Pop(S);
    }
 }
 */

//堆栈的应用有：编译过程中函数调用及递归的实现中，如果没有堆栈，递归是很难实现的
//深度优先搜索（表现形式可能是递归），回溯算法(试探可能性，如果各种路径都走不通，要回退到上一级)

//2.3.1 平衡符号算法
/*
symbol_match(file){
    设置一个空栈S；
    从文件中读取一个字符ch；
    while(file未结束){
        if ch 属于 {'(', '[', '{'}
            Push(S, ch);
        else if ch 属于 {')', ']', '}'}
        {
            chr = Pop(s);
            if ch 与 chr unmatch
                报错；
        }
        从file中读入下一个字符ch;
    }
    if 栈S 为空
        匹配成功;
    else
        匹配失败;
}T(n)=O(n)
 */
//利用栈实现阶乘的非递归算法

/*
unsigned int factorialStack2(unsigned int n){
    Stack S;
    StackInit(S);
    while(n>0){
        Push(S,n);
        n = n - 1;
    }
    n = 1;
    while(StackLength(S) > 0){
        n = n*Pop(S);
    }
    return n;
}
*/

//3. 队列 Queue
//Queue 队列: 具有一定操作约束的线性表，插入和删除操作，只能在一端插入，而在另一端删除, FIFO
//3.1.0 队列的顺序存储方式，队头front 做删除操作，队尾rear 做插入操作
struct QueueNode{
    int data[MaxSize];
    int front;//front 初始值为-1
    int rear;//rear 初始值为-1
};
//加入一个元素时rear+1，删除一个元素时front+1,rear=front时队列为空

//3.2.0 循环队列 Circular Queue
//front=rear时，队列中没有元素，注意这里存在一个空、满无法区分的问题，由于front减去rear的取值范围时[0,n-1]（n种）,而队列装载情况有n+1种，显然矛盾。解决：1)使用额外标记Size或Tag(插入一个元素 tag=1，删除一个元素，tag=0，front=rear时，看tag)域, 2)仅使用n-1个数组空间
//加入一个元素时rear+1，删除一个元素时front+1
typedef struct QueueNode* CircularQueue;
//3.2.1 Enqueue 入队--数据插入
void Enqueue(CircularQueue PtrQ, int item){
    if((PtrQ->rear + 1) % MaxSize == PtrQ->front)/*只允许放n-1个元素*/{
        cout << "The queue is full" << endl;
        return;
    }
    PtrQ->rear = (PtrQ->rear + 1) % MaxSize;
    PtrQ->data[PtrQ->rear] = item;
}
//3.2.2 Dequeue 出队--数据删除
int Dequeue(CircularQueue PtrQ){
    if(PtrQ->front == PtrQ->rear){
        cout << "The queue is empty" << endl;
        exit(-1);
    }
    else{
        PtrQ->front= (PtrQ->front + 1) % MaxSize;
        return PtrQ->data[PtrQ->front];
    }
}
//3.3.0 队列的链式存储
//链表表头做front删除，链表表尾做rear插入(链表表尾不能做删除操作)
struct LinkedQueueNode{//链队列结点
    int data;
    struct LinkedQueueNode *next;
};
typedef struct LinkedQueueNode LQNode;
typedef struct LinkedQueueNode *LinkedQNode;

struct QueueHEAD{//头、尾指针封装在一起的链队列
    LQNode *front;
    LQNode *rear;
};
typedef struct QueueHEAD LQueue;
typedef struct QueueHEAD *LinkedQueue;

//链式队列的初始化, 就是创建一个空队列
void LinkedQueueInit(LinkedQueue Q){
    LinkedQNode p = (LinkedQNode)malloc(sizeof(LQNode));
    if(p==NULL){
        cout << "头结点空间申请失败" << endl;
        exit(0);
    }
    else{
        p->next = NULL;
        Q->rear = p;
        Q->front = p;
    }
}
//链式队列的判空操作
int LinkedQueueEmpty(LinkedQueue Q){
    if(Q->front == Q->rear)
        return 1;
    else
        return 0;
}

//链式队列的入队操作
void EnLinkedQueue(LinkedQueue Q, int x){
    LinkedQNode q = (LinkedQNode)malloc(sizeof(LQNode));
    if(q == NULL){
        cout << "空间申请失败！" << endl;
        exit(0);
    }
    else{
        q->data = x;
        q->next = NULL;
        Q->rear->next = q;
        Q->rear = q;
    }
}
//链式队列的出队操作
int OutLinkedQueue(LinkedQueue Q){
    int x;
    if(Q->front == Q->rear){
        cout << "the queue is empty" << endl;
        exit(0);
    }
    LinkedQNode q = Q->front->next;
    Q->front->next = q->next;
    x = q->data;
    free(q);
    if(Q->front->next == NULL)
        Q->rear = Q->front;
    return x;
}
/*********************************************************************************************************/
/*
 4. 串 String
 //串的顺序存储结构
 */
# define STRSIZE = 256

//串的动态存储结构 (堆存储结构，用malloc分配)
//使用一组地址连续的存储单元存放串值字符序列，但存储空间是在程序执行过程中动态分配的
//这种存储方式可以利用标准函数malloc和free动态地分配和释放存储空间，并且以一个特殊的字符('\0')作为字符串的结束标志。
//在类型声明中str是串存放的起始地址，串的第i个字符存储在ch[i-1]中。length存储串的长，且最后一个字符的下标是length-1
struct StringNode{
    char *str;
    int length;
};
typedef struct StringNode string;

//串的赋值操作 将串T的值赋给串S
void SeqStringAssign(StringNode *S,StringNode *T) {
    if((S->str) != NULL)
        free(S->str);
    S->length = T->length;
    if (S->length == 0) {//若T是空串
        S->str = (char*) malloc(sizeof(char));
        if(!S->str) {
            printf("空间分配失败!");
            exit(0);
        }
        //S->str = '/0';
    }
    else{//T不是空串
        S->str = (char *)malloc((S->length + 1)*sizeof(char));
        if(!S->str){
            printf("空间分配失败!");
            exit(0);
        }
        for(int i=0; i<S->length; i++)
            S->str[i] = T->str[i];
    }
}
//串赋值操作
StringNode* SeqStringAssign(StringNode *S, char* V) {
    if ((S->str) != NULL)
        free(S->str);
    S->length = sizeof(V) / sizeof(char);
    S->str = (char*)malloc((S->length)*sizeof(char));
    if (!S->str){
        printf("overflow");
        exit(0);
    }
    for (int i = 0; i < S->length; i++) {
        S->str[i] = V[i];
    }
    return S;
}
//串连接操作
void SeqStringContact(StringNode* S, StringNode* T){
    StringNode temp;
    temp.length = S->length + T->length;
    temp.str = (char *)malloc((temp.length)*sizeof(char));
    if(!temp.str){
        cout << "空间分配失败！" << endl;
        exit(0);
    }
    else{
        for(int i = 0; i < S->length; i++){
            temp.str[i] = S->str[i];
        }
        for(int i = 0; i < T->length; i++){
            temp.str[S->length + i] = T->str[i];
        }
        free(temp.str);
        S->str = temp.str;
        S->length = temp.length;
    }
}
//串判等操作
int IsSeqStringEqual(StringNode *S, StringNode *T){
    if(S->length != T->length)
        return 0;
    for(int i = 0; i < S->length; i++){
        if(S->str[i] != T->str[i])
            return 0;
    }
    return 1;
}

//求子串操作
void SubSeqString(StringNode *S, StringNode *Sub, int start, int len){
    if(1<=start && start<=S->length && start<=S->length-len+1){
        Sub->str = (char *)malloc((len)*sizeof(char));
        if(!Sub->str){
            printf("空间分配失败!");
            exit(0);
        }
        else{
            Sub->length=len;
            for (int i=0;i<len;i++) Sub->str[i]=S->str[start+i-1];
        }
    }
    else {
        printf("start与len的值不正确");
        exit(0);
    }
}

//5. 串的模式匹配
//BF算法(Brute Force)
/*
 S = ababcdabbabababad  i
 P =          abababa   j

int SimpleMatching(StringNode S, StringNode P){
    int i = 0;
    while(i <= StringLength(S) - StringLength(P)){
        int j = 0;
        while(S[i] == P[j]){
            i++;
            j++;
        }
        if(j == StringLength(P))
            return i-StringLength(P); //返回匹配的位置
        i = i - j + 1；
    }
 return -1; //返回不匹配
}
T(n) = O((n-m+1)*m) = O(nm)
*/
//KMP算法
/*
 void findnext(StringNode P, int *next){
    next[0] = -1;
    j = 0;
    k = -1;
    while(j < Length(P)){
        while(k == 0 || P[j] == P[k]){
            j++;
            k++;
            next[j] = k;
        }
        k = next[k];
    }
}
 
int KMP(StringNode S, StringNode P){
    findnext(P, next);
    i = j = 0;
    while(i <= Length(S) - Length(P)){
        while(j == -1 || < Length(P) && S[i]==P[j]){
            i++;
            j++;
        }
        if(j==Length(P))
            return i - Length(P); //返回匹配的位置
        j = next[j]; //在不匹配的情况下，i不变化
    }
 return -1;
}

*/
/*********************************************************************************************************/
/*
 6. 二叉树 Binary Tree
 */
typedef struct BinTreeNode{
    int data;
    struct BinTreeNode *lchild, *rchild;
}BinTreeNode, *BinTree;
//在n个结点的二叉链表中，有n+1个空指针域, 空指针域数目 = 2n0 + n1 = n0 + n1 + n2 + 1 = n + 1

//二叉树的先序遍历(recursion)
void PreOrderTraversal(BinTree bt){
    if (bt!=NULL){ /* 如果bt为空，结束*/
        printf("%c", bt->data); /*访问根结点*/
        PreOrderTraversal( bt->lchild);/*先序遍历左子树*/
        PreOrderTraversal (bt->rchild);
    }
}
//二叉树的先序遍历(nonrecursion)
/*
 void PreOrderNoRec (BinTree BT) {
    Stack S; BinTree p=BT->root;
    while ((p != NULL) || !StackEmpty(S)) {
        if (p != NULL){
            printf("%c", p->data);//访问当前结点
            Push(S,p);//将p压入栈S
            p = p->lchild;//将p指向其左子树
        }
        else{
            p = Top(S);
            Pop(S); //从栈S弹出栈顶元素
            p = p->rchild; //将p指向其右子树
        }
    }
}
*/

//二叉树的中序遍历(recursion)
void InOrderTraversal(BinTree bt){
    if (bt!=NULL){ /* 如果bt为空，结束*/
        InOrderTraversal(bt->lchild);/*先序遍历左子树*/
        printf("%c", bt->data); /*访问根结点*/
        InOrderTraversal(bt->rchild);
    }
}

//二叉树的后序遍历(recursion)
void PostOrderTraversal(BinTree bt){
    if (bt!=NULL){ /* 如果bt为空，结束*/
        PostOrderTraversal(bt->lchild);/*先序遍历左子树*/
        PostOrderTraversal(bt->rchild);
        printf("%c", bt->data);
    }
}
//二叉树的层次遍历
void LevelOrderTraverse(BinTree bt){
    BinTreeNode Queue[MaxSize];
    int front, rear;
    if(bt == NULL)
        return; //空二叉树，遍历结束
    front = -1;
    rear = 0;
    Queue[rear] = *bt; //根结点入队列
    while(rear != front){/*队列不空，继续遍历，否则，遍历结束*/
        front ++;/*出队*/
        cout << Queue[front].data << endl;/*访问刚出队的元素*/
        if(Queue[front].lchild != NULL){//如果有左孩子，左孩子入队
            rear++;
            Queue[rear] = *Queue[front].lchild;
        }
        if(Queue[front].rchild != NULL){//如果有右孩子，右孩子入队
            rear++;
            Queue[rear] = *Queue[front].rchild;
        }
    }
}
//
/*
 7. 矩阵 Matrix
 */
/*********************************************************************************************************/
/*
 6. 数组 Array
 7. 矩阵 Matrix
 */
/*********************************************************************************************************/
//直接插入排序 StraightInsertionSort
//单趟直接插入
//arr是一个有序表，i为待插入的纪录，len为表长
void StraightInsertion(int* arr, int i, int len){
    arr[0] = i; //设置监视哨 //从右至左查找第一个比i小的数的位置
    int pos = len;
    while(i < arr[pos]){
        arr[pos + 1] = arr[pos];
        pos--;
    }
    arr[pos+1] = i;//将i插入到合适的位置
}
//arr是一个有序表，i为待插入的纪录，len为表长
void StarightInsertionSort(int *arr,int len){
    for(int i=2; i<len; i++){
        StraightInsertion(arr,arr[i],i-1);
    }
}

//希尔排序 ShellSort
//单趟希尔排序
int* Shell(int* arr, int h, int len){//h为增量
    for(int i = 1; i < h; i++){
        for(int j = 1; j < len; j +=h){
            arr[0] = arr[j];
            for(int m = j - h; m > 0; m -= h){
                if(arr[0] > arr[m]){
                    arr[m+h] = arr[m];
                }
            }
        }
    }
    return arr;
}

int* ShellSort(int* arr, int*h, int hlen, int len){
    int* temList = arr;
    for(int i = hlen - 1; i >= 0; i--){
        temList = Shell(temList, h[i], len);
    }
    return arr;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/


int main(int argc, const char * argv[]) {
    return 0;
}



