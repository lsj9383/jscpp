#include <iostream>
#include "Jscpp.h"

using namespace std;
using namespace jc;

void NodeDemo(void)
{
	JNode node1("ni1", 3);
	JNode node2("ni2", 3.0);
	JNode node3("ni3", string("nihaoya"));
	JNode node4("ni4", true);
	JNode node5("ni4", JVal(true));
}

void JscppDemo(void)
{
	Jscpp *jscpp = new Jscpp("student");
	jscpp->set(JPath("name", ":"), string("lsj"));
	jscpp->set(JPath("code", ":"), 7);
	jscpp->set(JPath("age", ":"), 23);
	jscpp->set(JPath("man", ":"), true);
	jscpp->set(JPath("marry", ":"), false);
	jscpp->set(JPath("test", "pass", ":"), true);
	jscpp->set(JPath("test", "grade", "chinese", ":"), 89.0);
	jscpp->set(JPath("test", "grade", "math", ":"), 115.5);
	jscpp->set(JPath("test", "grade", "english", ":"), 103.1);
	jscpp->set(JPath("test", "grade", "phy", ":"), 98.0);

	cout << *jscpp->get(JPath("test", "pass", ":")).GetData().pBool << endl;
	cout << *jscpp->get(JPath("test", "grade", "phy", ":")).GetData().pDouble << endl;
	cout << *jscpp->get(JPath("name", ":")).GetData().pString << endl;
//	cout << *jscpp->get(JPath("test", "pass", "phy", ":")).GetData().pBool << endl;		//error
	cout << jscpp->travel() << endl;
	jscpp->save("student.json");

	delete jscpp;
}

void FunctionDemo(void){
	/*
	deque<string> path = PathDeque("fei", "ji", "da", "pao", ":");
	for (int i = 0; i < path.size(); i++){
	cout << path[i] << endl;
	}
	*/
}