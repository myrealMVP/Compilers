6.28
如何操作：
1.在同目录下找到testfile.txt，在里面输入程序
2.运行程序
(可以是像我现在主函数这样:直接生成所有的Token串,
也可以每一次调用一次对象的nextw函数生成一个Token串)
3.每调用一次nextw函数，传进去的Token串更新，
同时将Token串写入同目录下的output.txt。

几点改动：
1.原先讨论的是构造成为一个函数，但是我将其进一步封装成为类。
这样，调用read_program的函数可以读入程序
调用nextw函数可以更新Token串
最最重要的是主函数简单，接口容易对接。
2.对于界符和关键字有了部分的改动
大概就是增加了 关键字 string 界符 ' "
删了两个注释
(最新版我已经放在同目录下）
3.注释的界符我就没有进行输出了，因为对语法分析没有帮助

需要讨论的：
1.关键字、界符等等这些是不是要放到scanner类中
2.像我刚刚尝试的char c = 'z'，现在将z放到了标识符中，
这显然是不正确的，或许我们要再开一个字符常量表和字符串常量表。

**********************************************************************
6.29
更改：
1.增加了字符常量表和字符串常量表
2.将所有的表均放到了类中，方便读取
3.在主函数后面对各表进行了输出，方便调试