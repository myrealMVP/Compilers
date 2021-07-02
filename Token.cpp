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

bool scanner::read_program()
{
    // 从 testfile.txt 读取程序
    string buf;
    ifstream in;

    in.open(INPUT_PATH, ios::in);

    if (!in.is_open()) {
        cout << "file not open" << endl;
        exit(1);
    }

    

    while (getline(in, buf)) {    // 将所有行的代码缩为一整行，且去掉空格
        all_ch = all_ch + buf;
        // 这里加空格是为了使得 关键字和标识符分离开
        // 否则的话 关键字会出现混入标识符的情况
        all_ch += '\n';
    }
    in.close();

    all_ch += "#";

    //string 不需要'\0'来判断结束
    scanner_ptr = all_ch.c_str();

    // 将输出文件清空
    ofstream out;
    out.open(OUTPUT_PATH, ios::out);
    out.close();
}

// 将ASCII码转换为整数
int scanner::val(const char ch)
{
    return ch - 48;
}

// 语法分析所需的读取下一个Token串
bool scanner::nextw(Token& token)
{
    // 这里的变量是用来判断是否已经读到Token串(读到为false退出，否则继续读取)
    bool if_continue = true;
    while (*scanner_ptr && if_continue) {
        if (*scanner_ptr == ' ' || *scanner_ptr == '\n' || *scanner_ptr == '\r'
            || *scanner_ptr == '\t' || *scanner_ptr == '\v' || *scanner_ptr == '\f') {
            // 读到空格的话，直接选择跳过
            scanner_ptr++;
            // 读到这些转义字符，没有生成Token串，需要继续读
            if_continue = true;
        }
        else if (*scanner_ptr >= 48 && *scanner_ptr <= 57) { // 常整数表 & 常实数表
// q1 状态，完成初始化工作
            int n = 0; // 拼尾数值变量
            int p = 0; // 拼指数值变量
            int m = 0; // 小数位数变量
            int t = 0; // 指数的符号
            // 1 为 正 ， -1 为 负
            int e = 1; // 类型变量
            // 0 为整型， 1 为实型
// q2 状态，读第一个字符进来
            n = n * 10 + val(*scanner_ptr);
            scanner_ptr++;
            // 需判断是否为终结符
            while (*scanner_ptr >= '0' && *scanner_ptr <= '9') { // 直到读到的字符不是数字停止               
                n = n * 10 + val(*scanner_ptr);
                scanner_ptr++;
            }
            // 跳出来的时候，分为两种情况
            // 1.下一个字符不是'e'和'.’则直接退出
            // 2.若是，那么就继续进入
// q3 状态，继续读数
            if (*scanner_ptr == '.') {
                t = 1; // 属于常实数了
                scanner_ptr++;
                if (*scanner_ptr >= '0' && *scanner_ptr <= '9') {
                    // 读到小数点后，后一位必须要是数字，否则词法错误
                    n = n * 10 + val(*scanner_ptr);
                    m++; // 小数位数多了一位
                    scanner_ptr++;
                }
                else {
                    FLAG = false;
                    break;
                }
                while (*scanner_ptr >= '0' && *scanner_ptr <= '9') { // 直到读到的字符不是数字停止               
// q4 状态 
                    n = n * 10 + val(*scanner_ptr);
                    m++; // 小数位数多了一位
                    scanner_ptr++;
                }
            }
            // q5 状态
            if (*scanner_ptr == 'e') {
                t = 1;
                scanner_ptr++;
                // +1 和 -1一定是读'e'后立即判断的，也可能没有
                if (*scanner_ptr == '+' || *scanner_ptr == '-') {
                    // q6 状态
                    if (*scanner_ptr == '-') {
                        e = -1; // 指数的系数为-1了
                    }
                    scanner_ptr++;
                }
                while (*scanner_ptr >= '0' && *scanner_ptr <= '9') { // 直到读到的字符不是数字停止               
// q7 状态
                    p = p * 10 + val(*scanner_ptr);
                    scanner_ptr++;
                }
            }

            // 计算最终值的结果
            // num 来存取最终值的结果
            double num = n * pow(10, e * p - m);
            if (t == 0) { // 该数为整形
                int i = 1;
                for (; i < count1_num; i++) {
                    if (num == CI[i]) {         // 如果有重复的话，直接用原有的输出
                        //string tmp = "INTCON " + std::to_string(C1[i]);
                        //v.push_back(tmp);
                        ////printf("(C1 %d)", i);
                        token.classification = "CI";
                        token.index = i;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "CI" << "," << i << ")" << endl;
                        out.close();
                        break;
                    }
                }
                if (i == count1_num) {          //无重复的话，加入并打印
                    CI[count1_num] = num;
                    //string tmp = "INTCON " + std::to_string(C1[count1_num]);
                    //v.push_back(tmp);
                    ////printf("(C1 %d)", count1_num);
                    token.classification = "CI";
                    token.index = count1_num;
                    if_continue = false;
                    ofstream out;
                    out.open(OUTPUT_PATH, ios::app);
                    out << "(" << "CI" << "," << count1_num << ")" << endl;
                    out.close();

                    count1_num++;
                }
            }
            else { // 该数为实型
                int i = 1;
                for (; i < count2_num; i++) {
                    if (num == CR[i]) {         // 如果有重复的话，直接用原有的输出
                        //string tmp = "(C2 " + std::to_string(i) + ")";
                        //v.push_back(tmp);
                        ////printf("(C2 %d)", i);
                        token.classification = "CR";
                        token.index = i;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "CR" << "," << i << ")" << endl;
                        out.close();
                        break;
                    }
                }
                if (i == count2_num) {          //无重复的话，加入并打印
                    CR[count2_num] = num;
                    //string tmp = "(C2 " + std::to_string(count2_num) + ")";
                    //v.push_back(tmp);
                    ////printf("(C2 %d)", count2_num);
                    token.classification = "CR";
                    token.index = count2_num;
                    if_continue = false;
                    ofstream out;
                    out.open(OUTPUT_PATH, ios::app);
                    out << "(" << "CR" << "," << count2_num << ")" << endl;
                    out.close();
                    count2_num++;
                }
            }
        }
        else if (*scanner_ptr == '_' || (*scanner_ptr >= 'a' && *scanner_ptr <= 'z')
            || (*scanner_ptr >= 'A' && *scanner_ptr <= 'Z')) {
            char* mystring = new char[20];
            // 必须要每次开辟每次释放，否则上次遗留的会对下一次的结果产生影响
            int length = 0;
            mystring[length++] = *scanner_ptr;

            int flag = 1;
            // 这个用来表示是否读到数字或者是下划线，如果读到则一定是标识符
            // flag = 0 则直接搜索标识符  1时需要搜索 标识符和关键字
            scanner_ptr++;
            while (*scanner_ptr == '_' || (*scanner_ptr >= 'a' && *scanner_ptr <= 'z')
                || (*scanner_ptr >= 'A' && *scanner_ptr <= 'Z') || (*scanner_ptr >= '0' && *scanner_ptr <= '9')) {
                if (*scanner_ptr == '_' || (*scanner_ptr >= '0' && *scanner_ptr <= '9')) {
                    flag = 0;
                }
                mystring[length++] = *scanner_ptr;
                scanner_ptr++;
            }
            // 一定要加这一句，否则不能构成一个完整的字符串
            mystring[length++] = '\0';
            // 读完了
            if (flag) {
                // 先搜索关键字
                bool isfind = false;
                for (int i = 1; i <= KEY_NUM; i++) {
                    if (mystring == K[i]) {
                        isfind = true;
                        //string tmp = K_name[i] + " " + K[i];
                        //v.push_back(tmp);
                        ////printf("(K %d)", i);
                        token.classification = "K";
                        token.index = i;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "K" << "," << i << ")" << endl;
                        //out.close();
                        break;
                    }
                }

                if (!isfind) { // 关键字没找到，则是标识符
                    int i = 1;
                    for (; i < identifier_num; i++) {
                        if (mystring == I[i] && strlen(mystring) == I[i].length()) {
                            // 如果有重复的话，直接用原有的输出
                            //string tmp = "IDENFR " + I[i];
                            //v.push_back(tmp);
                            ////printf("(I %d)", i);
                            token.classification = "I";
                            token.index = i;
                            if_continue = false;
                            ofstream out;
                            out.open(OUTPUT_PATH, ios::app);
                            out << "(" << "I" << "," << i << ")" << endl;
                            out.close();
                            break;
                        }
                    }
                    if (i == identifier_num) {          //无重复的话，加入并打印
                        I[identifier_num] = mystring;
                        //string tmp = "IDENFR " + I[identifier_num];
                        //v.push_back(tmp);
                        ////printf("(I %d)", identifier_num);
                        token.classification = "I";
                        token.index = identifier_num;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "I" << "," << identifier_num << ")" << endl;
                        out.close();
                        identifier_num++;
                    }
                }
            }
            else {
                int i = 1;
                for (; i < identifier_num; i++) {
                    if (mystring == I[i] && strlen(mystring) == I[i].length()) {
                        // 如果有重复的话，直接用原有的输出
                        //string tmp = "IDENFR " + I[i];
                        //v.push_back(tmp);
                        ////printf("(I %d)", i);
                        token.classification = "I";
                        token.index = i;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "I" << "," << i << ")" << endl;
                        out.close();
                        break;
                    }
                }
                if (i == identifier_num) {          //无重复的话，加入并打印
                    I[identifier_num] = mystring;
                    //string tmp = "IDENFR " + I[identifier_num];
                    //v.push_back(tmp);
                    ////printf("(I %d)", identifier_num);
                    token.classification = "I";
                    token.index = identifier_num;
                    if_continue = false;
                    ofstream out;
                    out.open(OUTPUT_PATH, ios::app);
                    out << "(" << "I" << "," << identifier_num << ")" << endl;
                    out.close();
                    identifier_num++;
                }
            }

            delete[]mystring;
            mystring = nullptr;
        }
        else if ((*scanner_ptr >= 40 && *scanner_ptr <= 45) ||
            *scanner_ptr == 47 ||
            (*scanner_ptr >= 59 && *scanner_ptr <= 62) ||
            (*scanner_ptr >= 123 && *scanner_ptr <= 125) ||
            *scanner_ptr == 33 || *scanner_ptr == 35 ||
            (*scanner_ptr >= 37 && *scanner_ptr <= 38) ||
            *scanner_ptr == 91 || *scanner_ptr == 93) {

            // 需判断两个字符
            if (*scanner_ptr == '=' || *scanner_ptr == '>'
                || *scanner_ptr == '<' || *scanner_ptr == '!'
                || *scanner_ptr == '/' || *scanner_ptr == '+'
                || *scanner_ptr == '-' || *scanner_ptr == '*'
                || *scanner_ptr == '%') {
                switch (*scanner_ptr) {
                case '=':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '=') {
                        //string tmp = P_name[9] + " " + P[9];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 5);
                        token.classification = "P";
                        token.index = 11;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 11 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[11] + " " + P[11];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 11);
                        token.classification = "P";
                        token.index = 13;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 13 << ")" << endl;
                        out.close();
                    }
                    break;
                }

                case '>':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '=') {
                        //string tmp = P_name[8] + " " + P[8];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 14);
                        token.classification = "P";
                        token.index = 10;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 10 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else if (*scanner_ptr == '>') {
                        //string tmp = P_name[8] + " " + P[8];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 14);
                        token.classification = "P";
                        token.index = 32;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 32 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[7] + " " + P[7];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 8);
                        token.classification = "P";
                        token.index = 9;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 9 << ")" << endl;
                        out.close();
                    }
                    break;
                }

                case '<':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '=') {
                        //string tmp = P_name[6] + " " + P[6];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 16);
                        token.classification = "P";
                        token.index = 8;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 8 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else if (*scanner_ptr == '<') {
                        //string tmp = P_name[6] + " " + P[6];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 16);
                        token.classification = "P";
                        token.index = 33;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 33 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[5] + " " + P[5];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 7);
                        token.classification = "P";
                        token.index = 7;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 7 << ")" << endl;
                        out.close();
                    }
                    break;
                }
                case '!':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '=') {
                        //string tmp = P_name[10] + " " + P[10];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 16);
                        token.classification = "P";
                        token.index = 12;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 12 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        /*string tmp = "(P " + std::to_string(7) + ")";
                        v.push_back(tmp);*/
                        //printf("(P %d)", 7);
                        token.classification = "P";
                        token.index = 6;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 6 << ")" << endl;
                        out.close();
                    }
                    break;
                }
                case '/':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '/') {
                        // 特殊的地方，可以把一行全部都读掉，不影响Token串的生成
                        while (*scanner_ptr != '\n') {
                            scanner_ptr++;
                        }
                        scanner_ptr++;
                    }
                    else if (*scanner_ptr == '=') {
                        //string tmp = P_name[6] + " " + P[6];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 16);
                        token.classification = "P";
                        token.index = 21;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 21 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[4] + " " + P[4];
                        //v.push_back(tmp);
                        ///*printf("(P %d)", 7);*/
                        token.classification = "P";
                        token.index = 4;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 4 << ")" << endl;
                        out.close();
                    }
                    break;
                }
                case '%':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '=') {
                        //string tmp = P_name[9] + " " + P[9];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 5);
                        token.classification = "P";
                        token.index = 22;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 22 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[11] + " " + P[11];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 11);
                        token.classification = "P";
                        token.index = 5;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 5 << ")" << endl;
                        out.close();
                    }
                    break;
                }
                case '*':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '=') {
                        //string tmp = P_name[9] + " " + P[9];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 5);
                        token.classification = "P";
                        token.index = 20;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 20 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[11] + " " + P[11];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 11);
                        token.classification = "P";
                        token.index = 3;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 3 << ")" << endl;
                        out.close();
                    }
                    break;
                }
                case '+':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '+') {
                        token.classification = "P";
                        token.index = 16;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 16 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else if (*scanner_ptr == '=') {
                        //string tmp = P_name[6] + " " + P[6];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 16);
                        token.classification = "P";
                        token.index = 18;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 18 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[4] + " " + P[4];
                        //v.push_back(tmp);
                        ///*printf("(P %d)", 7);*/
                        token.classification = "P";
                        token.index = 1;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 1 << ")" << endl;
                        out.close();
                    }
                    break;
                }
                case '-':
                {
                    scanner_ptr++;
                    if (*scanner_ptr == '-') {
                        token.classification = "P";
                        token.index = 17;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 17 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else if (*scanner_ptr == '=') {
                        //string tmp = P_name[6] + " " + P[6];
                        //v.push_back(tmp);
                        ////printf("(P %d)", 16);
                        token.classification = "P";
                        token.index = 19;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 19 << ")" << endl;
                        out.close();
                        scanner_ptr++;
                    }
                    else {
                        //string tmp = P_name[4] + " " + P[4];
                        //v.push_back(tmp);
                        ///*printf("(P %d)", 7);*/
                        token.classification = "P";
                        token.index = 2;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << 2 << ")" << endl;
                        out.close();
                    }
                    break;
                }

                default:
                    break;
                }
            }

            else { // 单一字符
                int i = 1;
                for (; i <= PRA_NUM; i++) {
                    if (*scanner_ptr == P[i][0]) {
                        //string tmp = P_name[i] + " " + P[i];
                        //v.push_back(tmp);
                        ////printf("(P %d)", i);
                        token.classification = "P";
                        token.index = i;
                        if_continue = false;
                        ofstream out;
                        out.open(OUTPUT_PATH, ios::app);
                        out << "(" << "P" << "," << i << ")" << endl;
                        out.close();
                        break;
                    }
                }
                scanner_ptr++;
            }
        }
        else if (*scanner_ptr == 39) { // 读到字符的开始'
            scanner_ptr++;
            int i = 1;
            for (; i < char_num; i++) {
                if (*scanner_ptr == CH[i]) {         // 如果有重复的话，直接用原有的输出
                    //string tmp = "(CT " + std::to_string(i) + ")";
                    //v.push_back(tmp);
                    ////printf("(CT %d)", i);
                    token.classification = "CH";
                    token.index = i;
                    if_continue = false;
                    ofstream out;
                    out.open(OUTPUT_PATH, ios::app);
                    out << "(" << "CH" << "," << i << ")" << endl;
                    out.close();
                    break;
                }
            }
            if (i == char_num) {          //无重复的话，加入并打印
                CH[char_num] = *scanner_ptr;
                //string tmp = "(CT " + std::to_string(char_num) + ")";
                //v.push_back(tmp);
                ////printf("(CT %d)", char_num);
                token.classification = "CH";
                token.index = char_num;
                if_continue = false;
                ofstream out;
                out.open(OUTPUT_PATH, ios::app);
                out << "(" << "CH" << "," << char_num << ")" << endl;
                out.close();
                char_num++;
            }
            scanner_ptr++;
            // 判断下一个字符是否为’
            if (*scanner_ptr == 39) { // 是的话，再读下一个
                scanner_ptr++;
            }
            else {
                FLAG = false; // 词法错误
                return false;

                break;
            }
        }
        else if (*scanner_ptr == 34) { // 读到字符串的开始"
            string tmp = "";
            scanner_ptr++;
            while (*scanner_ptr != 34) { // 不是" ,则一直读取
                tmp += *scanner_ptr;
                // 指针记得后移
                scanner_ptr++;
            }
            // 要存tmp了
            int i = 1;
            for (; i < string_num; i++) {
                if (tmp == ST[i]) {         // 如果有重复的话，直接用原有的输出
                    //string tmp = "(ST " + std::to_string(i) + ")";
                    //v.push_back(tmp);
                    ////printf("(ST %d)", i);
                    token.classification = "ST";
                    token.index = i;
                    if_continue = false;
                    ofstream out;
                    out.open(OUTPUT_PATH, ios::app);
                    out << "(" << "ST" << "," << i << ")" << endl;
                    out.close();
                    break;
                }
            }
            if (i == string_num) {          //无重复的话，加入并打印
                ST[string_num] = tmp;
                //string tmp = "(ST " + std::to_string(string_num) + ")";
                //v.push_back(tmp);
                ////printf("(ST %d)", string_num);
                token.classification = "ST";
                token.index = string_num;
                if_continue = false;
                ofstream out;
                out.open(OUTPUT_PATH, ios::app);
                out << "(" << "ST" << "," << string_num << ")" << endl;
                out.close();
                string_num++;
            }

            scanner_ptr++;
        }
        else { // 在不正常的位置读到了非法字符
            FLAG = false;
            // 如果读到非法字符，返回值为错误
            return false;
        }
    }
    // 除读完外，其余情况均读到了Token串，返回正确
    if (*scanner_ptr) {
        return true;
    }
    else {
        return false;
    }
}