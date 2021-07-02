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

bool scanner::read_program()
{
    // �� testfile.txt ��ȡ����
    string buf;
    ifstream in;

    in.open(INPUT_PATH, ios::in);

    if (!in.is_open()) {
        cout << "file not open" << endl;
        exit(1);
    }

    

    while (getline(in, buf)) {    // �������еĴ�����Ϊһ���У���ȥ���ո�
        all_ch = all_ch + buf;
        // ����ӿո���Ϊ��ʹ�� �ؼ��ֺͱ�ʶ�����뿪
        // ����Ļ� �ؼ��ֻ���ֻ����ʶ�������
        all_ch += '\n';
    }
    in.close();

    all_ch += "#";

    //string ����Ҫ'\0'���жϽ���
    scanner_ptr = all_ch.c_str();

    // ������ļ����
    ofstream out;
    out.open(OUTPUT_PATH, ios::out);
    out.close();
}

// ��ASCII��ת��Ϊ����
int scanner::val(const char ch)
{
    return ch - 48;
}

// �﷨��������Ķ�ȡ��һ��Token��
bool scanner::nextw(Token& token)
{
    // ����ı����������ж��Ƿ��Ѿ�����Token��(����Ϊfalse�˳������������ȡ)
    bool if_continue = true;
    while (*scanner_ptr && if_continue) {
        if (*scanner_ptr == ' ' || *scanner_ptr == '\n' || *scanner_ptr == '\r'
            || *scanner_ptr == '\t' || *scanner_ptr == '\v' || *scanner_ptr == '\f') {
            // �����ո�Ļ���ֱ��ѡ������
            scanner_ptr++;
            // ������Щת���ַ���û������Token������Ҫ������
            if_continue = true;
        }
        else if (*scanner_ptr >= 48 && *scanner_ptr <= 57) { // �������� & ��ʵ����
// q1 ״̬����ɳ�ʼ������
            int n = 0; // ƴβ��ֵ����
            int p = 0; // ƴָ��ֵ����
            int m = 0; // С��λ������
            int t = 0; // ָ���ķ���
            // 1 Ϊ �� �� -1 Ϊ ��
            int e = 1; // ���ͱ���
            // 0 Ϊ���ͣ� 1 Ϊʵ��
// q2 ״̬������һ���ַ�����
            n = n * 10 + val(*scanner_ptr);
            scanner_ptr++;
            // ���ж��Ƿ�Ϊ�ս��
            while (*scanner_ptr >= '0' && *scanner_ptr <= '9') { // ֱ���������ַ���������ֹͣ               
                n = n * 10 + val(*scanner_ptr);
                scanner_ptr++;
            }
            // ��������ʱ�򣬷�Ϊ�������
            // 1.��һ���ַ�����'e'��'.����ֱ���˳�
            // 2.���ǣ���ô�ͼ�������
// q3 ״̬����������
            if (*scanner_ptr == '.') {
                t = 1; // ���ڳ�ʵ����
                scanner_ptr++;
                if (*scanner_ptr >= '0' && *scanner_ptr <= '9') {
                    // ����С����󣬺�һλ����Ҫ�����֣�����ʷ�����
                    n = n * 10 + val(*scanner_ptr);
                    m++; // С��λ������һλ
                    scanner_ptr++;
                }
                else {
                    FLAG = false;
                    break;
                }
                while (*scanner_ptr >= '0' && *scanner_ptr <= '9') { // ֱ���������ַ���������ֹͣ               
// q4 ״̬ 
                    n = n * 10 + val(*scanner_ptr);
                    m++; // С��λ������һλ
                    scanner_ptr++;
                }
            }
            // q5 ״̬
            if (*scanner_ptr == 'e') {
                t = 1;
                scanner_ptr++;
                // +1 �� -1һ���Ƕ�'e'�������жϵģ�Ҳ����û��
                if (*scanner_ptr == '+' || *scanner_ptr == '-') {
                    // q6 ״̬
                    if (*scanner_ptr == '-') {
                        e = -1; // ָ����ϵ��Ϊ-1��
                    }
                    scanner_ptr++;
                }
                while (*scanner_ptr >= '0' && *scanner_ptr <= '9') { // ֱ���������ַ���������ֹͣ               
// q7 ״̬
                    p = p * 10 + val(*scanner_ptr);
                    scanner_ptr++;
                }
            }

            // ��������ֵ�Ľ��
            // num ����ȡ����ֵ�Ľ��
            double num = n * pow(10, e * p - m);
            if (t == 0) { // ����Ϊ����
                int i = 1;
                for (; i < count1_num; i++) {
                    if (num == CI[i]) {         // ������ظ��Ļ���ֱ����ԭ�е����
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
                if (i == count1_num) {          //���ظ��Ļ������벢��ӡ
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
            else { // ����Ϊʵ��
                int i = 1;
                for (; i < count2_num; i++) {
                    if (num == CR[i]) {         // ������ظ��Ļ���ֱ����ԭ�е����
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
                if (i == count2_num) {          //���ظ��Ļ������벢��ӡ
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
            // ����Ҫÿ�ο���ÿ���ͷţ������ϴ������Ļ����һ�εĽ������Ӱ��
            int length = 0;
            mystring[length++] = *scanner_ptr;

            int flag = 1;
            // ���������ʾ�Ƿ�������ֻ������»��ߣ����������һ���Ǳ�ʶ��
            // flag = 0 ��ֱ��������ʶ��  1ʱ��Ҫ���� ��ʶ���͹ؼ���
            scanner_ptr++;
            while (*scanner_ptr == '_' || (*scanner_ptr >= 'a' && *scanner_ptr <= 'z')
                || (*scanner_ptr >= 'A' && *scanner_ptr <= 'Z') || (*scanner_ptr >= '0' && *scanner_ptr <= '9')) {
                if (*scanner_ptr == '_' || (*scanner_ptr >= '0' && *scanner_ptr <= '9')) {
                    flag = 0;
                }
                mystring[length++] = *scanner_ptr;
                scanner_ptr++;
            }
            // һ��Ҫ����һ�䣬�����ܹ���һ���������ַ���
            mystring[length++] = '\0';
            // ������
            if (flag) {
                // �������ؼ���
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

                if (!isfind) { // �ؼ���û�ҵ������Ǳ�ʶ��
                    int i = 1;
                    for (; i < identifier_num; i++) {
                        if (mystring == I[i] && strlen(mystring) == I[i].length()) {
                            // ������ظ��Ļ���ֱ����ԭ�е����
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
                    if (i == identifier_num) {          //���ظ��Ļ������벢��ӡ
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
                        // ������ظ��Ļ���ֱ����ԭ�е����
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
                if (i == identifier_num) {          //���ظ��Ļ������벢��ӡ
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

            // ���ж������ַ�
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
                        // ����ĵط������԰�һ��ȫ������������Ӱ��Token��������
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

            else { // ��һ�ַ�
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
        else if (*scanner_ptr == 39) { // �����ַ��Ŀ�ʼ'
            scanner_ptr++;
            int i = 1;
            for (; i < char_num; i++) {
                if (*scanner_ptr == CH[i]) {         // ������ظ��Ļ���ֱ����ԭ�е����
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
            if (i == char_num) {          //���ظ��Ļ������벢��ӡ
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
            // �ж���һ���ַ��Ƿ�Ϊ��
            if (*scanner_ptr == 39) { // �ǵĻ����ٶ���һ��
                scanner_ptr++;
            }
            else {
                FLAG = false; // �ʷ�����
                return false;

                break;
            }
        }
        else if (*scanner_ptr == 34) { // �����ַ����Ŀ�ʼ"
            string tmp = "";
            scanner_ptr++;
            while (*scanner_ptr != 34) { // ����" ,��һֱ��ȡ
                tmp += *scanner_ptr;
                // ָ��ǵú���
                scanner_ptr++;
            }
            // Ҫ��tmp��
            int i = 1;
            for (; i < string_num; i++) {
                if (tmp == ST[i]) {         // ������ظ��Ļ���ֱ����ԭ�е����
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
            if (i == string_num) {          //���ظ��Ļ������벢��ӡ
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
        else { // �ڲ�������λ�ö����˷Ƿ��ַ�
            FLAG = false;
            // ��������Ƿ��ַ�������ֵΪ����
            return false;
        }
    }
    // �������⣬���������������Token����������ȷ
    if (*scanner_ptr) {
        return true;
    }
    else {
        return false;
    }
}