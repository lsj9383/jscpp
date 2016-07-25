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
	int index;

	Jscpp *jscpp = new Jscpp("student");

	//set test
	index = 0;
	jscpp->set(JPath(JIndex(index), "name", ":"), string("lsj"));
	jscpp->set(JPath(JIndex(index), "marry", ":"), false);
	jscpp->set(JPath(JIndex(index), "birthday", JIndex(0), ":"), 1993);
	jscpp->set(JPath(JIndex(index), "birthday", JIndex(1), ":"), 4);
	jscpp->set(JPath(JIndex(index), "birthday", JIndex(2), ":"), 26);
	jscpp->set(JPath(JIndex(index), "test", "pass", ":"), true);
	jscpp->set(JPath(JIndex(index), "test", "grade", "chinese", ":"), 89.0);
	jscpp->set(JPath(JIndex(index), "test", "grade", "math", ":"), 115.5);
	jscpp->set(JPath(JIndex(index), "test", "grade", "english", ":"), 103.1);

	index = 1;
	jscpp->set(JPath(JIndex(index), "name", ":"), string("hjs"));
	jscpp->set(JPath(JIndex(index), "marry", ":"), true);
	jscpp->set(JPath(JIndex(index), "birthday", JIndex(0), ":"), 1992);
	jscpp->set(JPath(JIndex(index), "birthday", JIndex(1), ":"), 7);
	jscpp->set(JPath(JIndex(index), "birthday", JIndex(2), ":"), 16);
	jscpp->set(JPath(JIndex(index), "test", "pass", ":"), false);
	jscpp->set(JPath(JIndex(index), "test", "grade", "chinese", ":"), 99.0);
	jscpp->set(JPath(JIndex(index), "test", "grade", "math", ":"), 125.5);
	jscpp->set(JPath(JIndex(index), "test", "grade", "english", ":"), 43.1);

	//travel test
	cout << jscpp->travel() << endl;


	//file test
	jscpp->save("student.json");
 	delete jscpp;
}