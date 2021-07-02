#pragma once
#include <iostream>
#include <string.h>
#include <deque>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip> 
#define INPUT_PATH "testfile.txt"
#define OUTPUT_PATH "output.txt"
using namespace std;
/* 这里的定义的是关键字和界符的数量，
   如果增加关键字和界符：
   1.在K / P 增加相应的关键字和界符
   2.增加 KEY_NUM / PRA_NUM 的数量
*/
#define KEY_NUM 20
#define PRA_NUM 36


class Token
{
public:
    string classification;
    int index;
};

class scanner
{
public:
    int identifier_num = 1;
    int count1_num = 1; // 常整数的个数
    int count2_num = 1; // 常实数的个数 
    int char_num = 1;   // 字符的个数
    int string_num = 1; // 字符串的个数 
    bool FLAG = true; // 判断词法是否合法
    vector<string> v; // 用来存取TOKEN序列
    string all_ch;
    //********************全程序最重要的指针**********************************
    //string 不需要'\0'来判断结束
    // 将连接起来的串转为char*
    const char* scanner_ptr;
    bool read_program();
    int val(const char ch);
    bool nextw(Token& token);

    // ***************************************关键字表**************************************
    string K[KEY_NUM + 1] =
    {
        "",
        // 定义
        "const",
        "int",
        "short",
        "float",
        "double",
        "char",
        "string",
        "bool",
        // 函数
        "void",
        "main",
        "return",
        // 判断
        "if",
        "else",
        // 循环
        "do",
        "while",
        "for",
        "break",
        // 输入输出
        "cin",
        "cout",
        // 结构
        "struct",
    };

    // ***************************************界符表**************************************
    string P[PRA_NUM + 1] =
    {
        "",
        // 加、减、乘、除、模、非
        "+",
        "-",
        "*",
        "/",
        "%",
        "!",
        // 小于、小于等于、大于、大于等于、等于、不等于
        "<",
        "<=",
        ">",
        ">=",
        "==",
        "!=",
        // 赋值、分号、逗号
        "=",
        ";",
        ",",
        // 双目运算符
        "++",
        "--",
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        // 圆括号、方括号、花括号
        "(",
        ")",
        "[",
        "]",
        "{",
        "}",
        // 注释
        "//",
        // 逻辑
        "&&",
        "||",
        // 输入流、输出流
        ">>",
        "<<",
        // 程序结束标识
        "#",
        // 单引号、双引号
        "'",
        "\"",
    };

    // ***************************************标识符表**************************************
    string I[50]
    {
        ""
    };

    // ***************************************实整数表(int)**************************************
    int CI[50]
    {
        0
    };

    // ***************************************实浮点数表(double)**************************************
    double CR[50]
    {
        0
    };

    // ***************************************字符常量表**************************************
    char CH[50]
    {
        ' '
    };

    // ***************************************字符串常量表(double)**************************************
    string ST[50]
    {
        ""
    };
};