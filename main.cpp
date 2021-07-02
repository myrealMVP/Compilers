#include <iostream>
#include "Token.h"
#include "GramTrans.h"
using namespace std;

int main()
{
    GramTrans gra_tra;
    gra_tra.s.read_program();

    gra_tra.Parse();
    /*scanner s;
   Token token;
   s.read_program();

   while (s.nextw(token)) {
       cout << token.classification << " " << token.index << endl;
   }

   cout << endl;
   cout << "标识符表：" << endl;
   for (int i = 1; i < s.identifier_num; i++) {
       cout << s.I[i] << endl;
   }

   cout << endl;
   cout << "常整数表：" << endl;
   for (int i = 1; i < s.count1_num; i++) {
       cout << s.CI[i] << endl;
   }

   cout << endl;
   cout << "常实数表：" << endl;
   for (int i = 1; i < s.count2_num; i++) {
       cout << s.CR[i] << endl;
   }

   cout << endl;
   cout << "字符常量表：" << endl;
   for (int i = 1; i < s.char_num; i++) {
       cout << s.CH[i] << endl;
   }

   cout << endl;
   cout << "字符串常量表：" << endl;
   for (int i = 1; i < s.string_num; i++) {
       cout << s.ST[i] << endl;
   }*/

    return 0;
}