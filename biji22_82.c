笔记
一、c语言
{	
C语言程序的编译流程

从 高级语言->汇编语言->机器语言（二进制）
1. 预处理编译器：cpp gcc -E hello.c -o hello.i 头文件展开，宏替换，注释去掉
2. 编译器：gcc gcc -S hello.i -o hello.s c文件变成汇编文件
3. 汇编器：as gcc -c hello.s -o hello.o 汇编文件变成二进制文件
4. 链接器：ld gcc hello.o -o hello 将函数库中相应的代码组合到目标文件中

● 预处理
	由.c文件到.i文件，这个过程叫预处理。预处理过程实质上是处理“#”，将#include包含的头文件直接拷贝到hell.c当中；
	将#define定义的宏进行替换，同时将代码中没用的注释部分删除等

具体做的事儿如下：
（1） 将所有的#define删除，并且展开所有的宏定义。说白了就是字符替换
（2） 处理所有的条件编译指令，#ifdef #ifndef #endif等，就是带#的那些
（3） 处理#include，将#include指向的文件插入到该行处
（4） 删除所有注释
（5） 添加行号和文件标示，这样的在调试和编译出错的时候才知道是是哪个文件的哪一行
（6） 保留#pragma编译器指令，因为编译器需要使用它们。

● 编译
由.i文件到.s文件，这个过程叫编译。编译的过程实质上是把高级语言翻译成机器语言的过程
1. 词法分析
2. 语法分析
3. 语义分析
4. 优化后生成相应的汇编代码

● 汇编
由.s文件到.o文件，这个过程叫汇编。汇编过程实际上指把汇编语言代码翻译成目标机器指令的过程。

● 链接
由.o文件到可执行文件，这个过程叫链接。就像刚才的hello.
c它使用到了C标准库的东西“printf”，但是编译过程只是把源文件翻译成二进制而已，这个二进制还不能直接执行，这个时候就需要做一个动作，将翻译
成的二进制与需要用到库绑定在一块。
	
● 隐式转换
低精度 --> 高精度
有符号 --> 无符号
double b  = (double)a;   这里对a本身没有改变

在C语言中，0为假，非0为真

day8 7.14

 指针和二维数组
二维数组的数组名表示该数组首行的地址
		
int a[2][3] = {1,2,3,4,5,6};
				
行指针(数组指针):
	<存储类型> <数据类型> (*数组指针变量名)[列数];
	例：
		int a[2][3] = {1,2,3,4,5,6};
		int (*p)[3] = a;
	
	p = &a[0];
	p+1 = &a[1];
	*(p+1) = a[1];
	**(p+1) = a[1][0];
	
	*(*(p+n)+n) == a[n][n];
	
day9 7.15
	
				char *x = "hello";
			将一个字符串赋给一个字符指针变量，实际上是将该字符串的首地址赋给字符指针变量
			
			注意：如果将一个字符串赋给一个字符指针变量后，则不能通过该指针变量修改字符串的内容
			*x = 'z'; //error
			
2、指针数组
			定义的一般形式
				<存储类型> <数据类型> *指针数组名[元素个数];
					int a[2][3] = {1,2,3,4,5,6};
					
					int *b[2]; //定义了一个指针数组，可以存放2个指向内容为int类型数据的地址
					
					b[0] == a[0]
					b[1] == a[1]
					
					*b[0] == *a[0] == a[0][0] == 1	
					
					
3、多级指针
		int a = 10;
		int *p = &a;
		
		一个指向一级指针的指针叫二级指针
			int **q = &p;
			*q == p
			**q == *p == a == 10;
			
		指针数组的数组名可以看作一个二级指针
		数组指针不是一个二级指针					
		
		
		
4、const指针
		(1) const int *p;
			将*p修饰为只读，不能通过*p访问指针内容去修改值
			但是可以通过修改p的地址来修改值
			
		(2) int const *p;  (同(1))
	
		(3)
			int * const p;
			将指针变量p修饰为只读，不能更改p的地址，
			但是可以通过访问修改地址中的内容		
			
	memset(b, 0, sizeof(b));	
	//将指定数据清0 参数1：清空内容的首地址 参数2： 0（清空） 参数3：清空内容长度	
	
	
typedef 和 #define 的区别

	typedef 在表现上有时候类似于 #define，但它和宏替换之间存在一个关键性的区别。正确思考这个问题的方法就是把 typedef 
	看成一种彻底的“封装”类型，声明之后不能再往里面增加别的东西。

	1 可以使用其他类型说明符对宏类型名进行扩展，但对 typedef 所定义的类型名却不能这样做。如下所示：
		#define INTERGE int
		unsigned INTERGE n;  //没问题

		typedef int INTERGE;
		unsigned INTERGE n;  //错误，不能在 INTERGE 前面添加 unsigned


	2 在连续定义几个变量的时候，typedef 能够保证定义的所有变量均为同一类型，而 #define 则无法保证。例如：
		#define PTR_INT int *
		PTR_INT p1, p2;
		
	经过宏替换以后，第二行变为：
		int *p1, p2;

	这使得 p1、p2 成为不同的类型：p1 是指向 int 类型的指针，p2 是 int 类型。

	相反，在下面的代码中：
		typedef int * PTR_INT
		PTR_INT p1, p2;

		p1、p2 类型相同，它们都是指向 int 类型的指针。
	
	

#ifndef _MYHEAD_H
#define _MYHEAD_H

#endif

}

二、Linux
{

inux 系统核心支持十多种文件系统类型：jfs,ReiserFS,ext,ext2,ext3,iso9660,xfs,minx,msdos,umsdos,Vfat,NTFS,Hpfs,Nfs,smb,sysv,proc 等.


mkdir day{1..10} 创建day1 day2 day3 ... day10 10个文件

mkdir -p aa/kk/mm 递归创建文件 

echo hello >> empty.c  将hello打印在empty.c 文件的最后面


#include<unistd.h>   
sleep(1)
usleep(1000)



df 查看磁盘空间
		-h   以k M 显示大小
	free 显示内存空间
	
系统维护指令：
	shutdown		关机 
		-h  now
		-h +45 
		-h +45 "game over"
	
	shutdown -r 	重启
	reboot 	now


shell编程 
测试命令test
1.测试字符串
    test -z 字符串
	测试该字符串长度是否为0，若为0则结果为0，若不为0则结果为1。
	
	test -n 字符串
	测试该字符串长度是否不为0，若不为0则结果为0，若为0则结果为1。（通常不需要-n，它代表默认操作，可以用-z选项来实现）
	
2.测试整数关系

a -eq b	测试a与b是否相等
a -ne b	测试a与b是否不相等
a -gt b	测试a是否大于b
a -ge b	测试a是否大于等于b
a -lt b	测试a是否小于b
a -le b	测试a是否小于等于b



}

三、数据结构
{
	
数据结构的两种结构
1，逻辑结构

是指数据对象中数据元素之间的相互关系

	逻辑结构分为以下四种：

        集合结构：指数据元素除了属于同一集合外，它们之间没有其他关系

        线性结构：线性结构中的数据元素之间是一对一的关系

        树形结构：数据元素之间存在一对多的层次关系

        图形结构：数据元素之间存在多对多的关系

2，物理结构

是指数据的逻辑结构在计算机中的存储形式

    数据元素的存储结构形式有如下两种：

        顺序存储结构：是把数据元素存放在地址连续的存储单元里，其数据间的逻辑关系和物理关系是一致的

        链式存储结构：是把数据元素存放在任意的存储单元里，这组存储单元可以是连续的，也可以是不连续的


判断是否为循环链表： 用两个遍历速度不一样的指针


顺序表
链式顺序表
数据栈
链式栈
数组队列
链式队列
数组树
链式树


二叉树的层序遍历
	要进行层次遍历，需要建立一个循环队列。 先将二叉树头结点入队列，然后出队列，访问该结点，如果它有左子树，则将左子树的根结点入队:
	如果它有右子树，则将右子树的根结点入队。 然后出队列，对出队结点访问，如此反复，直到队列为空为止。

}

四、IO进线程
{
	
	进程：

是并发执行的程序在执行过程中分配和管理资源的基本单位，是一个动态概念，竞争计算机系统资源的基本单位。



线程：

是进程的一个执行单元，是进程内科调度实体。比进程更小的独立运行的基本单位。线程也被称为轻量级进程。



协程：

是一种比线程更加轻量级的存在。一个线程也可以拥有多个协程。其执行过程更类似于子例程，或者说不带返回值的函数调用。





二、进程和线程的区别



地址空间：

线程共享本进程的地址空间，而进程之间是独立的地址空间。



资源：

线程共享本进程的资源如内存、I/O、cpu等，不利于资源的管理和保护，而进程之间的资源是独立的，能很好的进行资源管理和保护。



健壮性：

多进程要比多线程健壮，一个进程崩溃后，在保护模式下不会对其他进程产生影响，但是一个线程崩溃整个进程都死掉。



执行过程：

每个独立的进程有一个程序运行的入口、顺序执行序列和程序入口，执行开销大。

但是线程不能独立执行，必须依存在应用程序中，由应用程序提供多个线程执行控制，执行开销小。



可并发性：

两者均可并发执行。



切换时：

进程切换时，消耗的资源大，效率高。所以涉及到频繁的切换时，使用线程要好于进程。同样如果要求同时进行并且又要共享某些变量的并发操作，只能用线程不能用进程。



其他：

线程是处理器调度的基本单位，但是进程不是。
	
	
并发执行机制原理：
	简单地说就是把一个处理器划分为若干个短的时间片，每个时间片依次轮流地执行处理各个应用程序，由于一个时间片很短，相
	对于一个应用程序来说，就好像是处理器在为自己单独服务一样，从而达到多个应用程序在同时进行的效果 。
	
	
8.4 I/O  动态、静态库的创建

静态库的创建：
gcc -c fun.c  -->  fun.o  //fun.c 为需要做成静态库的功能函数
ar crs libmystatic.a fun.o  // libmystatic.a 为成为的静态库，  lib -> 库文件的前缀， static为此静态库的

静态库的使用：
gcc test.c -L. -lmystatic -static  //test.c 为链接静态库的主函数

动态库的创建：
gcc -fPIC -wall -c hello.c -> hello.c 为需要做成动态库的功能函数 
gcc -shared -o libmyhello.so hello.o
	-fPIC 用来创建于地址无关的编译程序

动态库的使用：
gcc test.c -L. -lmystatic

因为动态库没有直接存放在a.out文件中，所以每次运行时才会去链接动态库文件，
所以就有动态库的路径问题
为了让执行程序顺利找到动态库，有三种方法：
（1）把库拷贝到/usr/lib和/lib目录下。
（2）在LD_LIBRARY_PATH环境变量中加上库所在路径。
方法：在终端中输入: exprot LD_LIBRARY_PATH=库所在路径 // echo $LD_LIBRARY_PATH 查看
//此方法在新终端无效
（3）添加/etc/ld.so.conf.d/\*.conf文件，把库所在路径加到文件末尾，并执行ldconfig刷新。
这样，加入的目录下的所有库文件都可见。
比如：
	1.新建并编辑 /etc/ld.so.conf.d/my.conf文件，加入库文件所在目录的路径。
	2.运行ldconfig，该命令会重建/etc/ld.so.conf.d/my.conf文件
	
	
8.5 线程

创建线程：
int pthread_create(pthread_t *tid,pthread_attr_t *attr,void* (*handler)(void*),
				void *arg);
	tid:要创建的线程
	attr:创建线程的属性：NULL默认属性
	handler:线程执行函数
	arg:给线程执行函数传参
    返回值：0成功，-1失败
线程退出：
	void pthread_exit(void* arg);
		arg:线程退出时返回值的状态
    int pthread_join(pthread_t tid,void** result);
		tid：指定的线程
		result:保存子线程退出时返回的值


总结：

创建线程时传参：
	函数接收的是void * 类型数据 （ps：函数声明很重要!）
接收并打印结束线程时的返回信息：
	首先要创建一个void *类型的指针，用来接收线程结束时的返回信息，打印时在强制类型转换为对应的数据类型指针 如（char *）



解决线程 运行时的冲突问题

互斥锁
同步锁sem


进程间通信：
	1、unix：无名管道，有名管道，信号
	2、system v:共享内存，消息队列，信号灯集   
	3、BSD：socket 



1.守护进程：
	在linux中与用户交互的界面叫终端，从终端运行起来的程序都依附于这个终端，
	当终端关关闭时，相应的进程都会被关闭，守护进程可以突破这个限制。

2.特点：
	在后台服务的进程
	生存期很长
	守护进程独立于控制终端
	比如：init进程 pid=1 开机运行 关机才结束
创建守护进程：
1、创建子进程，父进程退出，
	fork();
	exit();
2、创建新的会话
	setsid();
3、更改进程的工作目录
	chdir("/");
4、修改文件的权限掩码
	umask(0);
5、关闭不需要的文件
	getdtablesize();
	close();
	while(1)
	{
		
	}

进程间通信的方式
	无名管道（只能在亲缘管道间通信） pipe
	有名管道 （任一文件间都可以通信）fifo    有名管道 + 线程 -> 可以实现文件之间的copy

信号  
	signal（信号量，要执行的函数）  -> 注册信号
	kill （想把信号发送给哪个进程的pid， 信号量）
	
进程间通信的最高效的方式
共享内存         共享内存 + 信号 -> 进程间的通信   


还可以使用消息队列进行进程间的通信       消息队列 + 线程  -> 进程间通信（每个进程里有两个线程，主函数负责循环发送，线程函数负责接收打印信息）

信号灯     信号灯一般配合共享内存使用


IPC操作：	内存共享， 消息队列， 信号灯

消息队列 （是消息的链表，存放在内核中）
int msgget (key_t key, int flag);
/***************************************************

*Description: 	创建或打开消息队列
*Input：	  	key： key值 （IPC_PRIVATE 或 ftok的返回值）
				flag：标志（同open函数的权限位，或上IPC_CREAT）
*Return：		成功返回队列ID，失败返回-1

***************************************************/

消息报类型
struct msgbuf {
	long mtype;		/*消息类型，必须 > 0*/
	char mtext[N]; 	/*消息文本*/
};

int msgnd (int msqid, const void *ptr, size_t size, int flag);
/******************************************************************

*Description:	发送消息
*Input：		msqid:	id
				ptr:	消息包地址（发送）
				size:	消息包正文大小
				flag：	方式（0：阻塞方式 IPC_NOWAIT： 表示非阻塞方式）
*Return：		成功返回0， 失败返回-1

*******************************************************************/

共享内存的实现

步骤：
	1. ftok
	2. shmget
	3. shmat
	4. 进程间通信 fork
	5. shmdt
	6. shmctl

消息队列的实现

}

五、网络编程
{

网络字节序与主机字节序的概念
	字节序分为主机字节序和网络字节序，主机字节序又称小端字节序，是低字节存放在低地址，而网络字节序又称大端字节序，是低字节放在高地址。

并发服务器
	：同一时刻，能够响应多个客户端的请求

三种并发服务器模型
	
1.多进程并发服务器
	基本原理：每连接一个客户，创建一个子进程， 子进程负责处理客户请求(connfd)，
			  父进程负责建立连接(sockfd)
//注意：客户端退出时，关闭连接套接字
//      子进程结束时，需要进行资源回收（处理僵尸）

	
2.多线程并发服务器
	基本原理：每连接一个客户，创建一个子线程， 子线程负责处理客户请求(connfd)，
			  主线程负责建立连接(sockfd)
//注意：客户端退出时，关闭连接套接字
//		子线程结束时，需要进行资源回收

3.IO复用服务器
	I/O 复用技术是为了解决进程或线程阻塞到某个 I/O 系统调用而出现的技术，使进程不阻塞于某个特定的 I/O 
	系统调用。它也可用于并发服务器的设计，常用函数 select() 或 epoll() 来实现。

IO多路复用

1 select机制
	基本原理： 创建一张表，把相关文件描述添加到表中，通过select函数进行轮询检测，
	一旦有文件描述符准备好了，select函数返回，然后扫描到对应的文件，进行读写操作。
2 poll机制
3 epoll机制



超时检测

方法1：
	设置套接字属性，设置接收超时
	
方法2：
	设置select函数或poll函数的超时值

方式3：
	设置闹钟实现，超时检测


sqlite3常用sql语句
注意常见的数据类型：int,float,text(char)	
create table usr (name text, passwd text);  			//创建表
create table usr (name text primary key, passwd text);  //创建表 以name作为主键
insert into usr values ("jack","ps666");    			//向表中插入数据
select * from usr;                          			//查询表中数据 
select * from usr where name="rose" and passwd="ps777"; //按规则查找
delete from usr where name="rose";                      //删除指定记录项
update usr set passwd="abc123xyz" where name="lilei";   //更新表
drop table usr;   										//删除表

}

六、C++
{
	
new delete 是运算符，malloc,free是函数
malloc与free是C++/C语言的标准库函数，new/delete是C++的运算符。它们都可用于申请动态内存和释放内存。

什么是内联函数
用关键字inline修饰的函数就是内联函数。关键字在函数声明和定义的时候都要加上，不写系统还是会当成常规函数
https://blog.csdn.net/qq_33757398/article/details/81390151

&：引用不能引用常量

explicit 关键字的作用就是防止 类构造函数 的 隐式自动转换.

模板：

	使用模板类时要显示声明 (即使模板类有默认参数，在声明对象时要有<>)
		例：Data<> a;
			Data a //error
			
C++多重继承里的一种特殊继承方式菱形继承可能会引发二义性，可以使用虚继承（继承时加virtual关键字）的方法来解决这种问题。
	虚继承底层是使用了一个虚表；
	



概念
封装wrap：
	实现细节隐藏，使得代码模块化。把成员数据和成员函数封装起来，通过公共的成员接口进行成员数据的操作。
继承inheritance：
	扩展已存在的代码，目的是为了代码的重用
多态polymorphism：
	多态按字面意思就是“多种状态”，简单地概括为“一个接口，多种方法”，程序在运行时才决定调用的函数。
	目的是为了接口重用。也就是说，不论传递过来的究竟是那个类的对象，函数都能够通过同一个接口调用到适合各自对象的实现方法。
	有时候，希望子类和基类有相同的方法，但是行为却有所不同，这就是多态。这里就引入了虚函数的概念。
	注意：简单的继承，is-a的关系不是多态；
虚函数(virtual function)
	简单的说，用virtual修饰的成员函数，就是虚函数。虚函数的作用就是实现多态性。多态性是将接口与实现进行分离；用形象的语言解释
	就是实现以共同的方法，但因个体差异，而采用不同的策略。
	
C++中，构造函数不可以是虚函数，而析构函数可以且常常是虚函数。
不建议在构造函数和析构函数里面调用虚函数。
	虚函数调用是在部分信息下完成工作的机制，允许我们只知道接口而不知道对象的确切类型，要创建一个对象，你需要知道对象的完整信息。 特别是，你需要知道你想要创建的确切类型。 因此，构造函数不应该被定义为虚函数。
	1.因为只有在构造函数里把对象实例化后才会有虚函数表，所以构造函数不在虚函数表里；
	2.因为构造函数是创建对象时自动调用的，不能主动调用；
	
成员函数的隐藏
	在不同的作用域中，基类中与派生类中有相同的函数（函数名，参数类型、个数、次序），但是基类中的函数并没有用virtual关键字修饰，
	此时基类中的同名函数是隐藏在派生类中。当在基类中加上virtual关键字修饰后，在派生类中就叫做覆盖或者重写。
	
成员函数覆盖（override，也称重写）
	是指派生类重新定义基类的虚函数，特征如下：
	A、不同的作用域（分别位于派生类与基类）
	B、函数名字相同
	C、参数相同
	D、基类函数必须有virtual关键字，不能有static
	E、返回值类型相同
	F、重写函数的权限访问限定符可以不同
成员函数重载（overload）
	是指函数名相同，参数不同（数量、类型、次序），特征如下：
	A、相同的范围（在同一个作用域中）
	B、函数名字相同
	C、参数不同
	D、virtual关键字可有可无
	E、返回值可以不同
运算符重载

1.可重载的运算符列表：
双目算术运算符	+ (加)，-(减)，*(乘)，/(除)，% (取模)
关系运算符	==(等于)，!= (不等于)，< (小于)，> (大于)，<=(小于等于)，>=(大于等于)
逻辑运算符	||(逻辑或)，&&(逻辑与)，!(逻辑非)
单目运算符	+ (正)，-(负)，*(指针)，&(取地址)
自增自减运算符	++(自增)，--(自减)
位运算符	| (按位或)，& (按位与)，~(按位取反)，^(按位异或)，<< (左移)，>>(右移)
赋值运算符	=, +=, -=, *=, /= , % = , &=, |=, ^=, <<=, >>=
空间申请与释放	new, delete, new[ ] , delete[]
其他运算符	()(函数调用)，->(成员访问)，,(逗号)，[](下标)

2.不可重载的运算符列表：
1. .(点运算符),通常用于去对象的成员,但是->(箭头运算符),是可以重载的
2. ::(域运算符),即类名+域运算符,取成员,不可以重载
3. .*(点星运算符,)不可以重载,成员指针运算符".*,即成员是指针类型
4. ?:(条件运算符),不可以重载
5. sizeof(大小长度运算符),不可以重载


什么函数不能声明为虚函数

	普通函数（非成员函数）、静态成员函数、内联成员函数、构造函数、友元函数都不能声明为虚函数
	
	静态成员函数不能是虚函数；
		静态函数，它其实就是普通函数。静态函数跟类实例没有关系，用a1和a2去调用结果一致，甚至于可以用A.fun2()的方式调用。
		静态函数调用时不会隐式传入this指针。
		简而言之，成员函数实例相关，静态函数类相关。
	内联函数不能为虚函数；
	构造函数不能是虚函数；
	析构函数可以是虚函数，而且通常声明为虚函数


纯虚函数

	纯虚函数是一种特殊的虚函数，它的一般格式如下(C++格式)：
	class <类名>
	{
	virtual <类型><函数名>(<参数表>)=0;
	…
	};
	
	纯虚函数可以让类先具有一个操作名称，而没有操作内容，让派生类在继承时再去具体地给出定义。凡是含有纯虚函数的类叫做抽象类。这种类不能声明对象，只是
	作为基类为派生类服务。除非在派生类中完全实现基类中所有的的纯虚函数，否则，派生类也变成了抽象类，不能实例化对象。
	
	一般而言纯虚函数的函数体是缺省的，但是也可以给出纯虚函数的函数体（此时纯虚函数仍然为纯虚函数，对应的类仍然为抽象类，还是不能实例化对象）调用纯虚
	函数的方法为：抽象类类名::纯虚函数名(实参表)
	
多态性

	指相同对象收到不同消息或不同对象收到相同消息时产生不同的实现动作。C++支持两种多态性：编译时多态性，运行时多态性。
	a.编译时多态性：通过重载函数和运算符重载实现。
	b运行时多态性：通过虚函数和继承实现。
	
C++中的多态可分为静态多态和动态多态，这两种形式的多态在实现机制上有着本质的差别。
	静态多态可以称为编译期多态，它是在编译期间通过函数重载和运算符重载的方式决定被调用函数的
	动态多态可以称为运行期多态，它可以通过继承和虚函数来实现。实现时，编译器将在进程运行的过程中动态的捆绑想要调用的函数	

构造函数为什么不建议调用虚函数？
	为了安全
	当实例化一个派生类对象时，首先进行基类部分的构造，然后再进行派生类部分的构造。
	基类部分在派生类部分之前被构造，当基类构造函数执行时派生类中的数据成员还没被初始化。如果基类构造函数中的虚函数调用被解析成调用派生类的虚函数，而派
	生类的虚函数中又访问到未初始化的派生类数据，将导致程序出现一些未定义行为和bug。
	
拷贝构造函数（复制构造）

	#include<iostream>
	using namespace std;
	class Complex{
	public:
		double real, imag;
		Complex(double r,double i){
			real = r; imag = i;
		}
		Complex(const Complex & c){
			real = c.real; imag = c.imag;
			cout<<"Copy Constructor called"<<endl ;
		}
	};
	
	int main(){
		Complex cl(1, 2);
		Complex c2 (cl);  //调用复制构造函数
		cout<<c2.real<<","<<c2.imag;
		return 0;
	}

智能指针
	在C++中，动态内存的管理是用一对运算符完成的：new和delete，new:
	在动态内存中为对象分配一块空间并返回一个指向该对象的指针，delete：指向一个动态独享的指针，销毁对象，并释放与之关联的内存。

	动态内存管理经常会出现两种问题：一种是忘记释放内存，会造成内存泄漏；一种是尚有指针引用内存的情况下就释放了它，就会产生引用非法内存的指针。

	为了更加容易（更加安全）的使用动态内存，引入了智能指针的概念。智能指针的行为类似常规指针，重要的区别是它负责自动释放所指向的对象。标准库提供的两
	种智能指针的区别在于管理底层指针的方法不同，shared_ptr允许多个指针指向同一个对象，unique_ptr则“独占”所指向的对象。标准库还定义了一种名为weak_
	ptr的伴随类，它是一种弱引用，指向shared_ptr所管理的对象，这三种智能指针都定义在memory头文件中。


C++ class和struct到底有什么区别

	C++中的 struct 和 class 基本是通用的，唯有几个细节不同：
		使用 class 时，类中的成员默认都是 private 属性的；而使用 struct 时，结构体中的成员默认都是 public 属性的。
		class 继承默认是 private 继承，而 struct 继承默认是 public 继承。
		class 可以使用模板，而 struct 不能。


}

七、Qt
{
信号与槽：发送信号
		
	signal一般是在事件处理时候Qt发出，如果需要程序自己触发信号，则使用emit。
	使用语法如下：
		emit signal
		
对话框
{
	
	1.文件对话框（QFileDialog）
	
		1.getOpenFileName()
		
		QString filename = QFileDialog::getOpenFileName(this, "Open Document",
														QDir::currentPath(),
														"Document files(*.doc *.rtf);; All files(*.*)");
		if (!filename.isNull())
		{
			...
		}
		
		2.getSaveFileName()
		
		QString filename = QFileDialog::getSaveFileName(this, "Save Document",
														QDir::currentPath(),
														"Documents(*.doc);; All files(*.*)");
		...
		
		3.getExistingDirectory()
		
		QString dirname = QFileDialog::getExistingDirectory(this, "Select a Directory",
														QDir::currentPath());
		...
	
	2.消息对话框（QMessageBox）
		
		about()
		aboutQt()
		critical()
		information()
		question()
		warning()
		
			QMessage::XXX(this, "Application Name", "An XXX ,message.");
			
	3.输入对话框（QInputDialog）
		
		getText()
		getItem()
		getInteger()
		getDouble()
		
	4.颜色对话框（QColorDialog）
		
		getColor()
		
		QColor color = QColorDialog::getColor(Qt::yellow, this);
		if (color, isValid())
		{
			...
		}
			
	5.字体对话框（QFontDialog）
		
		getFont()
		
		bool ok;
		QFont font = QFontDialog::getFont(&OK, 
											QFont("Arial", 18), 
											this,
											"Pick a font");
		if (ok)
		{
			...
		}
		
}
		
内置部件
{
	
	按钮 (QPushButton)
	标签 (QLabel)
	复选框 (QCheckBox)
	单选按钮 (QRadioButton)
	分组框 (QGroupBox)
	列表部件框(QListWidget)
	组合框 (QComboBox)
	自旋框(QSpinBox)
	滑动条 (QSlider)
	进度条 (QProgressBar)
	
	
	
	按钮(QPushButton)
		
		clicked() 	(signal)
		pressed()	(signal)
		release()	(signal)
		
	标签(QLabel)
		
		setBuddy (QWidget*)
		
	
	行编辑框(QLineEdit)与文本编辑框(QTextEdit)
	
		text()
		setText(const QString &)			(slot)
		textChanged (const QString&)		(signal)
		textEdited(const QString&)			(signal)
		setMaxLength(int)
		setEchoMode (EchoMode)


	复选框（QCheckBox）
		
		isChecked()
		stateChanged(int)		(signal)
		
		
	单选按钮(QRadioButton)
	
		clicked()			(signal)
		isChecked()


	分组框(QGroupBox)



	列表部件框( QListWidget )
	
		addItem(const QString&)
		addItems(const QStringList&)
		selectedItems ()
		item(int row)
		takeItem(int row)
		setSelectionMode (QAbstractItemView::SelectionMode mode)


	组合框(QComboBox)
	
		setEditable()
		activated()						(signal)
		currentIndexChanged()			(signal)
		editTextChanged()				(signal)
		currentIndex() / currentText()


	自旋框(QSpinBox)
		
		setMinimum(int)
		setMaximum(int)
		setRange(int,int)
		setSingleStep(int)
		valueChanged(int)				(signal)
		setValue(int)					(slot)
		
		
	双精度自旋框(QDoubleSpinBox)
		
		setDecimals()
		

	滑动条(QSlider)
	
		setMinimum(int)
		setMaximum(int)
		setRange(int,int)
		setSingleStep(int)
		setPageStep(int)
		setOrientation(Qt::Orientation)
		valueChanged(int) (signal)
		
	
	滚动条（QScrollBar）


	进度条(QProgressBar)
	
		valueChanged(int) 			(signal)
		setMaximum(int)				(slot)
		setMinimum(int)				(slot)
		setRange(int, int) 			(slot)
		setValue(int)				(slot)
		reset()						(slot)
		setFormat(const QString&)
		setTextVisible(bool)
		
}


布局管理器
	
	布局管理器主要常用的三个类:QHBoxLayout、QVBoxLayout、QGridLayout
	
		QHBoxLayout :水平布局
		QVBoxLayout:垂直布局
		QGridLayout :网格布局
		
		
	一个窗体有且仅有一个布局管理器（其他的布局管理器可以被窗体的布局管理器管理而已），成为窗体的布局管理器的方法∶
		1、构造布局管理器对象时设置窗体为父对象
		2、void QWidget::setLayout (QLayout *layout);


主窗口(QMainWindow)

	QMainWindow类提供了一个典型应用程序的主窗口框架，对于小屏幕设备使用Qt图形设计器定义标准Qwidget模板比使用主窗口类更好一些。典型模板包
	含有菜单栏QMenuBar，工具栏QToolBar和状态栏QStatusBar。
	只有一个工作区可以放置任意从QWidget继承出来的窗口对象，放置方法︰
	
		void QMainWindow::setCentralWidget(Qwidget *widget);
	
	多个工作区涉及类QDockWidget:
	
		void QMainWindow::addDockWidget(Qt::DockWidgetArea area，QDockWidget *dockwidget);
		void QDockWidget::setWidget (QWidget *widget);


关于事件
{
	
	1.事件重写

	2.event(QEvent *en)事件分发函数:
	{
		1.在内部使用en时要转换为对应的事件类型.
		QKeyEvent *key = static_cast<QKeyEvent*>(en);
		2.返回值!!
		{
			当接受并正确处理完事件后,返回true,该事件就不会往后传递了.
			返回false表示忽略事件,事件也不会往后传递.
			最后调用父组件的event函数,让其他事件继续分发(不然其他事件得不到处理)
			: return QWdiget::event(en);
		}
	}
	
	3.eventFilter(QObject *watched, QEvent *event)事件过滤器
	{
		1.在过滤事件之前要先给对象安装事件过滤器!
		installEventFilter(QObject *QFilter)
		当接受并正确处理完事件后,返回true.其他返回false
		最后调用父组件的eventFilte函数,完成其他组件的事件处理(不然其他事件得不到处理)
		: rerurn QWdiget::eventFilter(obj, en);
	}
	
}

}

八、ARM
{
	
ARM工作模式
{
	ARM主要有7个基本工作模式
		User :  非特权模式，大部分任务执行在这种模式
		FIQ :   当一个高优先级(fast) 中断产生时将会进入这种模式
		IRQ :   当一个低优先级(normal) 中断产生时将会进入这种模式
		Supervisor :当复位或软中断指令执行时将会进入这种模式
		Abort : 当存取异常时将会进入这种模式
		Undef : 当执行未定义指令时会进入这种模式
		System : 使用和User模式相同寄存器集的特权模式
	 
	ARM 有37个寄存器
		1 个用作PC( Program Counter)
		1个用作CPSR(Current Program Status Register)
		5个用作SPSR(Saved Program Status Registers)
		30 个通用寄存        
}

CPSR 寄存器
{
	T 位 J 位
		T = 0;J = 0    处理器处于 ARM 状态
		T = 1;J = 0    处理器处于 Thumb 状态

	中断禁止位：
		I = 1: 禁止 IRQ.
		F = 1: 禁止 FIQ
	
	Mode位：处理器模式位
		10000  User mode     10011 SVC mode;             
		10010  IRQ           10001 FIQ mode;           
		10111  Abort mode   11011 Undfined mode  11111 System mode;

	CPSR / SPSR操作指令
		msr CPSR, r0	//将r0寄存器中的值赋给CPSR寄存区
		mrs r0, CPSR	//将CPSR寄存区中的值赋给r0寄存区   
}		

	
	load：存储器(内存，闪存) -> 寄存器
	store： 寄存器 -> 存储器
	
	
	异常的优先级
	Reset > Data Abort > FIQ > IRQ > Prefetch Abort > SWI > Undefined instruction
	
裸机编程
一.裸机编程
	直接通过操作特殊功能寄存器控制硬件的方式；
	1.硬件介绍
		1核心板
			soc芯片：cpu GPIO控制器  Uart控制器 timer ADC 总线 iROM iRAM....
			4片内存
			flash(EMMC 4G)
		2外围板
			各种外设：led 蜂鸣器 传感器(mpu6050 ds18b20) 串口 AD 网卡 USB camera....
	2.裸机三步骤
		1看原理图(板子厂商)
			得到cpu与硬件的连接管脚
		2看芯片手册(芯片厂商)
			得到控制cpu引脚的特殊功能寄存器
		3编程(汇编 C)
	点灯为例：
		1.先查看板子厂商的原理图找到对应的外部设备LED模块的图，找到对应灯的名字；
		2.再去厂商的核心手册找到对应灯的寄存器的名字；
		3.去芯片厂商的芯片手册查看对应寄存器的地址和使用方法；
			例如：查到灯对应的寄存名为：GPF3_5  先去找到关于GPF3组的寄存器都有哪些，再去找到相关的寄存器去操作里面对应地址的值

串口编程
	裸机编程
	1.原理图	
		GPA1_0: uart2-> RXD
		GPA1_1: uart2 -> TXD
	2.芯片手册
		对外设置 ：GPIO设置：
			GPA1CON -> 0:3 4:7 0010 0010
		对内设置：uart设置

ADC编程：
	1.原理图 
		AIN3
	2.芯片手册
		
		void ADC_init()
		{
	
			1.ADCCON
			  分辨率12bits: ADCCON -> 16位 -> 1
			  使能分频      ADCCON -> 14位 -> 1
			  分频值        ADCCON -> 13位 ->  132      133MHZ /(132+1)  = 1MHZ
			  
			 2.选择通道
				ADCMUX -> 0011    AIN3
		}
		
TImer的PWM编程：
	1.看原理图
		GPD0_0
	2.看芯片手册
		对外设置：(管脚设置)
			GPD0CON -> 3:0 -> 0010
		对内设置：(pwm配置)
			设置预分频值：TCFG0 -> 7:0 -> 255 (prescaler value: 1~255)
			设置分频值：  TCFG1 -> 3:0 -> 0100(divider value: 1/2/4/8/16)
			eg:
				Timer Input Clock Frequency = 100MHZ/({255 + 1})/{16} = ??? 
			
			计数寄存器: TCNTB0 = 200;
			比较寄存器：TCMPB0 = 100;
		说明：
			当CNT > CMP，电平为0
			当CNT <= CMP，电平翻转为1
			
			配置寄存器：TCON -> 3:0 -> 1110 手动   
						TCON -> 3:0 -> 1101 自动重装载  开启定时器
			
	3.编程
		GPD0CON &= ~0xf;
		GPD0CON |= 0x2;
		
RTC编程：
	1.看芯片手册
	void RTC_init(void)
	{
		RTCCON -> 0 -> 1
		BCDYEAR -> 111
		BCDMON ->  11
		....
		
		RTCCON -> 0 -> 0
	}	
	
	int main()
	{
		RTC_init();
		uart_init();
		while(1)
		{
			display_time();
			delay1s();
		
		}
	}
wdt编程：
	1.设置看门狗配置寄存器
		t_watchdog = 1/(100MHZ/(155 + 1)/128) -> 频率:  1/5000 * 5000 -> 1s
		
		wdt_init()
		{
			1. WTCNT = 5000; //看门狗计数器的值
			2. WTCON: 0->1   4:3->11 15:8 -> 155(0~255)  5->1		
		}
	
扩展：
	1.单总线：
		ds18b20温度采集
	2.I2C总线协议
	3.SPI总线协议
	

设备间的通讯方式
	串行通讯：
		单线
		双线： uart -> 特点：全双工 异步
		双线： i2c  -> 特点：半双工 同步 
		三线： spi  -> 特点：全双工 同步
	并行通讯：

UART：
	UART是异步串行通信的。
	UART是异步串行通信的。利用UART协议传输数据时，需要两个数据引脚，一个用于传输数据的TX，另一个用于接收的RX。
	一个设备的TX接的是另一设备的RX，反之RX接TX
	UART是最常见的通信协议之一，它可以实现全双工传输，但它的传输速度比较慢，而且只能支持一对一的设备。

I2C：
	I2C最常被应用于模块或者传感器之间的通信，因为I2C基于二根传输线，同步通信的半双工协议，而且协议也非常简单可靠。 
	I2C使用两根传输线实现一个主设备与多个从设备，甚至是多个主设备与对应从设备之间的通信。 
	这两根通讯线一根为控制时钟线，称之为SCL，用于同步设备间的数据传输时钟； 
	另一根为数据线，称之为SDA，用于携带数据。理论上，一条I2C总线上能支持挂载128台设备。
	
	I2C虽然只需要两根线，就能支持多主机多从机的数据传输，但由于只有一根用于数据传输，它通过在“接收”和“传输”两种状态之间但切换实现了双向传
	输，但牺牲了不少传输速率。I2C还有典型的开漏问题，总线需要加上拉电阻。

SPI：
	SPI全称Serial Peripheral Interface(串行外设接口)
	由摩托罗拉公司提出的一种同步串行数据传输协议。SPI类似I2C也是同步通信的协议，但是全双工，支持数据的同时输出和输入。
	这两个特征使SPI的传输速率比UART和I2C都高，这对于像SD卡、或者屏幕等数据型模块来说，是非常具有优势的。
	
	SPI支持一主多从的模式，但SPI也是三种协议中需要线最多的协议，一共需要4条信号线：
		MOSI、MISO、SCLK、CS(或SS)，以CS选择从机
	要注意的是，SCK信号线只由主设备控制，从设备不能控制信号线。同样，在一个基于SPI的设备中，至少有一个主控设备。
	SPI接口的一个缺点：没有指定的流控制，没有应答机制确认是否接收到数据。
	

根据ADC值算实际值

	ADC的值/(ADC位数最大值+1)*参考电压

	首先确定ADC用几位表示，最大数值是多少。比如一个8位的ADC，最大值是0xFF，就是255。
	然后确定最大值时对应的参考电压值。一般而言最大值对应3.3V。这个你需要看这个芯片ADC模块的说明。寄存器中有对于输入信号参考电压的设置。
	要计算电压，就把你的ADC数值除以刚才确定的最大数值再乘以参考电压值。比如你ADC值为0x80，那么实际值就是0x80/(0xFF+1)*3.3V = 1.65V

}

九、系统移植
{
	
u-boot移植
1.认识uboot目录
	api:接口
	common:uboot支持的命令
	disk：磁盘相关的文件
	examples:示例
	lib:库文件
	include:头文件目录
	fs:文件系统
	net：网络相关的东西
	arch: 支持的CPU的架构目录
	board:支持的板子目录
	drivers:设备驱动目录
	doc:文档
	dts:设备树
	tools:工具
	Makefile:指定编译规则
	boards.cfg: 板子的配置文件信息
2.uboot启动流程
	第一阶段：(汇编)	
		设置CPU工作模式为SVC、关中断、关MMU……
		内存初始化：为内核运行做准备
		自搬运：不是每个u-boot都需要做的
		设置堆栈、清空BSS段：为进入C做准备
	
	第二阶段：(C阶段)
		初始化GPIO、串口、网口  使能中断 开MMU ……
		执行命令
		加载内核
		
3.u-boot移植
	(1)明确需求
		内核加载起来就可以了
	(2)准备工作：资料 ....
	(3)u-boot是否支持CPU
		a.支持 goto 4
		b.不支持: 下载更新版本的uboot 找芯片厂商要 找老板要
	(4)u-boot是否支持板子
		a.支持 goto 5
		b.不支持：下载更新版本的uboot 找板子厂商要  借鉴和板子芯片一模一样的板子
	(5)编译

4.移植
	(1)借鉴和板子芯片一模一样的板子(origen)
		头文件： cp  include/configs/origen.h include/configs/fs4412.h
		源文件： cp -a board/samsung/origen board/samsung/fs4412
	(2)添加fs4412的配置信息到boards.cfg
		vi boards.cfg
			fs4412        arm     armv7       fs4412      samsung    exynos

	(3)修改Makefile中的编译器
		 #ifeq ($(HOSTARCH),$(ARCH))
			CROSS_COMPILE ?=arm-linux-
		 #endif
	(4)make distclean  //清除之前make生成的文件
	(5)make fs4412_config   //指定编译的板子是fs4412
	(6)make //编译生成 u-boot.bin
	(7)拷贝u-boot.bin到tftp目录
		cp u-boot.bin /home/farsight/tftpboot
	
	(8)将编译生成的u-boot.bin烧写到SD卡/EMMC
		先将u-sd.bin烧写到SD卡
	
		SD卡启动：1000
			使用SD卡烧写工具 Win32DiskImager.exe 烧写
		
		EMMC启动：0111
			SD卡启动：1000
				tftp 41000000 u-boot.bin 
				movi write uboot 410000000  //把内存0x41000000中的内容写到EMMC的uboot区
			切换拨码开关到EMMC,0111 看效果
	【效果】
		板子边板砖。。。。。


u-boot-2013.01 的移植

一、建立自己的平台
	1、下载源码
	2、解压 uboot 源码并进入目录
	3、指定交叉编译工具链
	4、指定产品 CPU
	5、指定产品 BOARD
	6、编译 u-boot
		编译完成后生成的 u-boot.bin 就是可执行的镜像文件。
		但是该文件还不能在我们板子上运行，我们需要对 u-boot 源代码进行相应的修改。

二、实现能看到串口终端信息
	1、确认第一条指令有运行到（点灯法）
			在 arch/arm/cpu/armv7/start.S 134 行后添加点灯程序
		添加三星加密方式
			exynos 需要三星提供的初始引导加密后，我们的 u-boot,才能被引导运行
				$cp sdfuse_q u-boot-2013.01 -rf
				注：sdfuse_q 三星提供的加密处理
				$cp CodeSign4SecureBoot u-boot-2013.01 -rf
				注：CodeSign4SecureBoot 三星提供的安全启动方式
		修改 Makefile
		拷贝编译脚本
		
	2、实现串口输出	
		添加临时栈
		添加关闭看门狗代码
		添加串口初始化代码
		
三、网卡移植
	1、添加网络初始化代码
	2、修改配置文件添加网络相关配置
	3、重新编译u-boot
	
四、FLASH 移植 （EMMC）
	1、初始化EMMC
	2、添加相关命令
	3、添加 EMMC 相关配置
	4、重新编译 u-boot
	
	
从 EMMC 加载内核和文件系统
	(a)拷贝第一天/镜像文件/ramdisk.img 拷贝到虚拟机/tftpboot 目录下

	(b)烧写内核镜像到 EMMC 上
		# tftp 41000000 uImage
		# movi write kernel 41000000

	(c)烧写设备树文件到 EMMC 上
		# tftp 41000000 exynos4412-fs4412.dtb
		# movi write dtb 41000000

	(d)烧写文件系统镜像到 EMMC 上
		# tftp 41000000 ramdisk.img 
		# movi write rootfs 41000000 300000

	(e)设置启动参数
		# setenv bootcmd movi read kernel 41000000\;movi read dtb 42000000\;movi read rootfs 43000000300000\;bootm 41000000 43000000 42000000
		
		# saveenv	
	
}

十、Linux字符设备驱动
{
	
	BSP：板级支持包
	MMU：实现虚拟内存的功能
	
	编写linux内核认同的驱动文件（xxx.c）；
	修改Makefile
	make编译
	
	进入板子的Linux系统中
	给板子配置ip地址
		同一局域网：udhcpc -> 板子自动获取ip
		网线连接：ifconfig eth0 ip地址
	
	从给板子拷贝文件
		scp led_driver.ko ip:/
		
	给板子上的linux内核插入模块
		insmod led_driver.ko
		
	创建对应字符设备号的文件
		mknod xxx c 主号 次号
	
	运行对应的操作文件
		
	
Linux中操作：
	编写linux内核认同的驱动文件（xxx.c）；
	修改Makefile
	make编译
	编写运行文件xxx.c然后使用arm-linux-gcc编译
		arm-linux-gcc xxx.c
	将运行文件和内容模块文件传给板子
		scp xxx.ko 板子ip:/
		scp a.out 板子ip:/

板子linux：
	insmod xxx.ko(插入Linux内核)       rmmod  xxx.ko(去掉驱动)
	mknod xxx c 主号 次号
	cat xxx
	
	
提取模块中信息
	modinfo xxx.ko (module.ko)

设置驱动文件里的参数
module_param(参数名，参数类型， 参数读/写权限)
	int a；
	module_param(a, int, 0644);
	
	
rmnod 时出错：找不到对应的目录
	mkdir /lib/modules/3.14.0 -p

导出符号（自己写的驱动可以让其他驱动调用）
EXPORT_SYMBOL(符号名)
	例：
		void xxx(void){}
		EXPORT_SYMBOL(xxx); 
		
		

Linux下的设备
Linux下分成三大类设备：
	字符设备：字符设备是能够像字节流一样被访问的设备。一般来说对硬件的IO操作可归结为字符设备。常见的字符设备有led，蜂鸣器，串口，键盘等等。包
	括lcd与摄像头驱动都属于字符设备驱动。
	块设备：块设备是通过内存缓存区访问，可以随机存取的设备，一般理解就是存储介质类的设备，常见的字符设备有U盘，TF卡，eMMC，电脑硬盘，光盘等等
	网络设备：可以和其他主机交换数据的设备，主要有以太网设备，wifi，蓝牙等。

字符设备与块设备驱动程序的区别与联系
	1.字符设备的最小访问单元是字节，块设备是块字节512或者512字节为单位
	2.访问顺序上面，字符设备是顺序访问的，而块设备是随机访问的
	3.在linux中，字符设备和块设备访问字节没有本质区别

字符设备驱动程序解析
创建流程
1第一步：写出驱动程序的框架
	
	最开始还是要实现一个驱动程序的入口与出口函数。
	#include <linux/init.h>
	#include <linux/module.h>
	static int __init dev_fifo_init()
	{
		  return ;
	}

	static void __exit dev_fifo_exit()
	{
	}
	module_init(dev_fifo_init);
	module_exit(dev_fifo_exit);

	MODULE_LICENSE("Dual DSB/GPL");
	MODULE_AUTHOR("ZHAO");
	
2第二步：在驱动入口函数中申请设备号

	//设备号 : 主设备号(12bit) | 次设备号(20bit)
	dev_num = MKDEV(MAJOR_NUM, );

	//静态注册设备号
	ret = register_chrdev_region(dev_num,,"dev_fifo");
	if(ret < )
	{
		//静态注册失败，进行动态注册设备号
		ret = alloc_chrdev_region(&dev_num,,,"dev_fifo");
		if(ret < )
		{
			printk("Fail to register_chrdev_region\n");
			goto err_register_chrdev_region;
		}
	}
	
	注意，在入口函数中注册，那么一定要记得在驱动出口函数中释放
	//释放申请的设备号
	unregister_chrdev_region(dev_num, );

3第三步：创建设备类

	这一步会在/sys/class/dev_fifo下创建接口
	//创建设备类
	cls = class_create(THIS_MODULE, "dev_fifo");
	if(IS_ERR(cls))
	{
		ret = PTR_ERR(cls);
		goto err_class_create;
	}

4第四步：初始化字符设备

	在这一步中，会初始化一个重要的结构体，file_operations。
	//初始化字符设备
	cdev_init(&gcd->cdev,&fifo_operations);
	
	Linux使用file_operations结构访问驱动程序的函数，这个结构的每一个成员的名字都对应着一个调用。
	用户进程利用在对设备文件进行诸如read/write操作的时候，系统调用通过设备文件的主设备号找到相应的设备驱动程序，然后读取这个数据结构相应的函数指针，接着把控制权交给该函数，这是Linux的设备驱动程序工作的基本原理。 

	通常来说，字符设备驱动程序经常用到的5种操作
	struct file_operations
	{
		ssize_t (*read)(struct file *，char *, size_t, loff_t *);//从设备同步读取数据
		ssize_t (*write)(struct file *,const char *, size_t, loff_t *);
		int (*ioctl) (struct  inode *,  struct file *, unsigned int,  unsigned long);//执行设备IO控制命令
		int (*open) (struct inode *, struct file *);//打开
		int (*release)(struct inode *, struct file *);//关闭
	};
	
5第五步：添加设备到用户操作系统

	//添加设备到操作系统
	ret = cdev_add(&gcd->cdev,dev_num,);
	if (ret < )
	{
		goto  err_cdev_add;
	}

6第六步：导出设备信息到用户空间

	//导出设备信息到用户空间(/sys/class/类名/设备名)
	device = device_create(cls,NULL,dev_num,NULL,"dev_fifo%d",);
	if(IS_ERR(device)){
		ret = PTR_ERR(device);
		printk("Fail to device_create\n");
		goto err_device_create; 
	}


内核中定义的万能链表找首节点地址的宏：
	countainer_of
	

}

关于内存
{
	
按照数据存取的方式不同， ram 中的存储单元分为两种:静态存储单元一静态RAM (SRAM);动态存储单元—动态RAM (DRAM)。
	
C语言在内存中一共分为如下几个区域，分别是：

1. 内存栈区： 存放局部变量名；
2. 内存堆区： 存放new或者malloc出来的对象；
3. 常数区： 存放局部变量或者全局变量的值；
4. 静态区： 用于存放全局变量或者静态变量；
5. 代码区：二进制代码。

一个由C/C++编译的程序占用的内存分为以下几个部分

1、栈区（stack）— 程序运行时由编译器自动分配，存放函数的参数值，局部变量的值等。
        其操作方式类似于数据结构中的栈。

2、堆区（heap） — 在内存开辟另一块存储区域。
      一般由程序员分配释放， 若程序员不释放，程序结束时可能由OS回收 。
      注意它与数据结构中的堆是两回事，分配方式倒是类似于链表。

3、全局区（静态区）（static）—编译器编译时即分配内存。
       全局变量和静态变量的存储是放在一块的，
       初始化的全局变量和静态变量在一块区域，
        未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。 
       - 程序结束后由系统释放

4、文字常量区 —常量字符串就是放在这里的。 程序结束后由系统释放。

5、程序代码区—存放函数体的二进制代码。

注意：静态局部变量和静态全局变量
属于静态存储方式的量不一定就是静态变量。 
例如：全局变量虽属于静态存储方式，但不一定是静态变量，
           必须由 static加以定义后才能成为静态外部变量，或称静态全局变量。
把局部变量改变为静态变量后是改变了它的存储方式，即改变了它的生存期。
把全局变量改变为静态变量后是改变了它的作用域，限制了它的使用范围。


相关概念
1.内存交换
	把处于等待状态（或在CPU调度原则下被剥夺运行权利）的程序从内存移到辅存，把内存空间腾出来，这一来过程又叫换出；
	把准备好竞争CPU运行的程序从辅存移到内存，这一过程又称为换入。

2.内存溢出 out of memory
	是指程序在申请内存时，没有足够的内存空间供其使用，出现out of memory；
	比如申请了一个intege但给它存了long才能存下的数，那就是内存溢出。
	内存溢出就是你要求分配的内存超出了系统能给你的，系统不能满足需求，于是产生溢出。
	比如一个盘子用尽各种方法只能装4个果子，你装了5个，结果掉倒地上不能吃了。这就是溢出！
	比方说栈，栈满时再做进栈必定产生空间溢出，叫上溢，栈空时再做退栈也产生空间溢出，称为下溢。就是分配的内存不足以放下数据项序列称为内存
	溢出.

3.内存泄漏
	是指你向系统申请分配内存进行使用(new)，可是使用完了以后却不归还(delete)
	结果你申请到的那块内存你自己也不能再访问（也许你把它的地址给弄丢了），而系统也不能再次将它分配给需要的程序。
	总结：内存泄露的堆积最终会造成内存溢出(申请的空间大于分配的空间)

4.内存映射（mmap） 
是一种内存映射文件的方法，即将一个文件或者其他对象映射到进程的地址空间，实现文件磁盘地址和应用程序进程虚拟地址空间中一段虚拟地址的一一映射
关系。

}

部分概念
{
1.TCP/IP协议

	TCP/IP传输协议，即传输控制/网络协议，也叫作网络通讯协议。它是在网络的使用中的最基本的通信协议。TCP/
	IP传输协议对互联网中各部分进行通信的标准和方法进行了规定。并且，TCP/IP传输协议是保证网络数据信息及时、完整传输的两个重要的协议。

	TCP/IP协议族包括诸如Internet协议(IP)、地址解析协议(ARP)、互联网控制信息协议(ICMP)、用户数据报协议(UDP)、传输控制协议(TCP)、
	路由信息协议(RIP)、Telnet、简单邮件传输协议(SMTP)、域名系统(DNS)等协议。


2.在tcp/ip协议中，tcp通过三次握手建立起一个tcp的链接，大致如下

     第一次握手：客户端尝试连接服务器，向服务器发送syn包，syn=j，客户端进入SYN_SEND状态等待服务器确认

    第二次握手：服务器接收客户端syn包并确认(ack=j+1)，同时向客户端发送一个SYN包（syn=k），即SYN+ACK包，此时服务器进入SYN_RECV状态

    第三次握手：客户端收到服务器的SYN+ACK包，向服务器发送确认包ACK(ack=k+1)此包发送完毕，客户端和服务器进入ESTABLISHED状态，完成三次握手


3.算法的五个特征是：有穷性，确切性，输入项，输出项，可行性。


算法复杂度与初始状态无关的有：选择排序、堆排序、归并排序、基数排序
元素总比较次数与初始状态无关的有：选择排序、基数排序
元素总移动次数与初始状态无关的有：归并排序、基数排序


5.进程的调度比线程调度效率更低一点
	因为访问不同的进程时CPU的cache中的内容一直在不断的切换，当访问不同的进程
	时cache就在切换，而线程就不用切换，因为线程是进程内部的最小调度单位。



	select
	IO多路复用的原理
	
	
	
	
6.inline内联函数为什么比普通函数效率高
	内联函数在调用时，是将调用表达式用内联函数体来替换,而一般函数进行调用时，要将程序执行权转到被调用函数中，然后再返回到调用它的函数中。
	内联函数比普通函数效率高的原因就是编译器在调用处把这个函数展开，展开就是直接执行代码而不是调用这个函数，像宏展开的意思。

7.宏定义与内联函数的区别
	宏定义不检查函数参数，返回值什么的，只是展开，相对来说，内联函数会检查参数类型，所以更安全。
	
	内联函数和宏很类似，而区别在于，宏是由预处理器对宏进行替代，而内联函数是通过编译器控制来实现的。而且内联函数是真正的函数，只是在需要用到的时候，
	内联函数像宏一样的展开，所以取消了函数的参数压栈，减少了调用的开销。你可以象调用函数一样来调用内联函数，而不必担心会产生于处理宏的一些问题。

8.fgetc与getc的区别

	函数getchar等价于getc(stdin)。getc与fgetc的区别是getc可被实现为宏，而fgetc则不能实现为宏。这意味着：

		(1) getc的参数不应当是具有副作用的表达式。

		(2) 因为fgetc一定是一个函数，所以可以得到其地址。这就允许将fgetc的地址作为一个参数传递给另一个函数。

		(3) 调用fgetc所需时间很可能长于调用getc，因为调用函数所需的时间长于调用宏。

什么是IO多路复用
	一句话解释：单线程或单进程同时监测若干个文件描述符是否可以执行IO操作的能力。



漏极开路：
	漏极开路（Open Drain）即高阻状态，适用于输入/输出，其可独立输入/输出低电平和高阻状态，
	若需要产生高电平，则需使用外部上拉电阻或使用如LCX245等电平转换芯片。同时具有很大的驱动能力，可以作为缓冲器使用。

上拉电阻·电路：
	含有上拉电阻的电路组成叫做上拉电阻·电路。在上拉电阻所连接的导线上，
	如果外部组件未启用，上拉电阻则“微弱地”将输入电压信号“拉高”。当外部组件未连接时，对输入端来说，外部“看上去”就是高阻抗的。

}

算法学习
{

NC78链表反转

	方法一：
		思路：
			让头节点的next指针指向下一个节点的下一个节点，让下一个节点（头结点的下一个节点）的next指针指向上一个节点，依次循环执行，判断条件为头结点
			的下一个节点是否为空；
		做法：
			首先判断头结点是否为空；
			新建两个链表结构体指针，分别指向头结点与头结点下一个节点；
			循环条件为头节点的下一个节点不为空；			
				ListNode* ReverseList(ListNode* pHead) {
				if(NULL == pHead)
					return NULL;
				ListNode *head = pHead;
				ListNode *foll = pHead->next;
				while(foll)
				{
					pHead->next = foll->next;
					foll->next = head;
					head = foll;
					foll = pHead->next;
				}
				return head;
			}
			
	方法二：
		思路：
			让头结点的next指针直接先指向空(C++:nullptr)，然后依次让头结点的下一个节点的next指针指向上一个节点;
		做法：
			首先判断头结点是否为空；
			新建俩个链表结构体指针，分别用来指向新的头节点(创建时设为空)、头节点下一个节点(创建时可以设为空，循环中会赋值)；
			循环条件为当前节点节点不为空；		
				ListNode* ReverseList(ListNode* pHead) {
					if(NULL == pHead)
						return nullptr;
					ListNode *cur = pHead;
					ListNode *nex = nullptr;
					ListNode *pre = nullptr;
					while(cur)
					{
						nex = cur->next;
						cur->next = pre;
						pre = cur;
						cur = nex;
					}
					return pre;
				}



N33合并两个排序的链表

	方法一：
		思路：
			迭代的方法，创建一个新的节点用来连接最终的结果，在循环里比较两个链表哪个小就接哪一个，然后小的指向下一个进行比较；
		做法：
			1.如果L1指向的结点值小于等于L2指向的结点值，则将L1指向的结点值链接到头结点的next指针，然后L1指向下一个结点值
			2.否则，让L2指向下一个结点值
			3.循环步骤1,2，直到L1或者L2为nullptr
			4.将L1或者L2剩下的部分链接到pHead的后面
				/*
				struct ListNode {
					int val;
					struct ListNode *next;
					ListNode(int x) :
							val(x), next(NULL) {
					}
				};*/
				class Solution {
				public:
					ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
						if(!pHead1 && !pHead2)
							return nullptr;
						ListNode *pHead = new ListNode(-1);
						ListNode *back = pHead;
						while(pHead1 && pHead2)
						{
							if(pHead1->val < pHead2->val){
								pHead->next = pHead1;
								pHead1 = pHead1->next;
							}else{
								pHead->next = pHead2;
								pHead2 = pHead2->next;
							}
							pHead = pHead->next;
						}
						pHead->next = pHead1 ? pHead1 : pHead2;
						return back->next;
					}
				};

	方法二：递归版本
		方法一的迭代版本，很好理解，代码也好写。但是有必要介绍一下递归版本，可以练习递归代码。
		写递归代码，最重要的要明白递归函数的功能。可以不必关心递归函数的具体实现。
		比如这个ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
		函数功能：合并两个单链表，返回两个单链表头结点值小的那个节点。

		如果知道了这个函数功能，那么接下来需要考虑2个问题：

		递归函数结束的条件是什么？
		递归函数一定是缩小递归区间的，那么下一步的递归区间是什么？
		对于问题1.对于链表就是，如果为空，返回什么
		对于问题2，跟迭代方法中的一样，如果PHead1的所指节点值小于等于pHead2所指的结点值，那么phead1后续节点和pHead节点继续递归
			class Solution {
			public:
			 ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
			 {
				 if (!pHead1) return pHead2;
				 if (!pHead2) return pHead1;
				 if (pHead1->val <= pHead2->val) {
					 pHead1->next = Merge(pHead1->next, pHead2);
					 return pHead1;
				 }
				 else {
					 pHead2->next = Merge(pHead1, pHead2->next);
					 return pHead2;
				 }
			 }
			};


}



关于嵌入式
{

P型半导体
{
概念
	空穴型半导体又称P型半导体，是以带正电的空穴导电为主的半导体。在纯硅中掺入微量3价元素铟或铝，由于铟或铝原子周围有3个价电子，与周围4价硅原子组成共
	价结合时缺少一个电子，形成一个空穴。空穴相当于带正电的粒子，在这类半导体的导电中起主要作用。
特点
		掺入的杂质越多，多子（空穴）的浓度就越高
	
形成
	在纯净的硅晶体中掺入三价元素（如硼），使之取代晶格中硅原子的位置，就形成P型半导体。在P型半导体中，空穴为多子，自由电子为少子，主要靠空穴导电。由
	于P型半导体中正电荷量与负电荷量相等，故P型半导体呈电中性。空穴主要由杂质原子提供，自由电子由热激发形成。
}

N型半导体
{
概念
	也称为电子型半导体。N型半导体即自由电子浓度远大于空穴浓度的杂质半导体。
特点
	半导体中有两种载流子，即价带中的空穴和导带中的电子，以电子导电为主的半导体称之为N型半导体，与之相对的，以空穴导电为主的半导体称为P型半导体。 
	“N”表示负电的意思，取自英文Negative的第一个字母。在这类半导体中，参与导电的 (即导电载体) 
	主要是带负电的电子，这些电子来自半导体中的施主。凡掺有施主杂质或施主数量多于受主的半导体都是N型半导体。例如，含有适量五价元素砷、磷、锑等的锗或硅
	等半导体。 
	由于N型半导体中正电荷量与负电荷量相等，故N型半导体呈电中性。自由电子主要由杂质原子提供，空穴由热激发形成。掺入的杂质越多，多子（自由电子）的浓度
	就越高，导电性能就越强
}	

三极管
	是由输入的电流控制输出的电流。
	
场效应管
	其输出电流是由输入的电压（或称电场）控制，可以认为输入电流极小或没有输入电流，这使得该器件有很高的输入阻抗，同时这也是我们称之为场效应管的原因。
	
	
}


智能家居项目
{
	V4L2
	
}


Python
{
	变量的类型：
        不可变类型：数字、字符串、元组等，表示不支持原处修改
        可变类型：列表、字典、可变集合，表示可以在原处修改数值
	1.列表	
		list = [1, 2, 3]
	列表中的元素可以是任意类型
		list = [1, 2, 3, "one", [2, 3, 4]]
	列表元素的访问
		print(list[3])
		print(list[3][1])
		print(list[4])
		print(list[4][2])
	列表中的元素值可以改变
		list[3] = 4
		
	2.tuple 元组类似于 list列表，但是元素值不可变，是只读的
		tu = (1, 2, 3, 4)
		tu = (1, 2, "one", [1, 2, 3], (4, 5))
		print(tu)
		print(tu[2])
		
	3.字典类型 {key: value}，key可以是数值和字符串类型，value可以是任意类型
		dic = {"one": 1, "two": 2, 3: "three"}
	字典元素的访问 [key]
		print(dic["one"])
		print(dic[3])
	字典的元素值是可变的 [key] = value
		dic["one"] = [1, 2, 3]
		print(dic)
	字典元素可以新增
		dic["four"] = 4
		print(dic)
		
	函数的定义： def 函数名(形参列表):
                函数体
                return
}


Linux相关命令
{
tar命令
	-c或--create 建立新的备份文件。
	-f<备份文件>或--file=<备份文件> 指定备份文件。
	-v或--verbose 显示指令执行过程。
	-x或--extract或--get 从备份文件中还原文件。
	-z或--gzip或--ungzip 通过gzip指令处理备份文件。

	{
		压缩文件 非打包
			# touch a.c       
			# tar -czvf test.tar.gz a.c   //压缩 a.c文件为test.tar.gz
			a.c
		解压文件
			# tar -xzvf test.tar.gz 
			a.c
	}
du -sh  xxx		#以GB的形式查看某个单个文件大小

}
