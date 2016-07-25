#include <stdarg.h>
#include <fstream>
#include "Jscpp.h"

using namespace std;
using namespace jc;

Jscpp::Jscpp(string _root_key)
{
	jtree = new JTree(_root_key);
}

std::string Jscpp::travel(void)
{
	assert(jtree!=NULL);	//确保jtree不为空，才可以遍历
	return jtree->travel();
}

void Jscpp::set(std::list<std::string> path, JVal jval)
{
	jtree->set(path, jval);
}

JVal Jscpp::get(std::list<std::string> path)
{
	assert(jtree);
	return jtree->get(path);
}

bool Jscpp::save(char * file_path)
{
	if (jtree == NULL)	return false;

	ofstream ofs(file_path);
	string s = travel();
	ofs << s << endl;
	ofs.close();
	return true;
}

std::list<std::string> JPath(char* s1, ...)
{
	va_list pArg;
	va_start(pArg, s1);
	list<string> path(1, s1);
	char * s = NULL;

	do
	{
		s = va_arg(pArg, char *);
		path.push_back(string(s));
	} while (strcmp(s, ":"));
	path.pop_back();			//把刚刚添加进去的":"弄出来
	va_end(pArg);

	return path;
}

char * JIndex(int index)
{
	char *s = new char [256];
	sprintf_s(s, 256, "##%d", index);
	return s;
}