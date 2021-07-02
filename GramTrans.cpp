#include <iostream>
#include "GramTrans.h"
using namespace std;

//void GramTrans::setQuat(string o, Token a1, Token a2, Token r) {
//	quat.op = o;
//	quat.arg1.setToken(a1);
//	quat.arg2.setToken(a2);
//	quat.res.setToken(r);
//}

void GramTrans::Parse() {
	s.nextw(token);
	MAIN();
	/*
	if (flag == false) {
		exit(1);
	}
	*/
	if (token.classification == "P" && token.index == 34)//是#
	{
		cout << "OK!";
	}
	else {
		cout << "err1";
		exit(1);
	}
}

void GramTrans::MAIN() {
	if (token.classification == "K" && token.index == 2) {//int
		s.nextw(token);
		if (token.classification == "K" && token.index == 10) {//main
			s.nextw(token);
			if (token.classification == "P" && token.index == 23) {//(
				s.nextw(token);
				if (token.classification == "P" && token.index == 24) {//)
					s.nextw(token);
					if (token.classification == "P" && token.index == 27) {//{
						s.nextw(token);
						LIST();
						if (token.classification == "K" && token.index == 11) {//return
							s.nextw(token);
							if (token.classification == "CI") {//整数,如0
								s.nextw(token);
								if (token.classification == "P" && token.index == 14) {//;
									s.nextw(token);
									if (token.classification == "P" && token.index == 28) {//}
										s.nextw(token);
									}
									else {
										cout << "err10!"; //}
										exit(1);
									}
								}
								else {
									cout << "err9!"; //;
									exit(1);
								}
							}
							else {
								cout << "err8!"; //整数,如0
								exit(1);
							}
						}
						else {
							cout << "err7!";//return
							exit(1);
						}
					}
					else {
						cout << "err6!";//{
						exit(1);
					}
				}
				else {
					cout << "err5!";//)
					exit(1);
				}
			}
			else {
				cout << "err4!";//(
				exit(1);
			}
		}
		else {
			cout << "err3!";//main
			exit(1);
		}
	}
	else {
		cout << "err2!";//int
		exit(1);
	}
}

void GramTrans::LIST() {
	if (token.classification == "K" && (token.index == 2 || token.index == 4 || token.index == 5 || token.index == 6 || token.index == 7 || token.index == 8)
		|| token.classification == "I"
		|| token.classification == "K" && (token.index == 12 || token.index == 15)) {//int| char | float | double |bool|string，id,if,while
		SENTENCE();
		LIST();
	}
}

void GramTrans::SENTENCE() {
	if (token.classification == "K" && (token.index == 2 || token.index == 4 || token.index == 5 || token.index == 6 || token.index == 7 || token.index == 8)) {//int| char | float | double |bool|string
		V_ST();
	}
	else if (token.classification == "I") {//id
		ASSIGN();
	}
	else if (token.classification == "K" && token.index == 12) {//if
		IFJU();
	}
	else {//while
		WHJU();
	}
}

void GramTrans::V_ST() {
	TYPE();
	V1_ST();
	//
	while (token.classification == "P" && token.index == 15) {//,
		s.nextw(token);
		V1_ST();
	}
	if (token.classification == "P" && token.index == 14) {//;
		s.nextw(token);
	}
	else {
		cout << "err25!";
		exit(1);
	}
}

void GramTrans::TYPE() {
	switch (token.index)
	{
	case 2://int
		//在符号表下一行的type格填上itp
		s.nextw(token);
		break;
	case 4://float
		s.nextw(token);
		break;
	case 5://double
		s.nextw(token);
		break;
	case 6://char
		s.nextw(token);
		break;
	case 7://string
		s.nextw(token);
		break;
	case 8://bool
		s.nextw(token);
		break;
	default:cout << "err11!";
		exit(1);
	}
}
void GramTrans::V1_ST() {
	if (token.classification == "I") {//标识符
		//填当前行，id.entry:=id_Token.val; 
		//压语义栈，push(id.entry);
		s.nextw(token);
		if (token.classification == "P" && token.index == 13) {//=
			s.nextw(token);
			if (token.classification == "CH") {//字符
				s.nextw(token);
			}
			else if (token.classification == "ST") {//字符串
				s.nextw(token);
			}
			else {//E
				E();

			}
		}
	}
	else {
		cout << "err12!";
		exit(1);
	}
}

void GramTrans::E() {
	T();
	E1();
}
void GramTrans::E1() {
	if (token.classification == "P" && (token.index == 1 || token.index == 2)) {//w0
		s.nextw(token);
		T();
		E1();
	}
}

void GramTrans::T() {
	F();
	T1();
}
void GramTrans::T1() {
	if (token.classification == "P" && (token.index == 3 || token.index == 4 || token.index == 5)) {//w1
		s.nextw(token);
		F();
		T1();
	}
}
void GramTrans::F() {
	if (token.classification == "P" && (token.index == 16 || token.index == 17)) {//w2
		s.nextw(token);
		U();
	}
	U();
}
void GramTrans::U() {
	if (token.classification == "I" || token.classification == "CI" || token.classification == "CR") {//标识符、常数
		s.nextw(token);
	}
	else if (token.classification == "P" && token.index == 23) {//(
		s.nextw(token);
		E();
		if (token.classification == "P" && token.index == 24) {//)
			s.nextw(token);
		}
	}
	else {
		cout << "err13!";
		exit(1);
	}
}

void GramTrans::ASSIGN() {
	if (token.classification == "I") {//id
		s.nextw(token);
		if (token.classification == "P" && token.index == 13) {//=
			s.nextw(token);
			E();
			//Token a1 = SEM.top();
			//SEM.pop();
			//Token a2 = SEM.top();
			//SEM.pop();

			//quat.setQuat("=",a1,)
			if (token.classification == "P" && token.index == 14) {//;
				s.nextw(token);
			}
			else {
				cout << "err16!";
				exit(1);
			}
		}
		else {
			cout << "err15!";
			exit(1);
		}
	}
	else {
		cout << "err14!";
		exit(1);
	}
}

void GramTrans::IFJU() {
	if (token.classification == "K" && token.index == 12) {//if
		s.nextw(token);
		if (token.classification == "P" && token.index == 23) {//(
			s.nextw(token);
			R();
			if (token.classification == "P" && token.index == 24) {//)
				s.nextw(token);
				if (token.classification == "P" && token.index == 27) {//{
					FUHE();
				}
				else {
					SENTENCE();
				}
				if (token.classification == "K" && token.index == 13) {//else
					s.nextw(token);
					if (token.classification == "P" && token.index == 27) {//{
						FUHE();
					}
					else {
						SENTENCE();
					}
				}
			}
			else {
				cout << "err19!";
				exit(1);
			}
		}
		else {
			cout << "err18!";
			exit(1);
		}
	}
	else {
		cout << "err17!";
		exit(1);
	}
}

void GramTrans::WHJU() {
	if (token.classification == "K" && token.index == 15) {//while
		s.nextw(token);
		if (token.classification == "P" && token.index == 23) {//(
			s.nextw(token);
			R();
			if (token.classification == "P" && token.index == 24) {//)
				s.nextw(token);
				if (token.classification == "P" && token.index == 27) {//{
					FUHE();
				}
				else {
					SENTENCE();
				}
			}
			else {
				cout << "err22!";
				exit(1);
			}
		}
		else {
			cout << "err21!";
			exit(1);
		}
	}
	else {
		cout << "err20!";
		exit(1);
	}
}
void GramTrans::FUHE() {
	if (token.classification == "P" && token.index == 27) {//{
		s.nextw(token);
		LIST();
		if (token.classification == "P" && token.index == 28) {//}
			s.nextw(token);
		}
		else {
			cout << "err24!";
			exit(1);
		}
	}
	else {
		cout << "err23!";
		exit(1);
	}
}

void GramTrans::R() {
	RT();
	if (token.classification == "P" && token.index == 31) {//||
		s.nextw(token);
		R();
	}
}
void GramTrans::RT() {
	RF();
	if (token.classification == "P" && token.index == 30) {//&&
		s.nextw(token);
		RT();
	}
}
void GramTrans::RF() {
	RF2();
	while (token.classification == "P" && (token.index == 11 || token.index == 12)) {//a1
		s.nextw(token);
		RF2();
	}
}
void GramTrans::RF2() {
	E();
	while (token.classification == "P" && (token.index == 7 || token.index == 8 || token.index == 9 || token.index == 10)) {//a2
		s.nextw(token);
		E();
	}
}