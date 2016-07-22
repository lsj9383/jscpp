#include <iostream>
#include "Jscpp.h"

using namespace std;
using namespace jp;

void NodeDemo(void);

int main(void)
{
//	NodeDemo();
	string st;
	Jscpp jscpp("nihao");
	jscpp.set(7, "code", ":");
	jscpp.set(23, "age", ":");
	jscpp.set(1993, "year", ":");
	jscpp.set(4, "month", ":");
	jscpp.set(26, "day", ":");
	jscpp.set(89, "grad", "chinese", ":");
	jscpp.set(115, "grad", "math", ":");
	jscpp.set(103, "grad", "english", ":");
	jscpp.set(102, "grad", "english", ":");
	st = jscpp.travel();
	
	cout << st << std::endl;
	jscpp.save("student.json");
	return 0;
}