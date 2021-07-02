#pragma once
#pragma once
#pragma once
#include <iostream>
#include <stack>
#include "Token.h"
using namespace std;

class Quat {
public:
	string op;
	Token arg1;
	Token arg2;
	Token res;
};

class GramTrans {
public:
	scanner s;
	Token token;
	Token gang;
	bool flag;
	Quat quat;

	stack <Token> SYN;
	stack <Token> SEM;
	vector <Quat> QT;

	//GramTrans(){gang.classification}
	void setQuat(string o, Token a1, Token a2, Token r);

	void Parse();
	void MAIN();
	void LIST();
	void SENTENCE();
	void V_ST();
	void ASSIGN();
	void IFJU();
	void WHJU();
	void TYPE();
	void V1_ST();

	void E();
	void E1();
	void T();
	void T1();
	void F();
	void U();

	void FUHE();
	void R();
	void RT();
	void RF();
	void RF2();
};