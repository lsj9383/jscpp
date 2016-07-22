#include <iostream>
#include "Jscpp.h"

using namespace std;
using namespace jc;

void JscppDemo(void)
{
	string st;
	Jscpp *jscpp = new Jscpp("student");
	jscpp->set(JSTRING, "name", ":", string("lsj"));
	jscpp->set(JINT, "code", ":", 7);
	jscpp->set(JINT, "age", ":", 23);
	jscpp->set(JBOOL, "man", ":", true);
	jscpp->set(JBOOL, "marry", ":", false);
	jscpp->set(JBOOL, "test", "pass", ":", true);
	jscpp->set(JDOUBLE, "test", "grade", "chinese", ":", 89.0);
	jscpp->set(JDOUBLE, "test", "grade", "math", ":", 115.5);
	jscpp->set(JDOUBLE, "test", "grade", "english", ":", 103.1);

	st = jscpp->travel();

	cout << st << std::endl;
	jscpp->save("student.json");

	delete jscpp;
}