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
/* ����Ķ�����ǹؼ��ֺͽ����������
   ������ӹؼ��ֺͽ����
   1.��K / P ������Ӧ�Ĺؼ��ֺͽ��
   2.���� KEY_NUM / PRA_NUM ������
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
    int count1_num = 1; // �������ĸ���
    int count2_num = 1; // ��ʵ���ĸ��� 
    int char_num = 1;   // �ַ��ĸ���
    int string_num = 1; // �ַ����ĸ��� 
    bool FLAG = true; // �жϴʷ��Ƿ�Ϸ�
    vector<string> v; // ������ȡTOKEN����
    string all_ch;
    //********************ȫ��������Ҫ��ָ��**********************************
    //string ����Ҫ'\0'���жϽ���
    // �����������Ĵ�תΪchar*
    const char* scanner_ptr;
    bool read_program();
    int val(const char ch);
    bool nextw(Token& token);

    // ***************************************�ؼ��ֱ�**************************************
    string K[KEY_NUM + 1] =
    {
        "",
        // ����
        "const",
        "int",
        "short",
        "float",
        "double",
        "char",
        "string",
        "bool",
        // ����
        "void",
        "main",
        "return",
        // �ж�
        "if",
        "else",
        // ѭ��
        "do",
        "while",
        "for",
        "break",
        // �������
        "cin",
        "cout",
        // �ṹ
        "struct",
    };

    // ***************************************�����**************************************
    string P[PRA_NUM + 1] =
    {
        "",
        // �ӡ������ˡ�����ģ����
        "+",
        "-",
        "*",
        "/",
        "%",
        "!",
        // С�ڡ�С�ڵ��ڡ����ڡ����ڵ��ڡ����ڡ�������
        "<",
        "<=",
        ">",
        ">=",
        "==",
        "!=",
        // ��ֵ���ֺš�����
        "=",
        ";",
        ",",
        // ˫Ŀ�����
        "++",
        "--",
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        // Բ���š������š�������
        "(",
        ")",
        "[",
        "]",
        "{",
        "}",
        // ע��
        "//",
        // �߼�
        "&&",
        "||",
        // �������������
        ">>",
        "<<",
        // ���������ʶ
        "#",
        // �����š�˫����
        "'",
        "\"",
    };

    // ***************************************��ʶ����**************************************
    string I[50]
    {
        ""
    };

    // ***************************************ʵ������(int)**************************************
    int CI[50]
    {
        0
    };

    // ***************************************ʵ��������(double)**************************************
    double CR[50]
    {
        0
    };

    // ***************************************�ַ�������**************************************
    char CH[50]
    {
        ' '
    };

    // ***************************************�ַ���������(double)**************************************
    string ST[50]
    {
        ""
    };
};