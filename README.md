

>- [**前言**](#前言)
- [**前言**](#前言)
- [一、单向链表](#一单向链表)
	- [1.简介](#1简介)
	- [2.代码与图解](#2代码与图解)
- [二、带头双向循环链表](#二带头双向循环链表)
	- [1.简介](#1简介-1)
	- [2.代码与图解](#2代码与图解-1)
	- [3.补充](#3补充)
- [三、栈](#三栈)
	- [1.简介](#1简介-2)
	- [2.代码与图解](#2代码与图解-2)
- [四、队列](#四队列)
	- [1.简介](#1简介-3)
	- [2.代码与图解](#2代码与图解-3)
- [五、二叉树](#五二叉树)
	- [1.了解递归和递归与栈的关系](#1了解递归和递归与栈的关系)
	- [2.树的基本概念](#2树的基本概念)
	- [3.树的存储结构（待更）](#3树的存储结构待更)
	- [**4.二叉树**](#4二叉树)
	- [5.前、中、后序遍历（代码与图解）](#5前中后序遍历代码与图解)
	- [6.补充](#6补充)
- [六、排序算法](#六排序算法)
	- [1. 引子](#1-引子)
	- [2.基本排序算法](#2基本排序算法)
		- [2.1  冒泡排序](#21--冒泡排序)
		- [**2.2选择排序**](#22选择排序)
		- [**2.3插入排序**](#23插入排序)
- [七、进阶排序算法](#七进阶排序算法)
		- [1.1 希尔排序](#11-希尔排序)
		- [1.2 堆排序](#12-堆排序)
		- [1.3 快速排序—递归](#13-快速排序递归)
		- [1.4 归并排序—递归](#14-归并排序递归)
	- [八、改良排序](#八改良排序)
		- [2.1 三数找中](#21-三数找中)
		- [2.2 小区间优化](#22-小区间优化)
		- [\* 2.3 快速排序—非递归](#-23-快速排序非递归)
		- [\* 2.4 归并排序—非递归](#-24-归并排序非递归)



**前言**
======

**什么是数据结构：**

百度百科：数据结构是计算机存储、组织数据的方式。数据结构是指相互之间存在一种或多种特定关系的数据元素的集合。

**为何要学习数据结构：**

 通常情况下，精心选择的数据结构可以带来更高的运行或者存储效率。数据结构往往同高效的检索[算法](https://baike.baidu.com/item/%E7%AE%97%E6%B3%95/209025?fromModule=lemma_inlink "算法")和[索引](https://baike.baidu.com/item/%E7%B4%A2%E5%BC%95/5716853?fromModule=lemma_inlink "索引")技术有关。

一、单向链表
======

## 1.简介

链表作为一种基本的数据结构在程序开发过程当中经常会使用到。对C语言来说链表的实现主要依靠结构体和指针；

链表的一个结点如下⬇️：

```cpp
typedef int SLTDataType;
typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;
```

如图⬇️，为一个基本的[单向链表](https://so.csdn.net/so/search?q=%E5%8D%95%E5%90%91%E9%93%BE%E8%A1%A8&spm=1001.2101.3001.7020)：

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/fc356305ede649fe91485021ec1daa8f.jpeg)

掌握单向链表的增 、 删 、 查 、 改   ，为之后的带头、双向、循环链表做铺垫。

## 2.代码与图解

先看一下实现链表需要的函数⬇️

```cpp
void SListPrint(SLTNode* phead);
void SListPushBack(SLTNode** pphead, SLTDataType x);
void SListPushFront(SLTNode** pphead, SLTDataType x);
void SListPopFront(SLTNode** pphead);
void SListPopBack(SLTNode** pphead);
SLTNode* SListFind(SLTNode*phead, SLTDataType x);
void SListInsert(SLTNode** pphead,SLTNode*pos, SLTDataType x);
void SListErase(SLTNode** pphead, SLTNode* pos);
```

**①.尾插** 

**1.创建一个结构体指针（newnode），判断头指针是否为空（注意是*pphead）；**

 2.若不为空：备份头指针（tail），用while循环找到链表的尾部，最后将尾部的下一个指向新创建的newnode。

**![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/e8a1776994f04ec8ab3a213731759f87.jpeg)**

```cpp
void SListPushBack(SLTNode **pphead, SLTDataType x)
	{
 
	SLTNode* newnode = BuySListNode(x);
 
		if (*pphead == NULL)
		{
			*pphead = newnode;
		}
		else
		{
			SLTNode* tail = *pphead;
			while (tail->next != NULL)
			{
				tail = tail->next;
			}
			tail->next = newnode;
		}
	}
```

 其中`BuySListNode`函数即创建并初始化（注意返回值为SLTNode*）：

```cpp
SLTNode*BuySListNode(SLTDataType x)                               
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
    newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
```

**（理解了尾插，头插就是小case啦）**

**②.头插 **

1. `newnode->next`  ←  `*pphead`;  (“旧头”给“新头”的next👌)   

2.`pphead`  ← `newnode`；（将“新头”的地址给“旧头”，及把newnode变成新头）；

```cpp
void SListPushFront(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySListNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}
```

**③.头删      **

※1.若将头一刀砍，身子就找不到取出了🤣，意思是要将头指向的下一个保存起来（next）；

2.`free`掉旧头，`pphead`的地址变为next的地址（及将链表的第二个数变成新头）`*pphead`← `next`。

```cpp
void SListPopFront(SLTNode** pphead)
{
	 SLTNode*next= ( * pphead)->next;
	 free(*pphead);
	 *pphead = next;
}
```

**④尾删  **（别以为头删简单，就轻视尾删）

**1.两种特殊情况：链表为空  和  只有一个头，想到了后面删除就简单了；**

2.若有两个及以上：同样第一步是找到链表的尾部，※但是直接将尾部置为空，那么倒数第二个的next将无家可归🤦‍♂️

**所以，定义一个prev，当next的小老弟，跟在next的后面，当next指向尾部时，prev就自然是倒数第二了！**

```cpp
void SListPopBack(SLTNode** pphead){
	if (*pphead = NULL)
		return;
	else if ((*pphead)->next = NULL)
	{
		free(*pphead);
		*pphead = NULL;
			
	}
	else
	{
		SLTNode* prev = NULL;
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		prev->next = NULL;
	}
}
```

重头戏来了🙌                                                                 

**⑤插入  **

1.往pos之前插入，自然需要找到pos的位置（查找函数在下方），再将pos转入SListInsert函数之内，最后将需要插入的值传入；

2.如果pos的地址就为pphead，那么就是上面说的头插了；

3.同样定义prev，用它借助while循环找到pos的前一位，之后开辟一个newnode，通过next将prev----newnode----pos三者连接起来。

```cpp
void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x) {
	if (pos == *pphead)
		SListPushFront(pphead, x);
 
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		SLTNode* newnode = BuySListNode(x);
		prev->next = newnode;
		newnode->next = pos;
	}
}
```

**⑥删除  **

1.思路与 插入 类似：如果pos的地址就为pphead，那么就算是尾删了；

2.举一反三：定义prev，用它找到pos的前一位并用prev指向它，此时用next将prev与pos的下一位（pos->next）链接起来就能将pos指向的位置给丢掉啦！（别玩了用free掉pos，将他丢干净😎）

```cpp
void SListErase(SLTNode** pphead, SLTNode* pos) {
	if (pos == *pphead)
		SListPopBack(pphead);
 
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		prev->next = pos->next;
		free(pos);
	}
}
```

**补充**

**①查找（pos）**

 1.※（ *phead是一级指针），传入x，查找data为x的指针cur并将其返回（return cur）。

```cpp
SLTNode* SListFind(SLTNode* phead, SLTDataType x)
{
	SLTNode* cur = phead;
	while (cur)
	{
		if (cur->data == x)     //特别注意=  与 ==的区别；
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
```

**②输出   有了上述的理解，这儿就显得很easy啦！**

```cpp
void SListPrint(SLTNode* phead)
{
	SLTNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL");
}
```

二、带头双向循环链表        
==================

## 1.简介

学习了单向链会发现它理解起来容易但是实现起来复杂，而接下来的链表理解起来相对复杂，实现起来却很容易；

这条链表的一个结点如下：

```cpp
typedef int LTDataType;
typedef struct ListNode
{
	struct ListNode* next;
	struct ListNode* prev;
	LTDataType data;
}ListNode;                   
```

 如图⬇️，为一个基本的单向链表：

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/cca8eeef536446e4b158c3996e8466c8.jpeg)

 ※ 带头：这里的phead为一个不存数据的指针 ，所以传一级指针；可以说phead为假头，phead->next才是真头；

※ 双向：eg.之前尾删需要两个指针，这里的优点就非常明显了，一举两得，得到一个节点可以找到它的前一个（->prev）和后一个(->next);

※ 循环：尾结点的下一个节点不为空，而是假头(tail->next == phead);同样phead->prev == tail，这样能直接找到尾指针。

## 2.代码与图解

忽略掉简单的初始化、打印、销毁，需实现的函数如下：

```cpp
void ListPushBack(ListNode* phead, LTDataType x);
void ListPushFront(ListNode* phead, LTDataType x);
void ListPopFront(ListNode* phead);
void ListPopBack(ListNode* phead);
void ListInsert(ListNode* pos, LTDataType x);  //插入
void ListErase(ListNode* pos);  //删除
```

这里我们先写出插入与删除，之后有了上文的优点，其他的会变得非常简单：

**①.插入**

**图解**⬇️**：** 找到pos前的first，再将newnode与两者双向链接。

**![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/e4e10e0fdbfe4656a86c7050290d1067.png)**

代码如下：

```cpp
void ListInsert(ListNode* pos, LTDataType x)
{
	assert(pos);
	ListNode* first = pos->prev;
	ListNode* newnode = BuyListNode(x);
	first->next = newnode;
	newnode->prev = first;
	newnode->next = pos;
	pos->prev = newnode;
}
```

**②.删除**

**图解**⬇️**：**

若直接删除pos这个结点，这个链表就一刀两段了，所以要找到pos的头尾，再将它们链接起来。

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/15dad46fb33a48e6823c69f06e155dae.gif)

 ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/d36b067166d649f39477ba278004d8a6.png)

**代码如下：**

```cpp
void ListErase(ListNode* pos)
{
	assert(pos);
	ListNode* next = pos->next;
	ListNode* prev = pos->prev;
	prev->next = next;
	next->prev = prev;
	free(pos);
	pos = NULL;
}
```

有了插入与删除，接下来的代码就会非常简单了；

**③ 尾 插：**

参考   ①插入   这里传phead过去，到ListInsert函数里pos指向phead，因为是**循环链表**，可以往phead前找到first（及为链尾），再往first与phead之间插入就实现尾插了。⬇️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/a6d54ec09e3643a9a7838ce81e0e667d.png)

```cpp
void ListPushBack(ListNode* phead, LTDataType x)
{
	assert(phead);
 
	ListInsert(phead, x);
}
```

**④ 头 插：**

对比尾插，思考一下🤔🤔🤔，这里往ListInsert函数里传入的就是  **phead->next** 了，

也就是在phead与phead->next之间插入；

```cpp
void ListPushFront(ListNode* phead, LTDataType x)
{
	assert(phead);
	
	ListInsert(phead->next, x);
}
```

⑤&⑥ 头 删 与 尾 删

参考 ② 删除  若要实现头删，很好想象，就是传假头指向的真头（phead->next）

```cpp
void ListPopFront(ListNode* phead)
{
	assert(phead);
	assert(phead->next != phead);
 
	ListErase(phead->next);
}
```

同样，因为链表循环，尾删 就是删除 phead->prev;

```c
void ListPopBack(ListNode* phead)
{
	assert(phead);
	assert(phead->next != phead);
 
	ListErase(phead->prev);
}
```

## 3.补充

①. 掌握带头 双向 循环 链表也就是掌握了2 × 2 × 2 = 8种链表；

②. 简单的查找与打印就是遍历链表，这里就不说了；

③.**Destroy**：建立两个指针，将phead之后的结点都free掉，最后将free（phead）；

```c
void ListDestory(ListNode* phead)
{
	assert(phead);
	ListNode* cur = phead->next;
	while (cur != phead)
	{
		ListNode* next = cur->next;
		free(cur);
		cur = NULL;
		cur = next;
	}
	free(phead);
	phead = NULL;
}
```

三、栈
=======

## 1.简介

**①. 栈**，**线性表**的一种特殊的[存储结构](https://so.csdn.net/so/search?q=%E5%AD%98%E5%82%A8%E7%BB%93%E6%9E%84&spm=1001.2101.3001.7020)。与学习过的线性表的不同之处在于栈只能从表的**固定一端**对数据进行插入和删除操作，**另一端是封死的**;

②. 栈的“先进后出”原则：

- 先进：数据元素用栈的数据结构存储起来，称为“入栈”，也叫“压栈”，先进去的被压在最底端；

- **后出**：数据元素从栈结构中提取出来，称为“出栈”，也叫“弹栈”，也就是后进入的比先进入的先出来；

**③. **如下图⬇️，我们可以把栈比作手枪的**弹夹，**看得出来，先被**压**进弹夹的子弹是后**弹**出弹夹的；

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/504090ee148e4fbf9002b49ddde816ca.gif)

4.**我们用**数组**存储栈的数据，为了知道栈是否溢出，需要一个变量记录数组的容量**capacity**，最后用变量**top**记录栈顶，以实现出栈。将三者放入一个结构体内形成**栈⬇️

```c
typedef int STDataType;
typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;
```

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/338632d2c83a43d3b5e31105033a6c8e.png)

（参考书籍 《大话数据结构》 ）                                                                                                     

## 2.代码与图解

先看一下栈实现需要的函数⬇️

```c
void StackInit(ST* ps);    //初始化操作，建立一个空栈（ps）
void StackDestory(ST* ps);    //若栈存在，则销毁它，并清空
void StackPush(ST* ps,STDataType x);    // ※ 插入新数据x到栈ps中并成为栈顶数据
void StackPop(ST* ps);    //删除栈S中栈顶数据
STDataType StackTop(ST* ps);    //若栈存在且非空，返回ps的栈顶数据
int StackSize(ST* ps);    //返回栈的数据个数
bool StackEmpty(ST* ps);    //栈为空，返回true，否则返回false
```

**①.初始化：**

```c
void StackInit(ST* ps){
	assert(ps);
	ps->a = (STDataType*)malloc(sizeof(STDataType) * 4);
	ps->capacity = 4;
	ps->top = 0;
}
```

**②入栈：**  1.判断是否入栈之后会出现**栈溢出，若栈顶** == **容量**（capacity），则relloc对数组a增容，再改变capacity记录下现在的容量；

```c
void StackPush(ST* ps, STDataType x){
	assert(ps);
	if (ps->capacity == ps->top)
	{
		STDataType* tmp = (STDataType*)realloc(ps->a, ps->capacity * 2 * sizeof(STDataType));
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		else
		{
			ps->a = tmp;
			ps->capacity *= 2;
		}
	}
	ps->a[ps->top] = x;
	ps->top++;
}
```

**③.出栈      ※**只需要将栈顶**（top）-1**就可以了，当再次入栈时，新数据会**替代**top-1之后指向的位置

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/b3358f78d7e24bd5b7988f8aa05dbada.png)

```c
void StackPop(ST* ps){
	assert(ps);
	assert(ps->top> 0);
	ps->top--;
}
```

**④.栈顶数据、栈大小、判断是否为空栈，**均用**top**实现，较为容易，这里就不详述了，代码可进我[Gitee](https://gitee.com/dusong_041008 "Gitee")查询。![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/c74740a14e6e454199897abe8437183a.gif)

四、队列
====

## 1.简介

**①. **队列（queue）是只允许在一端进行插入操作，而在另一端进行删除操作的线性表；

**②.** 遵循**先进先出（First In First Out）**原则，简称**FIFO**；

**③.** 从名字就能想象，队列与我们平常生活中排队是一样的（但是没有插队这一说法😅）⬇️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/ee46c2c048864112adecbf146b5db8c2.gif)

**④.** 要实现一头出，一头进，并且省去从头遍历找到尾，我们定义两个指针，**head与tail**；

**⑤.** 队列可以像栈写成**数组**也可以像链表写成**结点**，这里区分栈，我把它写成结点，

这儿又有与链表不同的创建结构体方式⬇️： 

 ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/c8c3800d55a3424b9ccd5c850b5fe1c3.png)

像左边这样，函数只需要用**一级指针接收**；

接下来通过代码再次理解。

## 2.代码与图解

先看一下队列实现需要的函数⬇️

```c
void QueueInit(Queue* pq);    //初始化
void QueueDestroy(Queue* pq);    //销毁队列
void QueuePush(Queue* pq, QDataType x);    //若队列存在，插入新数据x到队列中并成为队尾元素
void QueuePop(Queue* pq);    //若队列存在，删除对头数据
QDataType QueueFront(Queue* pq);    //返回对头数据
QDataType QueueBack(Queue* pq);    //返回队尾数据
int QueueSize(Queue* pq);    //返回队列长度
bool QueueEmpty(Queue* pq);    //判断队列是否为空（true/false）
```

①. 尾插   

**1.**※**因为创建了两个结构体，所以这里要多加注意结构体指针的类型（**QNode和Queue）

**2\.** 同时，老套路了，要考虑**队列是否为空**；

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/00c1405119f54cc38b745e8a9d07acfe.png)

```c
void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);
 
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	newnode->data = x;
	newnode->next  = NULL;
	if (pq->head == NULL){
		pq->head = pq->tail = newnode;
	}
	else{
		pq->tail->next = newnode;
		pq->tail = pq->tail->next;
	}
}  
```

②. 头删 

**1.**若只有head一个结点（也就是head与tail为同一个结点），直接删除掉head；

**2.**若有多个结点，**※**不能直接删除头节点，之前也讲到过；定义next指向head->next,再删除head，

将next作为新的头节点。

```c
void QueuePop(Queue* pq)
{
	assert(pq);
	assert(pq->head);  
	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}
```

③.之后的函数也与前面极其类似，这里也不占用时间了。

五、二叉树
=====

## 1.了解递归和递归与栈的关系

 （参考书籍 《大话数据结构》、《数据结构与算法图解》）

**①. 函数调用自身**，就叫作**递归，**可以将其大概理解成一种特殊的**循环**；

**②.** 既然是函数调用自己，那么如果无止境的调用将会是一件非常可怕的事，这就需要一个判断来将这个自我调用往回走（**return**）；

接下来用一个经典的例子：**斐波那契数列**   来见识一下递归⬇️

 数学上可表示为：**F(0)=0，F(1)=1，F(n)=F(n-1)+F(n-2)(n≥2，n∈N*)**。第0项是0，第1项是第一个1。此数列从第2项开始，**每一项都等于前两项之和**。（其中的F（）也就和C语言中的函数一样，将其转化成代码如下⬇️）

 ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/43ad76ab71fc443ab093589f9ef0c967.png)

**③.**  当 i= 0 或 i = 1时，很好理解，传入Fbi函数返回0或1（**※**这就是函数不断调用自己到最后返回来的条件），但是当 i 是一个较大的数（i = 5）时又该怎么理解呢？我们画图分析⬇️：

  ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/d9924635c4c443bf9c9346c713d0d88b.png)

**注意：**图中圆圈里的数字是n，而不是返回值，**往回递归时**：圆圈里执行的是**两个返回值相加**，再对**结果**返回上一个递归中

**※补充④ .递归与栈的关系：**简单来说，递归分为两个部分（正序与逆序），那和栈怎么就搭边了呢？

在计算机系统内部，在递归**正序**时**存储**某些数据，并在后面又以存储的**逆序恢复**这些数据，以提供之后使用的需求，与栈中的**入栈与出栈**恰恰相似，因此，**编译器会用栈实现递归**。

## 2.树的基本概念

 **①. 前言**：之前学习的都是链表和顺序表，二树由根与子树构成，是一个一对多的结点类型的结构；这里将我们学过的递归思想运用到接下来的学习中

**②树的注意事项：**

**※根结点唯一**，如图⬇️，I 的根节点有两个，分别是 D 和 E；

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/9a91d468f9414e1889f9dfff9a68eb79.png)

 **※子树互不相交**，如图⬇️，D和E分别是B和C的子树，而他们相交是错误的；

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/fe70e5cf8cd24f0c953e0ee7b68a1a9a.png)

**③.** 关于**树的其他概念**较为繁琐，这里就暴力阐述了⬇️ 

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/4f0ca15ce1da4327af68e3d44aa5c519.png)

## 3.树的存储结构（待更） 

## **4.二叉树**

**①.** 二叉树是一种特殊的树，只有根、左子树、右子树组成（可以只有左子树，也可以只有右子树），每个结点的子结点最多不超过两个；

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/4b0bab83330848bf8402d0d98b5b67f7.png)

**②. ※满二叉树**： 若层数为**n**，那么**最后一层**的结点个数为 **2^n-1 **,通俗来讲就是最后一层的“叶子”一片不少⬇️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/770bb31b8c524c46b0f879610f43c9cb.png)

 **※完全二叉树**：若层数为**n**，那么**最后一层**的结点个数**x**满足 **1≤ x ≤ 2^n-1**,就是被摘了几片叶子的满二叉树⬇️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/a395bb12ba654ecd930d9705d34f0412.png)

 **③. 二叉树的性质：**  
**※.**若规定根节点的层数为1,则一棵非空_二叉树的第i层上最多有 **2^(i-1)** 个结点；✔️  
**※.**若规定根节点的层数为1,则**深度为h**的二叉树的最大结点数是 **2^h- 1**；✔️  
**※.**对任何一棵二叉树,如果度为0的叶结点个数为n0,度为2的分支结点个数为n2则有 **n0= n2+ 1**，eg.⬇️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/9ecbccf9648941949178aebcf4100a39.png)


**※.**若规定根节点的层数为1,具有n个结点的**满二叉树**的深度, **h=logN**；✔️

## 5.前、中、后序遍历（代码与图解）

**①. 数组**：我们可以简单地用数组存储二叉树的数据，再用下标表示结点位置（一颗满二叉树从根开始，每一层从左到右一次增大），但当不是结构整齐的满二叉树时（eg.只有左子树），也要按照满二叉树给数组分配空间，这样很不划算；

**②. 结构体**：从根开始，用**两个指针**分别指向左子树和右子树，再存储该结点的数据，就像链表中的一个结点一样，不同的是二叉树的一个结点指向了两个子结点，我们把这样的结构称为**二叉链表**，不废话了，看图⬇️

```c
typedef char BTDataType;
typedef struct BinaryTreeNpod
{
	struct  BTNode* left;
	struct BTNode* right;
	BTDataType data;
}BTNode;
```

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/07a8900fbba74ff4a577a50befc99362.png)

** 二叉树遍历**

**①. 前序**：传入根结点，，从根结点开始，递归遍历左子树，若不为空，则继续递归遍历左子树，若为空，返回；之后递归遍历右子树，（**根 -> 左子树 -\> 右子树**）

```c
void PrevOrder(BTNode* root)//前序
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->data);
	PrevOrder(root->left);
	PrevOrder(root->right);
}
```

图解：⬇️![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/f153383ffd744907bc3ccc3fc2954c4c.png)

 **②. 中序**：传入根结点，递归遍历左子树，到最后为空返回，访问根，之后遍历右子树；**（左子树 -> 根 -\> 右子树）**

```c
void InOrder(BTNode* root)//中序
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	InOrder(root->left);
	printf("%c ", root->data);
	InOrder(root->right);
}
```

**③. 后序**：传入根结点 ，递归遍历左子树，到最后为空返回，再递归遍历右子树，最后访问根；**（左子树 -> 右子树 -\> 根）**

```c
void PostOrder(BTNode* root)//后序
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%c ", root->data);
}
```

图解：⬇️ 

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/d9082b6a4a4e4ae6afd2b08ac817576d.png)

 ④. 层序：(待更)![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/03231ddccc52478da55bdd654bbff765.gif)

## 6.补充

**①.** 计算树总共的结点个数：※其中记录个数的 **size** 要定义为**全局变量**，因为每次递归局部变量会因出函数而销毁；或者用**传指针**；

```c
int size = 0;
void TreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		size++;
	}
	TreeSize(root->left);
	TreeSize(root->right);
}
```

**②. ※计算叶结点的总数：**

```c
nt TreeLeafSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	return root->left ==NULL&&root->right == NULL ? 1 : TreeLeafSize(root->left)+TreeLeafSize(root->right);
}
```

* * *



六、[排序算法](https://so.csdn.net/so/search?q=%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95&spm=1001.2101.3001.7020)     
===========================================================================================================

## 1\. 引子

排序在我们遍布的每个角落，还记得高考成绩出来那一天晚上，将自己的分数在一份一线表上查询，名次从上到下逐渐增大；排名就是排序，同样的还有当我们在淘宝上购买时，点击按销量排序一样，等等这些操作计算机是怎样实现的呢？接下来让我将其分为两类，一起来学习排序，。

## 2.基本排序算法

### 2.1  冒泡排序

相信大家在学习C语言的循环和数组时肯定都写过[冒泡排序](https://so.csdn.net/so/search?q=%E5%86%92%E6%B3%A1%E6%8E%92%E5%BA%8F&spm=1001.2101.3001.7020)(BubbleSort)吧，一个简单又复杂的排序

![](https://img-blog.csdnimg.cn/e526cb3966dc4297b67b8bb93774c2f5.gif)

 以升序为例

![](https://img-blog.csdnimg.cn/20210611113132421.gif#pic_center)

若数组为9到0，**第一层for循环**指需要排序的数，**第二层for循环**是将两两依次比较；**※**这里特别注意i的范围（ **i < n-1-j **）：设想如果将9移动到了最后，那么将8移动到后面的过程中就不需要将8与9比较了；**每一次第一层for循环结束就会选一次最大的数排在最后，所以第二次for循环的比较次数会越来越少；**

```c
void BubbleSort(int* a, int n)    /* n为数组大小 */
{
	for (int j = 0; j < n - 1; j++)
	{
		for (int i = 0; i < n - 1-j; i++)
		{
			if (a[i] > a[i + 1])
				Swap(&a[i], &a[i + 1]);
		}
	}
}
```

Swap: **※ **该函数应该在BubbleSort函数之上； **※ **注意解引用符号（*a1）

```c
void Swap(int* a1, int* a2)
{
	int tmp = *a1;
	*a1 = *a2;
	*a2 = tmp;
}
```

时间复杂度：**O(n^2)**

### **2.2选择排序**

 所谓选择，就是在每次循环中找到最大和最小的数的下标，在循环的最后将其交换；

**文字解析**⬇️：

> **（1）**首先定义begin和end分别指向头尾；进入while循环；
>
> **（2）**直至begin与end指向同一位置；
>
> **（3）**进入for循环，在本次begin和end指向的范围中，当 i 指向的数大于或小于两头时交换数的位置，最终在begin上为本次循环范围内的最小值，end则为最大值（升序）；
>
> **（4）**最后 begin ++，end --，再次进入while循环，进行下一次的begin与end范围内**选择最值**。✔️

当然你也可以选择遍历一遍选择最大（最小）然后放在开头（末尾），这里用一次遍历选择最大和最小相当于一个进阶的[选择排序](https://so.csdn.net/so/search?q=%E9%80%89%E6%8B%A9%E6%8E%92%E5%BA%8F&spm=1001.2101.3001.7020)；

```c
void SelectSort(int* a, int n)
{
	int begin = 0;
	int end = n - 1;
	while (end > begin)
	{
		for (int i = begin; i < end; i++)
		{
			if (a[i] < a[begin])
				Swap(&a[i], &a[begin]);
			if (a[i] > a[end])
				Swap(&a[i], &a[end]);
		}
		begin++;
		end--;
	}
}
```

时间复杂度：与冒泡排序同为 **O(n^2)** ,但是在性能上要略**优于**冒泡排序。

### **2.3插入排序**

 ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/9fcbd5e31c994c5dbe51354267a1c8e0.jpeg)

斗地主相信大家都玩过吧，拿到牌之后第一时间就是将牌按照自己的习惯一张张地插入到相应位置 ；

下面我就将一部分类比抽牌来解释插入排序的原理（升序）⬇️：

![](https://img-blog.csdnimg.cn/img_convert/a5b2969d0bf7358198f98834d78d076b.png)

> （1）进入for循环（i）**{**   定义**end = i** ，end指向手中卡牌的最后一张，tmp拷贝抽到的卡牌（**a\[end + 1\]**），及end指向的下一个；※ 之所以 **i < n - 1** , 当end指向的是**倒数第二张牌**时，即将排序的是最后一张牌(整个数组的最后一个数)，排序玩最后一张牌之后，整个数组就是有序的了；
>
> （2）之后进入while循环  **{ **  将end指向的数及之前的数，依次与即将插入的数（tmp）比较，若大于tmp，则将该数后移（a\[end+1\] = a\[end\]）**}   **若比tmp小则跳出循环，将tmp插入到该数之后；（当end = -1时，及所有数都比tmp大时，tmp插在最开头end == 0的位置） ✔️
>
> **}**

```cpp
void InsertSort(int* a, int n){
    for (int i = 0; i < n - 1; i++)	{	
        int end = i;	
        int tmp = a[end + 1];	
        while (end >= 0){	
            if (a[end] > tmp){	
                a[end + 1] = a[end];	
                end--;			
            }else		
                break;	
        	}		
        a[end + 1] = tmp;	
    	}
	}
}
```

时间复杂度： 同样也是 **O(n^2)** ,但是比冒泡排序和选择排序性能要好；





七、进阶[排序算法](https://so.csdn.net/so/search?q=%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95&spm=1001.2101.3001.7020)
========================================================================================================

（接下来的排序难度上升较大，需要耐心学习） 

### 1.1 希尔排序

**介绍：**

[希尔排序](https://so.csdn.net/so/search?q=%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F&spm=1001.2101.3001.7020)又称**缩小增量排序** ，之前接触的三种排序时间复杂度均为 O(n^2) ,而 _D·L·Shell_ 于 1959 年提出的希尔排序实现了时间复杂度的突破，其时间复杂度为 **O(n*logn);**

通过怎样的方法提高排序效率呢？首先我们来了解一个概念：

**基本有序**：较小的数基本都排在前面，较大的数基本都排在前面，例如{<u>2，1，3</u>，<u>6，7，5</u>，<u>9，7，8</u>} 

如果一个序列他基本有序，序列中**待排序的记录个数**会大量的**减少**，那么现在再用头上讲的插入排序，效率自然就高了；问题来了，用何种方法将序列趋于基本有序呢？

**※** 希尔选取间隔一定**增量**的数组成一个子序列，在这个子序列中执行插入排序，实现局部有序，之后**缩小增量，**再在组成的子序列中进行插入排序，当增量为1时，就相当于对整个序列进行插入排序。图例⬇️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/5c0e060bb1e44413b99869aba71c3d3d.png)

> （1）看下面代码，进入循环后增量（**gap**）分别有3、2、1；当gap为3时，进入for循环（i），带入之前学习的插入排序，进入while循环 **{** **将与end相隔gap的数插入到由gap拆分的子序列中 }**，之后随着 **i ++**，**序列中的数依次进行在自己子区间中的插入排序**；
>
> （2）到最后进入while循环 gap = gap / 3 + 1 = 1，此时整个序列已经是基本有序了，再次执行插入排序，这样之后整个序列就变成有序的了✔️

```c
void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;    //特别注意：最后gap必须为 1 
		for (int i = 0; i < n - gap; i++)  //同上，注意i的范围
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{ 
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
					break;	
			}
			a[end + gap] = tmp;
		}
	}
}
```

### 1.2 堆排序

引入： 

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/386dcbeeda38419ca13d21a3761b679b.gif)

我们想想之前学习的完全二叉树的形状是不是也与堆相似呢堆的逻辑结构是一颗完全二叉树，而物理结构是一个数组（二叉树中结点位置就是数组的下标）⬇️； 

![](https://img-blog.csdnimg.cn/4b2edbbfa0064fdea0c037a41b3db19e.gif)

 既然是完全二叉树，那么就有父节点与子结点了，由以下公式可求出**左孩子、右孩子以及父节点的下标**：

**leftchild = parent * 2 +1         rightchild = parent * 2 + 2**

**parent = (child - 1) / 2**

堆又分为**大顶堆（树中所有父亲的值都大于或等于孩子）**和**小顶堆 （树中所有的父亲的值都小于或等于孩子）**例如⬇️：

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/c7eee9e75d35450d81f8390593d5af68.png)

 若给出一个数组，让判断是否是堆，那么就用图二中的方法将其逻辑化为一个完全二叉树，再判断其是否为大小堆；



 那么接下来我们一起来实现这个[堆排序](https://so.csdn.net/so/search?q=%E5%A0%86%E6%8E%92%E5%BA%8F&spm=1001.2101.3001.7020)（小堆）：

**建堆：（1）**若将一个数组建成一个小堆，首先我们需要用到**向下调整算法：**从根节点开始，我们需要其**左右子树均为小堆**，之后选择左右孩子中较小的一个，将其与根比较，若小于根的值则交换，然后继续往往下走，循环上面的步骤到叶结点。⬇️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/06f2faf0b93740868583d0ba3cef81ae.gif)

以下为向下调整算法的代码（解析写在了代码的注释当中）✔️： 

```c
void AdjustDown(int* a, int n, int root)    /*root为传入的数组下标*/
{
	int parent = root;
	int child = parent * 2 + 1;           /*用之前的公式先找到左孩子*/
 
		while (child < n)               /*注意 child < n */
		{
			if (child + 1 < n && a[child] < a[child + 1])    /*若右孩子较大，则将child+1*/
			{
				child += 1;
			}
			if (a[child] < a[parent]   /*如果想要得到大堆，只需要将<改成>即可，上面代码也要改*/      
			{
				Swap(&a[child], &a[parent]);
				parent = child;
				child = child * 2 + 1;         /*交换完之后需要转到子结点，再进入while循环*/
			}
			else
				break;
		}
}
```

**（2）**如果左右子树不是小堆，也就意味着不能使用**向下调整算法了**，那怎么让左右子树均为小堆呢？（结合两段代码）⬇️

要使每个子树均为小堆，那么我们**“从整棵树中最后的一颗小树起手”**，首先将随后一个叶结点的父亲传入（AdjustDown），对其使用向下调整算法，之后（ i -- ）到下一个结点，直至最后到第一个结点的时候（i= 0）将整棵树进行向下调整算法，及建得小堆。

我们画图分析：✔️

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/2110cd3c57404d8eb538db9a838f0a15.gif)

 由图，从“小树”开始，需要传入他的父节点，我们知道二叉树从上到下依次对应这数组的下标，那么最后一个叶结点的下标就为 **n - 1 ** (n为数组元素个数),其父节点由公式可得：**（n - 1 - 1）/ 2** 

```c
void HeapSort(int* a, int n)
{
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)   /* 建堆的时间复杂度O（N）*/
	{
		AdjustDown(a, n, i);
	}
        /*排升序，建大堆; 排降序，建小堆*/
	int end = n - 1;
	while (end > 0)
	{   
		Swap(&a[0], &a[end]);             /*整体时间复杂度为O( N * logN )*/
        end --;
		AdjustDown(a, end, 0);
	}
}
```

**排序：**

排升序，建大堆；排降序，建小堆；为什么呢？设想如果是**排降序**，建大堆，那么首先选出堆顶最大数，之后剩下的数又要重新建堆，效率就大打折扣了；

但如果是**建小堆**，那么每次将堆顶的元素，也就是最小的元素放在最后，在将其排出（**end --，**end指向的是最后一个元素），又因为左右子树是小堆，所以再次对**0到end**的数用向下调整算法，让堆顶的数再次变为最小值，再次循环⬆️

我们再看图分析：⬇️

 ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/4c83f64e02be4d8fb8abd8261f77c1ae.gif)

这样之后也就彻底完成堆排序了，步骤确实复杂有难度。俗话说好的东西需要时间的沉淀，那么堆排序有什么优缺点呢：

堆排序不同于希尔排序，不用考虑原始的排序状态，时间复杂度总体是**O( n*logn )**,但是因为是跳跃式的交换，堆排序是一种不稳定的排序。

### 1.3 快速排序—递归

**简介**：  
快速排序是Hoare于1962年提出的一种**二叉树结构**的交换排序方法，其基本思想为:任取待排序元素序列中的某元素作为**基准值**，按照该排序码将待排序集合分割成两子序列,左子序列中所有元素均小于基准值,右子序列中所有元素均大于基准值（升序）,然后左右子序列重复该过程，直到所有元素都排列在相应位置上为止。

总体思想是这样的——分区间加上递归，但是如何将两个区间分出来就是个问题了，接下来我们一起学习一下三种方法🙌

**方法（1）：**  
**挖坑法**：

> 选择一个关键字key = a\[begin\]（左边或者是右边）作为基准值，第一趟排完序之后，左边的值比key小，右边比key大，所以key的位置就可以不用动了，之后再递归key的左边和右边，循环以上步骤；
>
> 🔢我们先看里面的while循环，右边end--，直到找到比key小的值，将它放到提前挖好的坑里（**pivot = begin**，因为begin指向的值已经被key拷贝，所以可以覆盖），之后再将拿走的位置形成新的坑，让其放入从左边找到的比key大的值。
>
> 🔢经过之前的一趟下来只交换了两个数，没有保证key最后放置好后左边小右边大，所以还需要再上面的步骤上套一层while循环；
>
> 🔢当begin与end指向的位置相同，该位置也就是key存放的坑了；  图解如下⬇️
>
> 🔢联想二叉树，采用**分治递归**的方法将每个区间的左右区间变为有序，最后实现整个序列有序；

 ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/7da594dd16964e6cbe9c7bd1c6b8b2b8.gif)

```c
void QuickSort1 (int* a, int left, int right)
{
    if(left >= right){
    return;
    }                   //递归返回条件
    
	int begin = left, end = right;
	int key = a[begin];      
	int pivot = begin;
	while (begin < end)
	{
		while (begin < end && a[end] >= key)
		{
			end--;
		}
		a[pivot] = a[end];
		pivot = end;    //end空出变为新坑
 
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		a[pivot] = a[begin];
		pivot = begin;   //begin空出变为新坑
	}
	pivot = begin;    //此时  end=begin
	a[pivot] = key;
	QuickSort1(a, left, pivot - 1);    
    QuickSort1(a, pivot + 1, right); //将整个序列分为[left,pivot-1] [pivot] [pivot+1,right]
}
```

> **铺垫：**
>
> 之后的方法根挖坑法类似的，也是排完一个值，将左右区间递归，所以我们可以把这个步骤写成一个函数，**函数结束返回基准值的下标（方法一中的pivot）**，将不同的方法放入快速排序的函数中⬇️
>
> ```c
> void QuickSort(int* a, int left,int right)
> {
> 	if (left >= right)
> 	{
> 		return;
> 	}
> 	//int keyIndex = PartSort1(a, left, right);  方法一
> 	int keyIndex = PartSort2(a, left, right);    //方法二
> 	//int keyIndex = PartSort3(a, left, right);  方法三
> 	       
> 		QuickSort(a, left, keyIndex - 1);
>  
> 		QuickSort(a, keyIndex + 1, right);
> }
> ```
>
> 

方法（2）：

**左右指针法：**

> 🔢 while循环之前的步骤跟方法一是相同的，加上三数找中，将三个数中不大不小的放在第一位；
>
> 🔢 **先看里面的那层while循环：**跟挖坑法一样，从左边找大，从右边找小，之后将大于key和小于key的值交换   
>
> **     ※特别注意：****while的判断条件里必须加上  begin < end ，设想如果从右边找，所有数都大于key的值，那么end就会减到begin的左边，end就越界了，所以每次进入while循环都需要对begin与end比较大小。✔️**
>
> 🔢 **之后看外面的一层循环：**若begin < end ，继续循环第二步，直到begin与end指向同一位置，该位置及为基准值存放的位置（代码注释里有其余的补充说明⬇️）
>
> 🔢 函数结束将begin（end）传回QuickSort函数，再递归左右区间。

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/93cfb11b67bb4be7afe3c122eaf6b40d.gif)

在画图分析时，我发现必须先从后开找，如果先从前找大的话，画图后的结果是错的，这个等待之后的确认吧 

```c
int PartSort2(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);
	Swap(&a[index], &a[left]);   //后续改良介绍的三数取中
 
	int begin = left ,end = right;
	int key = begin;
	while (begin < end)
	{
        while (begin < end && a[end] >= a[key])    //后面的>= 也是必需的，大家可自行画图理解
		{
			end--;
		}
 
		while (begin < end && a[begin] <= a[key])
		{
			begin++;
		}
		
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin], &a[key]);   //因为key在首元素没有动，所以直接与begin指向的位置交换
	return begin;
}
```

**方法（3）：**

**前后指针法： **

> 🔢 跟之前两个方法相似，三数去中后将第一个元素定为key
>
> 🔢 **定义两个指针，cur指向prev的后面一个，让cur向后移去找比key小的值，找到之后停住cur，将prev向后移一位，将cur与prev指向的值交换（若两者指向同一位置就可不用交换了）**
>
> 🔢 当cur找完整个序列之后，prev指向的就是基准值带存放的位置了，最后将prev指向的值与key交换，本次排序即可完成
>
> 🔢 函数结束将prev传回QuickSort函数，再递归左右区间。⬇️

（图中的key实际上是下标，key = 0，a\[key\] = 6）

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/76129c47ff264dcea82ccd2817c73d49.gif)

 当cur指向的数小于a\[key\]时，prev++，所以到最后prev之前的值肯定都比a\[key\]的值小了

```c
int PartSort3(int* a, int left, int right)
{
	int index = GetMidIndex(a, left, right);
	Swap(&a[index], &a[left]);
 
	int key = left;
	int prev = left, cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] < a[key] && ++prev!= cur)  //如果小于再执行后面一句让++prev，前置++，先加后                                           
			Swap(&a[prev], &a[cur]);          //然后判断prev与cur是否相等，如果相等可省去交换
		cur++;
	}
 
	Swap(&a[prev], &a[key]);
	return prev;
}
```

**快排总结：**

到此为止，快速排序的三种方法就讲解到这里了；**快排的核心思想其实就是通过一次排序将一个数排到它最后属于的位置，然后以他为界递归左右区间**

**时间复杂度：O（logn）**



### 1.4 归并排序—递归

**引入：**

归并排序是目前为止我认为最复杂的排序了，要弄懂归并排序需要对递归以及[二叉树](https://blog.csdn.net/Dusong_/article/details/127061544?spm=1001.2014.3001.5502 "二叉树")有更深层次的理解；

归并排序的理解非常抽象，**简单来说就是将一个无序序列不断分成两个序列，直到分成单独元素，然后开始归并：将两两序列归并成有序序列**，具体如何实现，我们一起看下面代码和图解。

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/d6cf8c09b63e42e3a70b22cf1f2e447a.png)

**解析：**

> **🔢 **因为需要将数归并回去，所以我们需要创建一个临时空间（malloc）
>
> 🔢 当left >= right,说明递归到只有一个元素，这时候就可以返回去归并了
>
> 🔢 后面定义五个变量指向不同位置，左右区间的开头和结尾，以及临时数组的开头；后面的代码实现起来就简单了：比较大小，将小的数放在临时数组里，如果遇到一个区间的数放完，另一个区间有剩的，直接将剩下区间的数挨个放入。

说着简单，但是代码如何运行、如何递归的以及为什么这样写是个问题，接下来我用视频录制的方法将我理解的思路分享给大家   ⬇️

[《归并排序的递归过程》](https://live.csdn.net/v/251573?spm=1001.2014.3001.5501)(视频讲解)

**视频中我只讲递归的代码截图了，在看时需要直到当右区间递归完之后，紧接的就是将本次的左右区间归并成一个有序序列✔️**

 看了视频之后有没有发现这个递归步骤很想之前讲解二叉树中的**后序遍历🤔**

```c
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;
 
	int mid = (left + right) >> 1;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);
 
	//归并
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
 
	for (int i = left;i <= right; i++)
	{
		a[i] = tmp[i];
	}
}
 
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
} 
```

八、改良排序
------

### 2.1 三数找中

我们回想一下之前学习的快速排序，如果每次选择的**key**都位于排序之后的**中间值**，那么这个排序就无限地接近于二叉树(**O(logn)**)地结构了，排序地效率会大大增加。

将序列地头尾以及中间值比较大小⬇️

```c
int GetMidIndex(int* a, int left, int right)
{
	int mid = (left + right) >> 1;//除2；
	if (a[left] < a[mid])
	{
		if (a[right] > a[mid])
			return mid;         //a[left] < a[mid] < a[right]
		else if (a[left] > a[right])
			return left;     //a[right] < a[left] < a[mid]
		else
			return right;    //a[left] < a[right] < a[mid]
	}
	if (a[left] > a[mid])
	{
		if (a[mid] > a[right])
			return mid;
		else if (a[right] > a[left])
			return left;
		else
			return right;
	}
}
```

### 2.2 小区间优化

通过之前对快速排序（递归）的了解，当分成的很小的递归区间时，还要通过递归左区间和右区间；如果需要排序的是一串很长的数字，到最后递归区间只有几个数时，需要递归的次数变得非常多，效率自然就低了，这样不如直接对剩余的小区间序列用之前学习的排序方法，一次性将其排序🤔

 那么选择何种排序呢？

**首先排除冒泡和选择这两个效率较低的排序，从插入和希尔排序，因为最后待排序数量较小，所以直接用较为简单的[插入排序](https://blog.csdn.net/Dusong_/article/details/127061544?spm=1001.2014.3001.5502 "插入排序")就行了。**

所以更改之后的代码如下  ⬇️

```c
if (keyIndex - 1 - left > 10)   //可根据待排序的总量确定小区间优化的范围
		QuickSort(a, left, keyIndex - 1);
else
		InsertSort(a + left, keyIndex - 1 - left + 1);
 
if (right - (keyIndex + 1) > 10)
		QuickSort(a, keyIndex + 1, right);
else
		InsertSort(a + keyIndex + 1, right - (keyIndex + 1) + 1);
```

 如果这里对插入排序有遗忘的，可以返回去看[插入排序的内容![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/icon-default.png)https://blog.csdn.net/Dusong_/article/details/127061544?spm=1001.2014.3001.5502](https://blog.csdn.net/Dusong_/article/details/127061544?spm=1001.2014.3001.5502 "插入排序的内容")

回来我们继续看，传入插入排序的第一个参数是数组及**排序的首元素—\> 数组名＋n表示数组下标为n的地址**，第二个参数是待排序个数，所以需要对，（**keyIndex - 1**） **\- left   再加上1(左区间)** /  right - (keyIndex + 1)  再加上1(右区间)；

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/11a9febd987a4a79a43fb606f6094755.png)

* * *

**•** 之前学习的快速排序和归并排序都是用递归来实现的，但是递归有个致命的缺陷，那就是**当递归调用栈帧的深度非常深的时候就会导致****栈溢出（Stack overfolw）**，所以想要完全吃透快排和归并我们还需要掌握他的非递归算法

**•** 将递归改成非递归的方法有两种：① 直接用循环，

​                                                    ② 用[数据结构的栈](https://blog.csdn.net/Dusong_/article/details/127061544?spm=1001.2014.3001.5502 "数据结构的栈")模拟递归过程。

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/0fcc3d29cc314760bf95a1b1beaae0fd.gif)

### \* 2.3 快速排序—非递归

> 我们用之前数据结构学习的栈（先进后出）模拟内存中递归开辟的栈帧：
>
> 🔢 首先初始化一个栈，将序列的头尾进行压栈
>
> 🔢 当栈里没有数据时，循环停下；进入循环，抽出栈中的一个序列（用left，right指向范围里的一个区间），对其进行一次排序
>
> 🔢 排完一个数之后再模拟之前的递归快排，将左右区间压入栈中，（**※注意：要想先排左区间，就得后压左区间**），再次循环，将一个区间出栈，再次进行一次排序，直到区间里只有一个数为止
>
> （具体栈的应用在代码块的注释之中），我们再次用画图的方式解析这个过程（部分）⬇️

 ![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/6d62cb8b0e5349b48b5f9c8edaafff0d.gif)

```C
void QuickSortNonR(int* a, int n)
{
	ST st;   //创建栈
	StackInit(&st);  //初始化
	StackPush(&st, n - 1);
	StackPush(&st, 0);
 
	while (!StackEmpty(&st))
	{
		int left = StackTop(&st);    //后压的是左边，所以先取出
		StackPop(&st);
		int right = StackTop(&st);
		StackPop(&st);
 
		int keyIndex = PartSort1(a, left, right);   //这里选择之前的三种方法中的其中一种
 
		if (keyIndex + 1 < right)
		{
			StackPush(&st, right);
			StackPush(&st, keyIndex + 1);
		}
		if (keyIndex - 1 > left)
		{
			StackPush(&st, keyIndex-1);
			StackPush(&st, left);
		}
	}
	StackDestory(&st);   //销毁，防止内存泄漏
}
```

创建的栈是malloc出的，在堆上申请的空间，而函数调用是在栈上调用的空间，而堆的空间是远大于栈的，所以完全不用考虑堆的空间不够用的情况

### \* 2.4 归并排序—非递归

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/708bfac6d5dc4cad88b9f7e380f047a7.png)

> **•**  如图，直接设定一个间隔（类似与希尔排序），先一个一个排序，再两个两个的排序，对间隔（gap）每次乘2；
>
> **•** 所以对于gap的控制就非常的复杂了，我们直接用图来解析这个gap变化的过程⬇️
>
> **•** 其中的**排序部分跟之前的递归版归并排序是一样的**

![](https://typora-dusong.oss-cn-chengdu.aliyuncs.com/d1747c8e27e045bca1f7d0f8b4e7ea1f.gif)

```C
void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
 
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			int index = i;
 
			if (begin2 >= n)
				break;           //右半区间不存在的情况
			if (end2 >= n)
				end2 = n - 1;    //右区间的右边可能越界
 
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
					tmp[index++] = a[begin1++];
				else
					tmp[index++] = a[begin2++];
			}
			while (begin1 <= end1)
			{
				tmp[index++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[index++] = a[begin2++];
			}
			for (int j = i; j <= end2; j++)
				a[j] = tmp[j];
		}
		
		gap *= 2;
	}
	free(tmp);
}
```

